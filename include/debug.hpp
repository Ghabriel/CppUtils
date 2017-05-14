/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#ifndef UTILS_DEBUG_HPP
#define UTILS_DEBUG_HPP

#include <csignal>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>

#ifndef ALLOW_DEBUG_USAGE
#define ALLOW_DEBUG_USAGE 1
#endif

#ifndef DEBUG_ENABLED
#define DEBUG_ENABLED 1
#endif

#if ALLOW_DEBUG_USAGE == 1

namespace detail {
    std::pair<size_t, std::string> debugBuffer;
    const std::unordered_map<int, std::string> debugLabels = {
        {SIGABRT, "Aborted"},
        {SIGFPE, "Division by zero"},
        {SIGILL, "SIGILL"},
        {SIGINT, "Interruption"},
        {SIGSEGV, "Segmentation fault"},
        {SIGTERM, "SIGTERM"}
    };

    inline void printer(int type) {
        auto line = std::to_string(debugBuffer.first);
        auto& filename = debugBuffer.second;
        std::cout << debugLabels.at(type) << " in " << filename
                  << ":" << line << std::endl;
        std::signal(type, SIG_DFL);
        std::raise(type);
    }

    using StreamType = decltype(std::cout);

    struct StreamContainer {
        static std::reference_wrapper<StreamType> stream;
    };
    decltype(StreamContainer::stream) StreamContainer::stream = std::cout;

    inline StreamType& stream() {
        return StreamContainer::stream.get();
    }

    template<bool = DEBUG_ENABLED>
    struct DebugContainer;

    template<>
    struct DebugContainer<true> {
        static void echo() {}

        template<typename T, typename... Args>
        static void echo(const T& value, Args&&... args) {
            stream() << value << '\n';
            echo(std::forward<Args>(args)...);
        }

        static void echoIndented(size_t) {}

        template<typename T, typename... Args>
        static void echoIndented(size_t numTabs, const T& value, Args&&... args) {
            for (size_t i = 0; i < numTabs; i++) {
                stream() << "\t";
            }
            echo(value);
            echoIndented(numTabs, std::forward<Args>(args)...);
        }

        template<typename T>
        static void trace(const std::string& name, const T& value) {
            stream() << name << " = ";
            echo(value);
        }

        template<typename T, typename F>
        static void trace(const std::string& name, const T& value, const F& formatter) {
            stream() << name << " = " << formatter(value) << '\n';
        }

        template<typename T>
        static void traceIterable(const std::string& name, const T& value) {
            unsigned long long counter = 0;
            for (auto& elem : value) {
                stream() << name << "[" << std::to_string(counter++) << "] = ";
                echo(elem);
            }
        }

        static void debug(size_t line, const std::string& filename) {
            debugBuffer = {line, filename};
            static bool ready = false;
            if (!ready) {
                for (auto& pair : debugLabels) {
                    std::signal(pair.first, printer);
                }
                ready = true;
            }
        }

        template<typename T>
        static void debugRedirect(T& stream) {
            StreamContainer::stream = stream;
        }
    };

    template<>
    struct DebugContainer<false> {
        template<typename... Args>
        static void echo(Args&&...) {}

        template<typename... Args>
        static void echoIndented(Args&&...) {}

        template<typename... Args>
        static void trace(Args&&...) {}

        template<typename T>
        static void traceIterable(const std::string&, const T&) {}

        static void debug(size_t, const std::string&) {}

        template<typename T>
        static void debugRedirect(const T&) {}
    };
}

template<typename... Args>
inline void echo(Args&&... args) {
    detail::DebugContainer<>::echo(std::forward<Args>(args)...);
}

template<typename... Args>
inline void echoIndented(size_t numTabs, Args&&... args) {
    detail::DebugContainer<>::echoIndented(numTabs, std::forward<Args>(args)...);
}

template<typename... Args>
inline void trace(Args&&... args) {
    detail::DebugContainer<>::trace(std::forward<Args>(args)...);
}

template<typename T>
inline void traceIterable(const std::string& name, const T& value) {
    detail::DebugContainer<>::traceIterable(name, value);
}

inline void debug(size_t line, const std::string& filename) {
    detail::DebugContainer<>::debug(line, filename);
}

template<typename T>
inline void debugRedirect(T& stream) {
    detail::DebugContainer<>::debugRedirect(stream);
}

#define FIRST_NAME(v, ...) (#v)

#define ECHO(...) echo(__VA_ARGS__)
#define ECHOI(numTabs,...) echoIndented((numTabs), __VA_ARGS__)
#define TRACE(...) trace(FIRST_NAME(__VA_ARGS__), __VA_ARGS__)
#define TRACE_L(x,...) trace((x), __VA_ARGS__)
#define TRACE_IT(x) traceIterable((#x), (x))
#define TRACE_ITL(x) traceIterable((l), (x))
#define BLANK ECHO("");
#define DEBUG debug(__LINE__, __FILE__);
#define DEBUG_REDIRECT(stream) debugRedirect(stream)

#if DEBUG_ENABLED == 1
    #define DEBUG_EXEC(...) __VA_ARGS__
#else
    #define DEBUG_EXEC(...) ;
#endif

#else

#define ECHO(...) {int debug_usage;}
#define ECHOI(numTabs,...) {int debug_usage;}
#define TRACE(...) {int debug_usage;}
#define TRACE_L(x,...) {int debug_usage;}
#define TRACE_IT(x) {int debug_usage;}
#define TRACE_ITL(x) {int debug_usage;}
#define BLANK {int debug_usage;}
#define DEBUG {int debug_usage;}
#define DEBUG_EXEC(...) {int debug_usage;}

#endif

#endif
