/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#include <unordered_map>
#include "type.hpp"

std::vector<utils::__detail::type_info> utils::__detail::typeStringToVector(const std::string& str) {
    std::vector<__detail::type_info> result;
    std::string buffer;
    std::size_t size = str.size();
    bool completeBuffer = false;
    for (std::size_t i = 0; i < size; i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            completeBuffer = true;
            std::string temp;
            while (str[i] >= '0' && str[i] <= '9') {
                temp += str[i];
                i++;
            }
            unsigned long long size = stoull(temp);
            temp.clear();
            for (unsigned long long j = 0; j < size; j++) {
                temp += str[i];
                i++;
            }
            i--;
            buffer += std::to_string(temp.size()) + temp;
        } else if (c != 'I') {
            buffer += c;
            if (c <= 'A' || c >= 'Z') {
                completeBuffer = true;
            }
        } else {
            completeBuffer = true;
            std::size_t nestingLevel = 0;
            while (i < size && (str[i] != 'E' || nestingLevel > 1)) {
                if (str[i] == 'I') {
                    nestingLevel++;
                } else if (str[i] == 'E') {
                    nestingLevel--;
                }
                buffer += str[i];
                i++;
            }
            buffer += str[i];
        }

        if (i == size - 1 || (str[i+1] != 'I' && completeBuffer)) {
            result.push_back(typeFromString(buffer));
            buffer.clear();
            completeBuffer = false;
        }
    }
    return result;
}

utils::__detail::type_info utils::__detail::typeFromString(const std::string& baseName) {
    __detail::type_info result;
    std::unordered_map<char, std::string> baseTypes = {
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
    for (std::size_t i = 0; i < baseName.size(); i++) {
        char c = baseName[i];
        // std::cout << "[char] " << c << std::endl;
        switch (c) {
            case 'P':
                result.numPointers++;
                break;
            case 'K':
                result.isConst = true;
                break;
            case 'V':
                result.isVolatile = true;
                break;
            case 'A': {
                i++;
                std::string buffer;
                while (baseName[i] != '_') {
                    buffer += baseName[i];
                    i++;
                }
                result.arraySize = stoull(buffer);
                break;
            }
            case 'I': {
                std::size_t nestingLevel = 0;
                std::string buffer;
                i++;
                while (baseName[i] != 'E' || nestingLevel > 0) {
                    if (baseName[i] == 'I') {
                        nestingLevel++;
                    } else if (baseName[i] == 'E') {
                        nestingLevel--;
                    }
                    buffer += baseName[i];
                    i++;
                }

                auto types = typeStringToVector(buffer);
                for (__detail::type_info& type : types) {
                    result.templateTypes.push_back(std::move(type));
                }
                break;
            }
            default:
                if (c >= 'a' && c <= 'z') {
                    result.baseName = baseTypes[c];
                } else if (c >= '0' && c <= '9') {
                    std::string buffer;
                    while (baseName[i] >= '0' && baseName[i] <= '9') {
                        buffer += baseName[i];
                        i++;
                    }
                    unsigned long long size = stoull(buffer);
                    buffer.clear();
                    for (unsigned long long j = 0; j < size; j++) {
                        buffer += baseName[i];
                        i++;
                    }
                    i--;
                    result.baseName = buffer;
                }
        }
    }
    return result;
}

std::string utils::__detail::infoToString(const utils::__detail::type_info& info) {
    std::string str;
    if (info.isConst) str += "const ";
    if (info.isVolatile) str += "volatile ";
    str += info.baseName;
    if (info.templateTypes.size() > 0) {
        str += "<";
        for (std::size_t i = 0; i < info.templateTypes.size(); i++) {
            if (i > 0) {
                str += ", ";
            }
            str += infoToString(info.templateTypes[i]);
        }
        str += ">";
    }
    for (std::size_t i = 0; i < info.numPointers; i++) {
        str += "*";
    }
    if (info.arraySize > 0) {
        str += "[" + std::to_string(info.arraySize) + "]";
    }
    return str;
}
