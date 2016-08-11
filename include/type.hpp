#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <typeinfo>
#include <vector>

namespace utils {
    namespace __detail {
        struct type_info {
            std::string baseName;
            std::size_t numPointers = 0;
            std::size_t arraySize = 0;
            bool isConst = false;
            bool isVolatile = false;
            std::vector<type_info> templateTypes;
        };

        type_info typeFromString(const std::string&);
        std::vector<type_info> typeStringToVector(const std::string&);
        type_info typeFromString(const std::string&);
        std::string infoToString(const type_info&);
    }

    template<typename T>
    std::string type(const T& t) {
        return __detail::infoToString(__detail::typeFromString(typeid(t).name()));
    }
}

#endif
