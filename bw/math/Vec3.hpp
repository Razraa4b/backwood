#pragma once

namespace bw
{    
    ///
    /// @class Vec3
    /// @brief 3D Vector template class with common Vector operations
    /// 
    /// This class represents a 3-dimensional Vector with multiple component naming options:
    /// - (x,y,z) for standard coordinates
    /// - (r,g,b) for color operations
    /// - (s,t,p) for texture coordinates
    /// 
    /// Provides complete 3D Vector math operations and utility functions.
    /// All operations are component-wise unless otherwise noted.
    ///
    /// @tparam T Type of vector components
    /// 
    template <typename T>
    class Vec3
    {
    public:
        union 
        {
            T x, r, s;
        };

        union 
        {
            T y, g, t;
        };

        union 
        {
            T z, b, p;
        };
        
        Vec3(T x, T y, T z) : x(x), y(y), z(z) { }
        Vec3() : Vec3(T{}, T{}, T{}) { }
        
        Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) { }
        Vec3(Vec3&& moved) noexcept;

        template <typename U>
        Vec3(const Vec3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}

        template <typename U>
        Vec3(Vec3<U>&& moved);

        Vec3& operator=(const Vec3& other);
        Vec3& operator=(Vec3&& moved);

        constexpr bool operator==(const Vec3& other) const;
        constexpr bool operator!=(const Vec3& other) const;

        constexpr Vec3 operator+(const Vec3& other) const;
        constexpr Vec3 operator-(const Vec3& other) const;
        constexpr Vec3 operator*(const Vec3& other) const;
        constexpr Vec3 operator/(const Vec3& other) const;

        constexpr Vec3 operator+(const T& scalar) const;
        constexpr Vec3 operator-(const T& scalar) const;
        constexpr Vec3 operator*(const T& scalar) const;
        constexpr Vec3 operator/(const T& scalar) const;

        /// @brief Returns zero-initialized Vector (0,0,0)
        static Vec3 zero();

        /// @brief Returns a Vector initialized with a unit (1,1,1)
        static Vec3 one();

        /// @brief Returns a Vector length
        constexpr T length() const;

        /// @brief Returns normalized (unit) Vector
        constexpr Vec3 normalized() const;
    };
    
    using Vec3i = Vec3<int>;
    using Vec3f = Vec3<float>;
    using Vec3d = Vec3<double>;
}

#include "Vec3.tpp"
