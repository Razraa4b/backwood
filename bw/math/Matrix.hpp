#pragma once

#include <ostream>
#include <array>
#include <vector>
#include <memory>
#include <concepts>
#include "Vec3.hpp"

namespace bw
{
    ///
    /// @class Matrix
    /// @brief Template class representing a mathematical matrix with R rows and C columns of type T
    /// 
    /// @tparam R Number of rows (compile-time constant)
    /// @tparam C Number of columns (compile-time constant)
    /// @tparam T Data type of matrix elements
    ///
    template<size_t R, size_t C, typename T>
    class Matrix
    {
    public:
        // Constructors

        /// @brief Creates zero-initialized matrix
        Matrix();

        /// @brief Construct from 2D raw pointer array
        Matrix(T** initializer);

        /// @brief Construct from array of arrays
        Matrix(const std::array<std::array<T, C>, R>& data);

        /// @brief Construct from vector of vectors
        Matrix(const std::vector<std::vector<T>>& initializer);

        Matrix(const Matrix& other);
        Matrix(Matrix&& moved) noexcept = default;

        ~Matrix() = default;

        template <typename U>
        explicit operator Matrix<R, C, U>() const;

        // Access operators
        T& operator()(size_t row, size_t col);
        const T& operator()(size_t row, size_t col) const;

        T* operator[](size_t row);
        const T* operator[](size_t row) const;

        bool operator==(const Matrix& other) const;
        bool operator!=(const Matrix& other) const;

        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& moved) noexcept = default;

        Matrix operator+(const Matrix& other) const;
        Matrix operator-(const Matrix& other) const;

        template<size_t Arg_C>
        Matrix<R, Arg_C, T> operator*(const Matrix<C, Arg_C, T>& other) const;

        Matrix operator*(T scalar) const;

        /// @brief Convert matrix to 1D array (row-major order)
        std::array<T, C* R> toLinearArray() const;

        /// @brief Fill matrix with specified value
        void fill(T value);

        void translate(Vec3<T> position) requires std::is_floating_point_v<T> && (R == 4) && (C == 4);
        
        size_t rows() const { return R; }
        size_t cols() const { return C; }

    private:
        std::unique_ptr<T[]> _data; // 1D array storing matrix data (row-major)

        size_t _getIndex(size_t row, size_t col) const;
        void _copyFrom(const Matrix& other);
    };

    template<typename T>
    using Matrix2x2 = Matrix<2, 2, T>;
    template<typename T>
    using Matrix3x3 = Matrix<3, 3, T>;
    template<typename T>
    using Matrix4x4 = Matrix<4, 4, T>;
}

#include "Matrix.tpp"
