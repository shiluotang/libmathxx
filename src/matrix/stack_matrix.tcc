#include <algorithm>
#include <functional>
#include <ostream>

#include "../misc/utility.hpp"
#include "stack_matrix.thh"

namespace mathxx {
    namespace matrix {

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>::stack_matrix(T const &value) {
            std::fill(begin(), end(), value);
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>::~stack_matrix() {
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>&
        stack_matrix<T, R, C>::operator += (stack_matrix<T, R, C> const &other) {
            std::transform(begin(), end(), other.begin(), begin(), std::plus<T>());
            return *this;
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>&
        stack_matrix<T, R, C>::operator -= (stack_matrix<T, R, C> const &other) {
            std::transform(begin(), end(), other.begin(), begin(), std::minus<T>());
            return *this;
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>&
        stack_matrix<T, R, C>::operator *= (T const &value) {
            std::transform(begin(), end(), begin(), mathxx::misc::multiplier<T>(value));
            return *this;
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>&
        stack_matrix<T, R, C>::operator /= (T const &value) {
            std::transform(begin(), end(), begin(), mathxx::misc::divider<T>(value));
            return *this;
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>
        stack_matrix<T, R, C>::operator + (stack_matrix<T, R, C> const &other) const {
            stack_matrix<T, R, C> result(*this);
            result += other;
            return result;
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>
        stack_matrix<T, R, C>::operator - (stack_matrix<T, R, C> const &other) const {
            stack_matrix<T, R, C> result(*this);
            result -= other;
            return result;
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>
        stack_matrix<T, R, C>::operator * (T const &value) const {
            stack_matrix<T, R, C> result(*this);
            result *= value;
            return result;
        }

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C>
        stack_matrix<T, R, C>::operator / (T const &value) const {
            stack_matrix<T, R, C> result(*this);
            result /= value;
            return result;
        }

        template <typename T, std::size_t R1, std::size_t C1>
        template <std::size_t C2>
        stack_matrix<T, R1, C2>
        stack_matrix<T, R1, C1>::operator * (stack_matrix<T, C1, C2> const &other) {
            stack_matrix<T, R1, C2> result(T(0));
            for (std::size_t i = 0, n = rows(); i < n; ++i) {
                for (std::size_t j = 0, m = other.columns(); j < m; ++j) {
                    for (std::size_t k = 0, l = columns(); k < l; ++k) {
                        result(i, j) += this->operator()(i, k) * other(k, j);
                    }
                }
            }
            return result;
        }

        template <typename T, std::size_t R, std::size_t C>
        std::ostream& operator << (std::ostream &os, stack_matrix<T, R, C> const &mat) {
            os << "[";
            if (mat.rows() > 0 && mat.columns() > 0) {
                os << "[" << mat(0, 0);
                for (std::size_t i = 1, n = mat.columns(); i < n; ++i)
                    os << ", " << mat(0, i);
                os << "]";
                for (std::size_t i = 1, n = mat.rows(); i < n; ++i) {
                    os << ", [" << mat(i, 0);
                    for (std::size_t j = 1, m = mat.columns(); j < m; ++j) {
                        os << ", " << mat(i, j);
                    }
                    os << "]";
                }
            }
            os << "]";
            return os;
        }
    }
}
