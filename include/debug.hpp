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

namespace detail {
    // constexpr bool ALLOW_DEBUG_USAGE = true;
    // constexpr bool DEBUG_ENABLED = true;

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
            echo(args...);
        }

        template<typename T>
        static void echoIndented(const T& value, size_t numTabs) {
            for (size_t i = 0; i < numTabs; i++) {
                std::cout << "\t";
            }
            echo(value);
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

        template<typename T>
        static void echoIndented(const T&, size_t) {}

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

template<typename T>
inline void echoIndented(const T& value, size_t numTabs) {
    detail::DebugContainer<>::echoIndented(value, numTabs);
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

#if ALLOW_DEBUG_USAGE == 1

#define FIRST_NAME(v, ...) (#v)

#define ECHO(...) echo(__VA_ARGS__)
#define ECHOI(x,numTabs) echoIndented((x),(numTabs))
#define TRACE(...) trace(FIRST_NAME(__VA_ARGS__), __VA_ARGS__)
#define TRACE_L(x,y) trace((x), (y))
#define TRACE_IT(x) traceIterable((#x), (x))
#define TRACE_ITL(x) traceIterable((l), (x))
#define BLANK ECHO("");
#define DEBUG debug(__LINE__, __FILE__);

#else

#define ECHO(...) {int debug_usage;}
#define ECHOI(x,n) {int debug_usage;}
#define TRACE(x) {int debug_usage;}
#define TRACE_L(x,y) {int debug_usage;}
#define TRACE_IT(x) {int debug_usage;}
#define BLANK {int debug_usage;}
#define DEBUG {int debug_usage;}

#endif

#endif
