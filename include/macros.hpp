/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef UTILS_MACROS_HPP
#define UTILS_MACROS_HPP

#include <iostream>
#include <ostream>
#include <sstream>
#include <utility>

namespace {
    template<typename T>
    inline std::string traceable(T* const value) {
        std::stringstream ss;
        ss << static_cast<const void*>(value);
        return ss.str();
    }
    template<typename T>
    inline std::string traceable(const T& value) { return std::to_string(value); }
    inline std::string traceable(const char* value) { return value; }
    inline std::string traceable(const std::string& value) { return value; }
    inline std::string traceable(char value) { return std::string(1, value); }

    template<typename T1, typename T2>
    inline std::string traceable(const std::pair<T1, T2>& pair) {
        return '{' + traceable(pair.first) + ", " + traceable(pair.second) + '}';
    }

    template<typename T>
    inline std::string construct(const T& value) {
        return traceable(value);
    }

    template<typename T1, typename T2, typename... Args>
    inline std::string construct(const T1& value, const T2& next, Args&&... args) {
        return traceable(value) + ", " + construct(next, args...);
    }

    template<typename... Types, size_t... I>
    inline std::string extract(const std::tuple<Types...>& tuple, std::index_sequence<I...>) {
        return construct(std::get<I>(tuple)...);
    }

    template<typename... Types>
    inline std::string traceable(const std::tuple<Types...>& tuple) {
        return '{' + extract(tuple, std::make_index_sequence<sizeof...(Types)>()) + '}';
    }

    using no = char;
    using yes = char[2];
    no ref_no;
    yes ref_yes;

    struct any_t {
        any_t(...) {}
    };
}

inline no operator<<(std::ostream&, const any_t&) { return ref_no; }

namespace {
    inline yes& test(std::ostream&) { return ref_yes; }
    inline no test(no) { return ref_no; }
    template<typename T>
    struct insertion_exists {
        static std::ostream& stream;
        const static T& t;
        constexpr static bool value = sizeof(test(stream << t)) == sizeof(yes);
    };

    template<typename T, bool>
    struct fallback {
        static void apply(std::ostream& stream, const T& value) {
            stream << value;
        }
    };

    template<typename T>
    struct fallback<T, false> {
        static void apply(std::ostream& stream, const T& value) {
            stream << traceable(value);
        }
    };

    inline void echo() {}        

    template<typename T, typename... Args>
    inline void echo(const T& value, Args&&... args) {
        fallback<T, insertion_exists<T>::value>::apply(std::cout, value);
        std::cout << std::endl;
        echo(args...);
    }

    template<typename T>
    inline void trace(const std::string& name, const T& value) {
        std::cout << name << " = ";
        echo(value);
    }
}

#define TRACE(x) trace((#x), (x));
#define TRACE_L(x,y) trace((x), (y))
#define TRACE_IT(x) \
    {\
        unsigned long long counter = 0; \
        for (auto& elem : (x)) { \
            std::cout << (#x) << "[" << std::to_string(counter++) << "] = "; \
            echo(elem); \
        }\
    }
#define TRACE_ITL(l,x) \
    {\
        unsigned long long counter = 0; \
        for (auto& elem : (x)) { \
            std::cout << (l) << "[" << std::to_string(counter++) << "] = "; \
            echo(elem); \
        }\
    }
#define ECHO(...) echo(__VA_ARGS__)
#define ECHOI(x,numTabs) \
    for (unsigned i = 0; i < numTabs; i++) {\
        std::cout << "\t"; \
    }\
    ECHO(x)

#define BLANK ECHO("");

#define DEBUG \
    {\
        auto line = std::to_string(__LINE__); \
        std::string prefix = "[debug] "; \
        ECHO(prefix + __FILE__ + ":" + line); \
    }

#define EXPAND(cmd) (int[]){((cmd), 0)...}

#endif
