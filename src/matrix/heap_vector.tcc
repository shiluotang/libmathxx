#include <algorithm>
#include <functional>
#include <stdexcept>
#include <ostream>

#include "../misc/utility.hpp"
#include "heap_vector.hpp"

namespace mathxx {
    namespace matrix {

        template <typename T, typename A>
        heap_vector<T, A>::heap_vector(std::size_t size, T const &value) {
            _M_size = size;
            _M_data.resize(size);
            std::fill(begin(), end(), value);
        }

        template <typename T, typename A>
        heap_vector<T, A>::~heap_vector() {
        }

        template <typename T, typename A>
        heap_vector<T, A>& heap_vector<T, A>::resize(std::size_t sz) {
            if (_M_size != sz)
                _M_data.resize(sz);
            return *this;
        }

        template <typename T, typename A>
        heap_vector<T, A>&
        heap_vector<T, A>::operator += (heap_vector<T, A> const &other) {
            if (!same_size(other))
                throw std::runtime_error("size mismatch!");
            std::transform(begin(), end(), other.begin(), begin(), std::plus<T>());
            return *this;
        }

        template <typename T, typename A>
        heap_vector<T, A>&
        heap_vector<T, A>::operator -= (heap_vector<T, A> const &other) {
            if (!same_size())
                throw std::runtime_error("size mismatch!");
            std::transform(begin(), end(), other.begin(), begin(), std::minus<T>());
            return *this;
        }

        template <typename T, typename A>
        heap_vector<T, A>&
        heap_vector<T, A>::operator *= (T const &value) {
            std::transform(begin(), end(), begin(), mathxx::misc::multiplier<T>(value));
            return *this;
        }

        template <typename T, typename A>
        heap_vector<T, A>&
        heap_vector<T, A>::operator /= (T const &value) {
            std::transform(begin(), end(), begin(), mathxx::misc::divider<T>(value));
            return *this;
        }

        template <typename T, typename A>
        heap_vector<T, A>
        heap_vector<T, A>::operator + (heap_vector<T, A> const &other) const {
            heap_vector<T, A> result(*this);
            result += other;
            return result;
        }

        template <typename T, typename A>
        heap_vector<T, A>
        heap_vector<T, A>::operator - (heap_vector<T, A> const &other) const {
            heap_vector<T, A> result(*this);
            result -= other;
            return result;
        }

        template <typename T, typename A>
        heap_vector<T, A>
        heap_vector<T, A>::operator * (T const &value) const {
            heap_vector<T, A> result(*this);
            result *= value;
            return result;
        }

        template <typename T, typename A>
        heap_vector<T, A>
        heap_vector<T, A>::operator / (T const &value) const {
            heap_vector<T, A> result(*this);
            result /= value;
            return result;
        }

        template <typename T, typename A>
        T heap_vector<T, A>::operator * (heap_vector<T, A> const &other) const {
            T sum(0);
            for (const_iterator it1 = begin(), e = end(),
                    it2 = other.begin(); it1 != e; ++it1, ++it2)
                sum += *it1 * *it2;
            return sum;
        }

        template <typename T, typename A>
        std::ostream& operator << (std::ostream &os, heap_vector<T, A> const &v) {
            os << "[";
            if (v.size() > 0) {
                os << v[0];
                for (std::size_t i = 1, n = v.size(); i < n; ++i)
                    os << ", " << v[i];
            }
            os << "]";
            return os;
        }
    }
}

