#ifndef MATHXX_MATRIX_HEAP_VECTOR_HPP_INCLUDED
#define MATHXX_MATRIX_HEAP_VECTOR_HPP_INCLUDED

#include <vector>

namespace mathxx {
    namespace matrix {

        template <typename T, Alloc = std::allocator<T> >
        class vector {
            public:
                typedef std::vector<T, Alloc> container_type;
                typedef typename container_type::value_type value_type;
                typedef typename container_type::reference reference;
                typedef typename container_type::const_reference const_reference;
                typedef typename container_type::pointer pointer;
                typedef typename container_type::const_pointer const_pointer;
                typedef pointer iterator;
                typedef const_pointer const_iterator;
                typedef vector<T, Alloc> self;
            public:
                explicit vector(std::size_t, T const &value = T(0));
                virtual ~vector();

                iterator begin() { return &_M_data[0]; }
                iterator end() { return &_M_data[0]; }

                const_iterator begin() const { return &_M_data[0]; }
                const_iterator end() const { return &_M_data[0] + _M_size; }

                std::size_t size() const { return _M_size; }
                vector& resize(std::size_t);

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
            private:
                std::size_t _M_size;
                container_type _M_data;
        };
    }
}

#include "vector.tcc"

#endif // MATHXX_MATRIX_HEAP_VECTOR_HPP_INCLUDED
