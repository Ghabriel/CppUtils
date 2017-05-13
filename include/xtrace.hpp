/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2017] */
#ifndef UTILS_XTRACE_HPP
#define UTILS_XTRACE_HPP

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>
#include <type_traits>
#include <vector>

#if ALLOW_DEBUG_USAGE == 1

namespace detail {
    template<int P> struct priority : public priority<P-1> {};
    template<> struct priority<0> {};

    class XTraceFormatter {
     public:
        static XTraceFormatter instance() {
            static XTraceFormatter inst;
            return inst;
        }

        std::string operator()(bool) const;
        std::string operator()(char) const;
        std::string operator()(const char*) const;
        std::string operator()(const std::string&) const;
        template<typename T>
        std::string operator()(T* const) const;
        template<typename T>
        std::string operator()(const std::unique_ptr<T>&) const;
        template<typename T>
        std::string operator()(const std::shared_ptr<T>&) const;
        template<typename T>
        std::string operator()(const std::reference_wrapper<T>&) const;
        template<typename T>
        std::string operator()(const T&) const;
        template<typename T>
        std::string operator()(const std::vector<T>& vector) const;
        template<typename T1, typename T2>
        std::string operator()(const std::pair<T1, T2>& pair) const;
        template<typename... Types>
        std::string operator()(const std::tuple<Types...>& tuple) const;

     private:
        XTraceFormatter() = default;

        template<typename T,
            typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
        std::string generic(const T& value, priority<1>) const {
            return std::to_string(value);
        }

        template<typename T>
        std::string generic(const T& value, priority<0>) const {
            std::stringstream ss;
            ss << "UNPRINTABLE (typeid: ";
            ss << typeid(value).name();
            ss << ")";
            return ss.str();
        }

        template<typename T>
        std::string construct(const T&) const;

        template<typename T, typename... Args>
        std::string construct(const T&, Args&&...) const;

        template<typename... Types, size_t... I>
        std::string extract(const std::tuple<Types...>&, std::index_sequence<I...>) const;
    };

    template<typename T>
    inline std::string XTraceFormatter::operator()(T* const value) const {
        std::stringstream ss;
        ss << static_cast<void*>(value);
        return ss.str() + ", points to: " + (*this)(*value);
    }

    template<typename T>
    inline std::string XTraceFormatter::operator()(const std::unique_ptr<T>& value) const {
        return (*this)(value.get());
    }

    template<typename T>
    inline std::string XTraceFormatter::operator()(const std::shared_ptr<T>& value) const {
        return (*this)(value.get());
    }

    template<typename T>
    std::string XTraceFormatter::operator()(const std::reference_wrapper<T>& value) const {
        return (*this)(value.get());
    }

    inline std::string XTraceFormatter::operator()(bool value) const {
        return value ? "true" : "false";
    }

    inline std::string XTraceFormatter::operator()(char value) const {
        return std::string(1, value);
    }

    inline std::string XTraceFormatter::operator()(const char* value) const {
        std::stringstream ss;
        ss << '"' << value << '"';
        return ss.str();
    }

    inline std::string XTraceFormatter::operator()(const std::string& value) const {
        return (*this)(value.c_str());
    }

    template<typename T>
    inline std::string XTraceFormatter::operator()(const T& value) const {
        return generic(value, priority<1>{});
    }

    template<typename T>
    inline std::string XTraceFormatter::operator()(const std::vector<T>& vector) const {
        std::stringstream ss;
        ss << "{";
        bool first = true;
        for (auto& value : vector) {
            if (!first) {
                ss << ", ";
            }
            ss << (*this)(value);
            first = false;
        }
        ss << "}";
        return ss.str();
    }

    template<typename T1, typename T2>
    inline std::string XTraceFormatter::operator()(const std::pair<T1, T2>& pair) const {
        return '{' + (*this)(pair.first) + ", " + (*this)(pair.second) + '}';
    }

    template<typename... Types>
    inline std::string XTraceFormatter::operator()(const std::tuple<Types...>& tuple) const {
        return '{' +
                extract(tuple, std::make_index_sequence<sizeof...(Types)>())
                + '}';
    }

    template<typename T>
    inline std::string XTraceFormatter::construct(const T& value) const {
        return (*this)(value);
    }

    template<typename T, typename... Args>
    inline std::string XTraceFormatter::construct(const T& value, Args&&... args) const {
        return (*this)(value) + ", " + construct(std::forward<Args>(args)...);
    }

    template<typename... Types, size_t... I>
    inline std::string XTraceFormatter::extract(const std::tuple<Types...>& tuple,
        std::index_sequence<I...>) const {

        return construct(std::get<I>(tuple)...);
    }

    const auto xTraceFormatter = XTraceFormatter::instance();
}

#define XTRACE(x) trace((#x), (x), detail::xTraceFormatter)

#else

#define XTRACE(...) {int debug_usage;}

#endif

#endif
