/* created by Ghabriel Nunes <ghabriel.nunes@gmail.com> [2016] */
#ifndef AMOUNT_HPP
#define AMOUNT_HPP

#include "comparable.hpp"

namespace utils {
    template<int M, int L, int T>
    struct amount : public comparable<amount<M,L,T>> {
        constexpr amount(); // declared to allow decltype(amount()) only
        amount(double v) : value(v) {}
        double value;
    };

    template<int M, int L, int T>
    bool operator<(const amount<M,L,T>& lhs, const amount<M,L,T>& rhs) {
        return lhs.value < rhs.value;
    }

    template<int M, int L, int T>
    amount<M,L,T> operator+(const amount<M,L,T>& lhs, const amount<M,L,T>& rhs) {
        return {lhs.value + rhs.value};
    }

    template<int M, int L, int T>
    amount<M,L,T> operator-(const amount<M,L,T>& lhs, const amount<M,L,T>& rhs) {
        return {lhs.value - rhs.value};
    }

    template<int M, int L, int T>
    amount<M,L,T> operator*(double v, const amount<M,L,T>& rhs) {
        return {v * rhs.value};
    }

    template<int M, int L, int T>
    amount<-M,-L,-T> operator/(double v, const amount<M,L,T>& rhs) {
        return {v / rhs.value};
    }

    template<int M, int L, int T>
    amount<M,L,T> operator*(const amount<M,L,T>& lhs, double v) {
        return {lhs.value * v};
    }

    template<int M, int L, int T>
    amount<M,L,T> operator/(const amount<M,L,T>& lhs, double v) {
        return {lhs.value / v};
    }

    template<int M1, int L1, int T1, int M2, int L2, int T2>
    amount<M1+M2, L1+L2, T1+T2>
    operator*(const amount<M1,L1,T1>& lhs, const amount<M2,L2,T2>& rhs) {
        return {lhs.value * rhs.value};
    }

    template<int M1, int L1, int T1, int M2, int L2, int T2>
    amount<M1-M2, L1-L2, T1-T2>
    operator/(const amount<M1,L1,T1>& lhs, const amount<M2,L2,T2>& rhs) {
        return {lhs.value / rhs.value};
    }

    using Mass = amount<1, 0, 0>;
    using Length = amount<0, 1, 0>;
    using Time = amount<0, 0, 1>;

    using Area = decltype(Length() * Length());
    using Volume = decltype(Area() * Length());
    using Speed = decltype(Length() / Time());
    using Acceleration = decltype(Speed() / Time());
    using Frequency = decltype(1 / Time());
    using Force = decltype(Mass() * Acceleration());
    using Pressure = decltype(Force() / Area());

    using Kilogram = Mass;
    using Meter = Length;
    using Second = Time;
    using Hertz = Frequency;
    using Newton = Force;
    using Minute = decltype(60 * Second());
    using Hour = decltype(60 * Minute());
    using Day = decltype(24 * Hour());
};

utils::Kilogram operator"" _kg(long double v) { return v; }
utils::Kilogram operator"" _kg(unsigned long long v) { return v; }
utils::Meter operator"" _m(long double v) { return v; }
utils::Meter operator"" _m(unsigned long long v) { return v; }
utils::Area operator"" _m2(long double v) { return v; }
utils::Area operator"" _m2(unsigned long long v) { return v; }
utils::Volume operator"" _m3(long double v) { return v; }
utils::Volume operator"" _m3(unsigned long long v) { return v; }
utils::Second operator"" _s(long double v) { return v; }
utils::Second operator"" _s(unsigned long long v) { return v; }
utils::Minute operator"" _min(long double v) { return v; }
utils::Minute operator"" _min(unsigned long long v) { return v; }
utils::Hour operator"" _h(long double v) { return v; }
utils::Hour operator"" _h(unsigned long long v) { return v; }
utils::Newton operator"" _N(long double v) { return v; }
utils::Newton operator"" _N(unsigned long long v) { return v; }
utils::Hertz operator"" _Hz(long double v) { return v; }
utils::Hertz operator"" _Hz(unsigned long long v) { return v; }

#endif
