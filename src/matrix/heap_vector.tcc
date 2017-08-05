#include <algorithm>

#include "heap_vector.hpp"

namespace mathxx {
    namespace matrix {

        template <typename T, typename A>
        vector<T, A>::vector(std::size_t size, T const &value) {
            _M_size = size;
            _M_data.resize(size);
            std::fill(begin(), end(), value);
        }

        template <typename T, typename A>
        vector<T, A>::~vector() {
        }

        template <typename T, typename A>
        vector<T, A>& vector<T, A>::resize(std::size_t sz) {
            if (_M_size != sz)
                _M_data.resize(sz);
            return *this;
        }
    }
}

