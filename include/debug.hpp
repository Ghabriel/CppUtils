/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#ifndef UTILS_DEBUG_HPP
#define UTILS_DEBUG_HPP

#include <csignal>
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

    template<bool = DEBUG_ENABLED>
    struct DebugContainer;

    template<>
    struct DebugContainer<true> {
        static void echo() {}

        template<typename T, typename... Args>
        static void echo(const T& value, Args&&... args) {
            std::cout << value << std::endl;
            echo(std::forward<Args>(args)...);
        }

        static void echoIndented(size_t) {}

        template<typename T, typename... Args>
        static void echoIndented(size_t numTabs, const T& value, Args&&... args) {
            for (size_t i = 0; i < numTabs; i++) {
                std::cout << "\t";
            }
            echo(value);
            echoIndented(numTabs, std::forward<Args>(args)...);
        }

        template<typename T>
        static void trace(const std::string& name, const T& value) {
            std::cout << name << " = ";
            echo(value);
        }

        template<typename T, typename F>
        static void trace(const std::string& name, const T& value, const F& formatter) {
            std::cout << name << " = " << formatter(value) << std::endl;
        }

        template<typename T>
        static void traceIterable(const std::string& name, const T& value) {
            unsigned long long counter = 0;
            for (auto& elem : value) {
                std::cout << name << "[" << std::to_string(counter++) << "] = ";
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

#define FIRST_NAME(v, ...) (#v)

#define ECHO(...) echo(__VA_ARGS__)
#define ECHOI(numTabs,...) echoIndented((numTabs), __VA_ARGS__)
#define TRACE(...) trace(FIRST_NAME(__VA_ARGS__), __VA_ARGS__)
#define TRACE_L(x,...) trace((x), __VA_ARGS__)
#define TRACE_IT(x) traceIterable((#x), (x))
#define TRACE_ITL(x) traceIterable((l), (x))
#define BLANK ECHO("");
#define DEBUG debug(__LINE__, __FILE__);

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
