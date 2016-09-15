/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace utils {
    namespace __detail {
        struct type_info {
            std::vector<std::string> baseName;
            bool isPointer = false;
            size_t arraySize = 0;
            bool isConst = false;
            bool isVolatile = false;
            std::vector<type_info> templateTypes;
        };

        const std::unordered_map<char, std::string> baseTypes = {
            {'b', "bool"},
            {'c', "char"},
            {'d', "double"},
            {'e', "long double"},
            {'f', "float"},
            {'h', "unsigned char"},
            {'i', "int"},
            {'j', "unsigned int"},
            {'l', "long"},
            {'m', "unsigned long"},
            {'n', "nullptr_t"},
            {'s', "short"},
            {'t', "unsigned short"},
            {'v', "void"},
            {'w', "wchar_t"},
            {'x', "long long"},
            {'y', "unsigned long long"}
        };

        size_t catchNumber(const std::string&, size_t&);
        std::string capture(const std::string&, size_t&);
        type_info stringToType(const std::string&, size_t = 0);
        std::string typeToString(const type_info&);

        // type_info typeFromString(const std::string&);
        // std::vector<type_info> typeStringToVector(const std::string&);
        // type_info typeFromString(const std::string&);
        // std::string infoToString(const type_info&);
    }

    template<typename T>
    std::string type(const T& t) {
        return __detail::typeToString(__detail::stringToType(typeid(t).name()));
    }
}

#endif
