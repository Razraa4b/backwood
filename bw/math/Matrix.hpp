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
    template<int R, int C, typename T>
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
        T& operator()(int row, int col);
        const T& operator()(int row, int col) const;

        T* operator[](int row);
        const T* operator[](int row) const;

        constexpr bool operator==(const Matrix& other) const;
        constexpr bool operator!=(const Matrix& other) const;

        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& moved) noexcept = default;

        constexpr Matrix operator+(const Matrix& other) const;
        constexpr Matrix operator-(const Matrix& other) const;

        template<int Arg_C>
        constexpr Matrix<R, Arg_C, T> operator*(const Matrix<C, Arg_C, T>& other) const;

        constexpr Matrix operator*(T scalar) const;

        /// @brief Convert matrix to 1D array (row-major order)
        constexpr std::array<T, C* R> toLinearArray() const;

        /// @brief Fill matrix with specified value
        constexpr void fill(T value);

        constexpr void translate(Vec3<T> position) requires std::is_floating_point_v<T> && (R == 4) && (C == 4);
        
        constexpr int rows() const { return R; }
        constexpr int columns() const { return C; }
    private:
        std::unique_ptr<T[]> _data; // 1D array storing matrix data (row-major)

        int _getIndex(int row, int col) const;
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
