#ifndef MATHXX_MATRIX_STACK_MATRIX_HPP_INCLUDED
#define MATHXX_MATRIX_STACK_MATRIX_HPP_INCLUDED

#include <cstddef>
#include <iosfwd>

namespace mathxx {
    namespace matrix {

        template <typename T, std::size_t ROWS, std::size_t COLS>
        class stack_matrix {
            public:
                typedef T value_type;
                typedef T& reference;
                typedef T const& const_reference;
                typedef T* pointer;
                typedef T const* const_pointer;
                typedef stack_matrix<T, ROWS, COLS> self;

                typedef pointer iterator;
                typedef const_pointer const_iterator;
            public:
                explicit stack_matrix(T const &value = T(0));
                virtual ~stack_matrix();

                std::size_t rows() const { return ROWS; }
                std::size_t columns() const { return COLS; }

                reference operator() (std::size_t i, std::size_t j) {
                    return _M_data[i * columns() + j];
                }

                const_reference operator() (std::size_t i, std::size_t j) const {
                    return _M_data[i * columns() + j];
                }

                iterator begin() { return &_M_data[0]; }
                iterator end() { return &_M_data[0] + rows() * columns();}

                const_iterator begin() const { return &_M_data[0]; }
                const_iterator end() const { return &_M_data[0] + rows() * columns();}

                self& operator += (self const&);
                self& operator -= (self const&);
                self& operator *= (T const&);
                self& operator /= (T const&);

                self operator + (self const&) const;
                self operator - (self const&) const;
                self operator * (T const&) const;
                self operator / (T const&) const;

                template <std::size_t C>
                stack_matrix<T, ROWS, C> operator * (stack_matrix<T, COLS, C> const&);
            protected:
            private:
                T _M_data[ROWS * COLS < 1 ? 1: ROWS * COLS];
        };

        template <typename T, std::size_t R, std::size_t C>
        stack_matrix<T, R, C> operator * (T const &value, stack_matrix<T, R, C> const &mat) {
            return mat.operator*(value);
        }

        template <typename T, std::size_t R, std::size_t C>
        extern std::ostream& operator << (std::ostream&, stack_matrix<T, R, C> const&);
    }
}

#include "stack_matrix.tcc"

#endif // MATHXX_MATRIX_STACK_MATRIX_HPP_INCLUDED
