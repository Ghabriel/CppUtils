/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#ifndef UTILS_DEBUG_HPP
#define UTILS_DEBUG_HPP

#include <csignal>
#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>

#ifndef ALLOW_DEBUG_USAGE
#define ALLOW_DEBUG_USAGE 1
#endif

#ifndef DEBUG_ENABLED
#define DEBUG_ENABLED 1
#endif

#if ALLOW_DEBUG_USAGE == 1

namespace dbg {
    class ArbitraryStream {
     public:
        virtual ArbitraryStream& operator<<(const std::string&) = 0;
    };

    template<typename... Args>
    void echo(Args&&...);

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
            std::stringstream ss;
            ss << debugLabels.at(type) << " in " << filename
               << ":" << line;
            echo(ss.str());
            std::signal(type, SIG_DFL);
            std::raise(type);
        }


        using StreamType = decltype(std::cout);

        class StreamContainer : public ArbitraryStream {
         public:
            static StreamContainer& instance() {
                static StreamContainer inst;
                return inst;
            }

            StreamContainer& operator<<(const std::string& message) {
                stream.get() << message;
                return *this;
            }

            void setStream(StreamType& newStream) {
                stream = newStream;
            }

         private:
            StreamContainer() = default;

            std::reference_wrapper<StreamType> stream = std::cout;
        };


        struct Container {
            static std::reference_wrapper<ArbitraryStream> activeStream;
        };
        decltype(Container::activeStream) Container::activeStream = StreamContainer::instance();


        inline ArbitraryStream& stream() {
            return Container::activeStream;
        }

        template<bool = DEBUG_ENABLED>
        struct DebugContainer;

        template<>
        struct DebugContainer<true> {
            static void echo() {}

            template<typename T, typename... Args>
            static void echo(const T& value, Args&&... args) {
                std::stringstream ss;
                ss << value << '\n';
                stream() << ss.str();
                echo(std::forward<Args>(args)...);
            }

            template<typename... Args>
            static void echo(const std::string& value, Args&&... args) {
                stream() << (value + '\n');
                echo(std::forward<Args>(args)...);
            }

            static void echoIndented(size_t) {}

            template<typename T, typename... Args>
            static void echoIndented(size_t numTabs, const T& value, Args&&... args) {
                std::stringstream ss;
                for (size_t i = 0; i < numTabs; i++) {
                    ss << "\t";
                }
                ss << value;
                echo(ss.str());
                echoIndented(numTabs, std::forward<Args>(args)...);
            }

            template<typename T>
            static void trace(const std::string& name, const T& value) {
                std::stringstream ss;
                ss << name << " = " << value;
                echo(ss.str());
            }

            static void trace(const std::string& name, const std::string& value) {
                echo(name + " = " + value);
            }

            template<typename T, typename F>
            static void trace(const std::string& name, const T& value, const F& formatter) {
                trace(name, formatter(value));
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

            static void debugRedirect(StreamType& stream) {
                static auto& streamContainer = StreamContainer::instance();
                Container::activeStream = streamContainer;
                streamContainer.setStream(stream);
            }

            static void debugRedirect(ArbitraryStream& stream) {
                Container::activeStream = stream;
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
}

#define FIRST_NAME(v, ...) (#v)

#define ECHO(...) dbg::echo(__VA_ARGS__)
#define ECHOI(numTabs,...) dbg::echoIndented((numTabs), __VA_ARGS__)
#define TRACE(...) dbg::trace(FIRST_NAME(__VA_ARGS__), __VA_ARGS__)
#define TRACE_L(x,...) dbg::trace((x), __VA_ARGS__)
#define TRACE_IT(x) dbg::traceIterable((#x), (x))
#define TRACE_ITL(x) dbg::traceIterable((l), (x))
#define BLANK ECHO("");
#define DEBUG dbg::debug(__LINE__, __FILE__);
#define DEBUG_REDIRECT(stream) dbg::debugRedirect(stream)

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
