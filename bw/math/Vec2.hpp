#pragma once

namespace bw
{
    ///
    /// @class Vec2
    /// @brief 2D Vector template class with common Vector operations
    /// 
    /// This class represents a 2-dimensional Vector with multiple component naming options:
    /// - (x,y) for standard coordinates
    /// - (r,g) for color operations
    /// - (s,t) for texture coordinates
    ///
    /// Provides basic Vector math operations and utility functions.
    ///
    /// @tparam T Type of vector components
    /// 
    template <typename T>
    class Vec2
    {
    public:
        union 
        {
            T x, r, s, width;
        };

        union 
        {
            T y, g, t, height;
        };
        
        Vec2(T x, T y) : x(x), y(y) { }
        Vec2() : Vec2(T{}, T{}) { }
        
        Vec2(const Vec2& v) : x(v.x), y(v.y) { }
        Vec2(Vec2&& moved) noexcept;

        template <typename U>
        Vec2(const Vec2<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

        template <typename U>
        Vec2(Vec2<U>&& moved);

        Vec2& operator=(const Vec2& other);
        Vec2& operator=(Vec2&& moved) noexcept;

        bool operator==(const Vec2& other) const;
        bool operator!=(const Vec2& other) const;

        Vec2 operator+(const Vec2& other);
        Vec2 operator-(const Vec2& other);
        Vec2 operator*(const Vec2& other);
        Vec2 operator/(const Vec2& other);

        Vec2 operator+(const T& scalar);
        Vec2 operator-(const T& scalar);
        Vec2 operator*(const T& scalar);
        Vec2 operator/(const T& scalar);

        /// @brief Returns zero-initialized Vector (0,0)
        static Vec2 zero();

        /// @brief Returns a Vector initialized with a unit (1,1)
        static Vec2 one();

        /// @brief Returns a Vector length
        T length() const;

        /// @brief Returns normalized (unit) Vector
        Vec2 normalized();
    };
    
    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;
    using Vec2d = Vec2<double>;
}

#include "Vec2.tpp"
