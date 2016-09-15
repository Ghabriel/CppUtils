/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */

#include <cassert>
#include "macros.hpp"
#include "type.hpp"

size_t utils::__detail::catchNumber(const std::string& content, size_t& index) {
    std::string result;
    while (content[index] >= '0' && content[index] <= '9') {
        result += content[index];
        index++;
    }
    return std::stoul(result);
}

std::string utils::__detail::capture(const std::string& content, size_t& index) {
    auto size = catchNumber(content, index);
    std::string result;
    for (size_t i = 0; i < size; i++) {
        result += content[index];
        index++;
    }
    return result;
}

utils::__detail::type_info
utils::__detail::stringToType(const std::string& content, size_t i) {
    type_info info;
    //
    while (i < content.size()) {
        char c = content[i];
        switch (c) {
            case 'N': {
                i++;
                while (content[i] >= '0' && content[i] <= '9') {
                    info.baseName.push_back(capture(content, i));
                }
                i++; // skip closing E
                break;
            }
            case 'P':
                info.isPointer = true;
                info.templateTypes.push_back(stringToType(content, i+1));
                return info;
            case 'K':
                info.isConst = true;
                i++;
                break;
            case 'V':
                info.isVolatile = true;
                i++;
                break;
            case 'A':
                i++;
                info.arraySize = catchNumber(content, i);
                i++; // skip underline
                break;
            default:
                if (c >= '0' && c <= '9') {
                    info.baseName.push_back(capture(content, i));
                } else if (c >= 'a' && c <= 'z') {
                    info.baseName.push_back(baseTypes.at(c));
                    i++;
                } else {
                    // is this possible?
                    assert(false);
                }
        }
    }
    //*/
    return info;
}

std::string utils::__detail::typeToString(const utils::__detail::type_info& info) {
    std::string str;
    if (info.isPointer) {
        return typeToString(info.templateTypes[0]) + "*";
    }

    if (info.isConst) str += "const ";
    if (info.isVolatile) str += "volatile ";
    for (size_t i = 0; i < info.baseName.size(); i++) {
        if (i > 0) {
            str += "::";
        }
        str += info.baseName[i];
    }
    if (info.templateTypes.size() > 0) {
        str += "<";
        for (size_t i = 0; i < info.templateTypes.size(); i++) {
            if (i > 0) {
                str += ", ";
            }
            str += typeToString(info.templateTypes[i]);
        }
        str += ">";
    }
    if (info.arraySize > 0) {
        str += "[" + std::to_string(info.arraySize) + "]";
    }
    return str;
}
