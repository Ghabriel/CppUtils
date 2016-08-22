/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef UTILS_MACROS_HPP
#define UTILS_MACROS_HPP

#include <utility>

namespace {
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

    inline void echo() {}

    template<typename T, typename... Args>
    inline void echo(const T& value, Args&&... args) {
        std::cout << traceable(value) << std::endl;
        echo(args...);
    }
}

// #define TRACE(x) std::cout << (#x) << " = " << (x) << std::endl
#define TRACE(x) std::cout << (#x) << " = " << traceable(x) << std::endl
#define TRACE_L(x,y) std::cout << (x) << " = " << (y) << std::endl
#define TRACE_IT(x) \
    {\
        unsigned long long counter = 0; \
        for (auto& elem : (x)) { \
            std::cout << (#x) << "[" << std::to_string(counter++) << "] = " << elem << std::endl; \
        }\
    }
#define TRACE_ITL(l,x) \
    {\
        unsigned long long counter = 0; \
        for (auto& elem : (x)) { \
            std::cout << (l) << "[" << std::to_string(counter++) << "] = " << elem << std::endl; \
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
