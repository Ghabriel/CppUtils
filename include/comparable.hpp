/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef COMPARABLE_HPP
#define COMPARABLE_HPP

namespace utils {
    template<typename T>
    class comparable {
    public:
        bool operator<(const T& other) const { return cast() < other; }
        bool operator>(const T& other) const { return other < cast(); }
        bool operator<=(const T& other) const { return !(other < cast()); }
        bool operator>=(const T& other) const { return !(*this < other); }
        bool operator==(const T& other) const {
            return *this <= other && *this >= other;
        }

        bool operator!=(const T& other) const {
            return *this < other || other < cast();
        }

    private:
        const T& cast() const {
            return *static_cast<const T*>(this);
        }
    };
}

#endif
