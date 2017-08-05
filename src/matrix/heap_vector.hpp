#ifndef MATHXX_MATRIX_HEAP_VECTOR_HPP_INCLUDED
#define MATHXX_MATRIX_HEAP_VECTOR_HPP_INCLUDED

#include <vector>

namespace mathxx {
    namespace matrix {

        template <typename T, typename Alloc = std::allocator<T> >
        class heap_vector {
            public:
                typedef std::vector<T, Alloc> container_type;
                typedef typename container_type::value_type value_type;
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;
                typedef pointer iterator;
                typedef const_pointer const_iterator;
                typedef Alloc allocator_type;
                typedef heap_vector<T, Alloc> self;
            public:
                explicit heap_vector(std::size_t, T const &value = T(0));
                virtual ~heap_vector();

                iterator begin() { return &_M_data[0]; }
                iterator end() { return &_M_data[0] + _M_size; }

                const_iterator begin() const { return &_M_data[0]; }
                const_iterator end() const { return &_M_data[0] + _M_size; }

                reference operator[] (std::size_t i) { return _M_data[i]; }
                const_reference operator[] (std::size_t i) const { return _M_data[i]; }

                std::size_t size() const { return _M_size; }
                heap_vector& resize(std::size_t);

                self& operator += (self const&);
                self& operator -= (self const&);
                self& operator *= (T const&);
                self& operator /= (T const&);

                self operator + (self const&) const;
                self operator - (self const&) const;
                self operator * (T const&) const;
                self operator / (T const&) const;

                T operator * (self const&) const;
            protected:
                bool same_size(self const &other) const {
                    return size() == other.size();
                }
            private:
                std::size_t _M_size;
                container_type _M_data;
        };

        template <typename T, typename A>
        T operator * (T const &value, heap_vector<T, A> const &v) {
            return v * value;
        }

        template <typename T, typename A>
        extern std::ostream& operator << (std::ostream&, heap_vector<T, A> const&);
    }
}

#include "heap_vector.tcc"

#endif // MATHXX_MATRIX_HEAP_VECTOR_HPP_INCLUDED
