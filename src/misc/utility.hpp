#ifndef LIBMATHXX_MATRIX_UTILS_HPP_INCLUDED
#define LIBMATHXX_MATRIX_UTILS_HPP_INCLUDED

#include <cstddef>
#include <sstream>
#include <algorithm>
#include <functional>

namespace mathxx {
    namespace misc {

        template <typename T, std::size_t N>
        std::size_t countof(T (&a)[N]) { return N; }

        template <typename U, typename V>
        U sstream_cast(V const &v) {
            U u;
            std::stringstream ss;
            ss << v;
            ss >> u;
            return u;
        }

        template <typename T>
        struct multiplier : std::unary_function<T, T> {
            multiplier(T const &value) :_M_value(value) { }
            ~multiplier() {}

            T operator () (T const &value) const { return value * _M_value; }

            T const _M_value;
        };

        template <typename T>
        struct divider: std::unary_function<T, T> {
            divider(T const &value) :_M_value(1 / value) {}
            ~divider() {}

            T operator () (T const &value) const { return value * _M_value; }

            T const _M_value;
        };
    }
}

#endif // LIBMATHXX_MATRIX_UTILS_HPP_INCLUDED
