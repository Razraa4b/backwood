#include "Matrix.hpp"
#include <cstring>
#include <stdexcept>

#ifndef MATRIX_TPP
#define MATRIX_TPP

namespace bw
{
    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T>::Matrix()
        : _data(std::make_unique<T[]>(R * C))
    {
        fill(T{});
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T>::Matrix(T** initializer)
        : _data(std::make_unique<T[]>(R* C))
    {
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                (*this)(i, j) = initializer[i][j];
            }
        }
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T>::Matrix(const std::array<std::array<T, C>, R>& data)
        : _data(std::make_unique<T[]>(R* C))
    {
        for (int i = 0; i < R; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                (*this)(i, j) = data[i][j];
            }
        }
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T>::Matrix(const std::vector<std::vector<T>>& initializer)
        : _data(std::make_unique<T[]>(R* C))
    {
        if (initializer.size() != R)
            throw std::invalid_argument("Invalid number of rows");

        for (int i = 0; i < R; i++)
        {
            if (initializer[i].size() != C)
                throw std::invalid_argument("Invalid number of columns in row " + std::to_string(i));

            for (int j = 0; j < C; j++)
            {
                (*this)(i, j) = initializer[i][j];
            }
        }
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T>::Matrix(const Matrix<R, C, T>& other)
        : _data(std::make_unique<T[]>(R* C))
    {
        _copyFrom(other);
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    T& Matrix<R, C, T>::operator()(int row, int col)
    {
        if (row >= R || col >= C)
            throw std::out_of_range("Matrix indices out of range: [" +
                std::to_string(row) + ", " +
                std::to_string(col) + "]");
        return _data[_getIndex(row, col)];
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    const T& Matrix<R, C, T>::operator()(int row, int col) const
    {
        if (row >= R || col >= C)
            throw std::out_of_range("Matrix indices out of range: [" +
                std::to_string(row) + ", " +
                std::to_string(col) + "]");
        return _data[_getIndex(row, col)];
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    T* Matrix<R, C, T>::operator[](int row)
    {
        if (row >= R)
            throw std::out_of_range("Matrix row index out of range: " +
                std::to_string(row));
        return _data.get() + row * C;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    const T* Matrix<R, C, T>::operator[](int row) const
    {
        if (row >= R)
            throw std::out_of_range("Matrix row index out of range: " +
                std::to_string(row));
        return _data.get() + row * C;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    template<typename U>
    Matrix<R, C, T>::operator Matrix<R, C, U>() const
    {
        Matrix<R, C, U> converted;

        for (int i = 0; i < R; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                converted(i, j) = static_cast<U>((*this)(i, j));
            }
        }

        return converted;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    bool Matrix<R, C, T>::operator==(const Matrix<R, C, T>& other) const
    {
        for (int i = 0; i < R * C; ++i)
        {
            if (_data[i] != other._data[i])
                return false;
        }
        return true;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    bool Matrix<R, C, T>::operator!=(const Matrix<R, C, T>& other) const
    {
        return !(*this == other);
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T>& Matrix<R, C, T>::operator=(const Matrix<R, C, T>& other)
    {
        if (this != &other)
        {
            _copyFrom(other);
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T> Matrix<R, C, T>::operator+(const Matrix& other) const
    {
        Matrix<R, C, T> result;

        for (int i = 0; i < R * C; ++i)
        {
            result._data[i] = _data[i] + other._data[i];
        }

        return result;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T> Matrix<R, C, T>::operator-(const Matrix& other) const
    {
        Matrix<R, C, T> result;

        for (int i = 0; i < R * C; ++i)
        {
            result._data[i] = _data[i] - other._data[i];
        }

        return result;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    Matrix<R, C, T> Matrix<R, C, T>::operator*(T scalar) const
    {
        Matrix<R, C, T> result;

        for (int i = 0; i < R * C; ++i)
        {
            result._data[i] = _data[i] * scalar;
        }

        return result;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    template<int Arg_C>
    Matrix<R, Arg_C, T> Matrix<R, C, T>::operator*(const Matrix<C, Arg_C, T>& other) const
    {
        Matrix<R, Arg_C, T> result;

        for (int i = 0; i < R; i++) {
            for (int k = 0; k < Arg_C; k++) {
                T sum{};
                for (int j = 0; j < C; j++) {
                    sum += (*this)(i, j) * other(j, k);
                }
                result(i, k) = sum;
            }
        }

        return result;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    void Matrix<R, C, T>::fill(T value)
    {
        for (int i = 0; i < R * C; ++i)
        {
            _data[i] = value;
        }
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    void Matrix<R, C, T>::translate(Vec3<T> position) requires std::is_floating_point_v<T> && (R == 4) && (C == 4)
    {
        Matrix<4, 4, T> translation;

        for (int i = 0; i < 4; ++i)
            translation(i, i) = static_cast<T>(1);

        translation(0, 3) = position.x;
        translation(1, 3) = position.y;
        translation(2, 3) = position.z;

        *this = *this * translation;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    std::array<T, C * R> Matrix<R, C, T>::toLinearArray() const
    {
        std::array<T, R* C> arr;
        std::copy_n(_data.get(), R * C, arr.begin());
        return arr;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    int Matrix<R, C, T>::_getIndex(int row, int col) const
    {
        return row * C + col;
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    void Matrix<R, C, T>::_copyFrom(const Matrix& other)
    {
        if constexpr (std::is_trivially_copyable_v<T>)
        {
            std::memcpy(_data.get(), other._data.get(), R * C * sizeof(T));
        }
        else
        {
            for (int i = 0; i < R * C; ++i)
            {
                _data[i] = other._data[i];
            }
        }
    }

    ////////////////////////////////////////////////////////////

    template<int R, int C, typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<R, C, T>& matrix)
    {
        for (int i = 0; i < R; ++i)
        {
            os << "[ ";
            for (int j = 0; j < C; ++j)
            {
                os << matrix(i, j);
                if (j + 1 < C) os << ", ";
            }
            os << " ]\n";
        }
        return os;
    }
}

#endif
