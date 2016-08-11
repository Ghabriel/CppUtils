#ifndef UTILS_MACROS_HPP
#define UTILS_MACROS_HPP

#define TRACE(x) std::cout << (#x) << " = " << (x) << std::endl
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
#define ECHO(x) std::cout << (x) << std::endl
#define ECHOI(x,numTabs) \
    for (unsigned i = 0; i < numTabs; i++) {\
        std::cout << "\t"; \
    }\
    ECHO(x)

#endif
