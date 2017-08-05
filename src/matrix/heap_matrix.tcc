#include <cstddef>
#include <ostream>
#include <algorithm>
#include <functional>

#include "../misc/utility.hpp"
#include "heap_matrix.hpp"

namespace mathxx {
    namespace matrix {
        template <typename T, typename Alloc>
        heap_matrix<T, Alloc>::heap_matrix(std::size_t rows, std::size_t columns, T const &value)
            : _M_rows(rows) , _M_columns(columns) {
            _M_data.resize(rows * columns);
            std::fill(_M_data.begin(), _M_data.end(), value);
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc>::~heap_matrix() {
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc>& heap_matrix<T, Alloc>::operator += (heap_matrix<T, Alloc> const &other) {
            if (!same_size(other))
                throw std::runtime_error("size mismatch!");
            std::transform(begin(), end(), other.begin(), begin(), std::plus<T>());
            return *this;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc>& heap_matrix<T, Alloc>::operator -= (heap_matrix<T, Alloc> const &other) {
            if (!same_size(other))
                throw std::runtime_error("size mismatch!");
            std::transform(begin(), end(), other.begin(), begin(), std::minus<T>());
            return *this;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc>& heap_matrix<T, Alloc>::operator *= (T const &value) {
            std::transform(begin(), end(), begin(), mathxx::misc::multiplier<T>(value));
            return *this;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc>& heap_matrix<T, Alloc>::operator /= (T const &value) {
            std::transform(begin(), end(), begin(), mathxx::misc::divider<T>(value));
            return *this;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc> heap_matrix<T, Alloc>::operator + (heap_matrix<T, Alloc> const &other) const {
            if (!same_size(other))
                throw std::runtime_error("size mismatch!");
            heap_matrix<T, Alloc> result(*this);
            result += other;
            return result;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc> heap_matrix<T, Alloc>::operator - (heap_matrix<T, Alloc> const &other) const {
            if (!same_size(other))
                throw std::runtime_error("size mismatch!");
            heap_matrix<T, Alloc> result(*this);
            result -= other;
            return result;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc> heap_matrix<T, Alloc>::operator * (T const &value) const {
            heap_matrix<T, Alloc> result(*this);
            result *= value;
            return result;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc> heap_matrix<T, Alloc>::operator / (T const &value) const {
            heap_matrix<T, Alloc> result(*this);
            result /= value;
            return result;
        }

        template <typename T, typename Alloc>
        heap_matrix<T, Alloc>& heap_matrix<T, Alloc>::resize(std::size_t r, std::size_t c) {
            if (r == rows() && c == columns())
                return *this;
            if (r * c != rows() * columns())
                _M_data.resize(r * c);
            _M_rows = r;
            _M_columns = c;
            return *this;
        }

        template <typename T, typename Alloc>
        std::ostream& operator << (std::ostream &os, heap_matrix<T, Alloc> const &matrix) {
            os << "[";
            if (matrix.rows() > 0 && matrix.columns() > 0) {
                os << "[" << matrix(0, 0);
                for (std::size_t i = 1, n = matrix.columns(); i < n; ++i)
                    os << ", " << matrix(0, i);
                os << "]";
                for (std::size_t i = 1, n = matrix.rows(); i < n; ++i) {
                    os << ", [" << matrix(i, 0);
                    for (std::size_t j = 1, m = matrix.columns(); j < m; ++j)
                        os << ", " << matrix(i, j);
                    os << "]";
                }
            }
            os << "]";
            return os;
        }
    }
}
