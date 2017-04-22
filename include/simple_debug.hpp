/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#ifndef UTILS_SIMPLE_DEBUG_HPP
#define UTILS_SIMPLE_DEBUG_HPP

#include <iostream>

#define ECHO(x) std::cout << x << std::endl;
#define TRACE(x) std::cout << (#x) << " = " << (x) << std::endl;

#define ECHOI(x,numTabs) \
    for (size_t i = 0; i < numTabs; i++) {\
        std::cout << "\t"; \
    }\
    std::cout << x << std::endl;

#define TRACE_L(x,y) std::cout << x << " = " << y << std::endl;

#define TRACE_IT(x) \
    {\
        unsigned long long counter = 0; \
        for (auto& elem : (x)) { \
            std::cout << (#x) << "[" << std::to_string(counter++) << "] = "; \
            std::cout << elem << std::endl; \
        }\
    }

#define TRACE_ITL(l,x) \
    {\
        unsigned long long counter = 0; \
        for (auto& elem : (x)) { \
            std::cout << (l) << "[" << std::to_string(counter++) << "] = "; \
            std::cout << elem << std::endl; \
        }\
    }

#define TRACE_MAP(x) \
    {\
        for (auto& pair : (x)) { \
            std::cout << (#x) << "[" << pair.first << "] = "; \
            std::cout << pair.second << std::endl; \
        }\
    }

#define TRACE_MAPL(l,x) \
    {\
        for (auto& pair : (x)) { \
            std::cout << (l) << "[" << pair.first << "] = "; \
            std::cout << pair.second << std::endl; \
        }\
    }

#define TRACE_PAIR(x) \
    std::cout << (#x) << " = {" << x.first << ", "; \
    std::cout << x.second << "}" << std::endl;

#define TRACE_PAIRL(l,x) \
    std::cout << (l) << " = {" << x.first << ", "; \
    std::cout << x.second << "}" << std::endl;

#define BLANK std::cout << std::endl;

#endif
