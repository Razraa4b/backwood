#pragma once

namespace bw
{
    ///
    /// @class Vec4
    /// @brief 4D Vector template class with common Vector and color operations
    /// 
    /// Represents a 4-dimensional Vector with multiple component naming conventions:
    /// - (x,y,z,w) for standard homogeneous coordinates
    /// - (r,g,b,a) for color operations with alpha
    /// - (s,t,p,q) for texture coordinates
    /// 
    /// Provides complete 4D Vector math operations. All operations are
    /// component-wise unless otherwise noted. Suitable for graphics,
    /// physics, and general mathematical computations.
    /// 
    /// @tparam T Type of vector components
    ///
    template <typename T>
    class Vec4
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

        union 
        {
            T w, a, q;
        };
        
        Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
        Vec4() : Vec4(T{}, T{}, T{}, T{}) { }
        
        Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
        Vec4(Vec4&& v) noexcept;

        template <typename U>
        Vec4(const Vec4<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {}

        template <typename U>
        Vec4(Vec4<U>&& moved);

        Vec4& operator=(const Vec4& v);
        Vec4& operator=(Vec4&& v);

        constexpr bool operator==(const Vec4& v) const;
        constexpr bool operator!=(const Vec4& v) const;

        constexpr Vec4 operator+(const Vec4& v) const;
        constexpr Vec4 operator-(const Vec4& v) const;
        constexpr Vec4 operator*(const Vec4& v) const;
        constexpr Vec4 operator/(const Vec4& v) const;

        constexpr Vec4 operator+(const T& scalar) const;
        constexpr Vec4 operator-(const T& scalar) const;
        constexpr Vec4 operator*(const T& scalar) const;
        constexpr Vec4 operator/(const T& scalar) const;

        /// @brief Returns zero-initialized Vector (0,0,0,0)
        static Vec4 zero();
        
        /// @brief Returns a Vector initialized with a unit (1,1,1,1)
        static Vec4 one();

        /// @brief Returns a Vector length
        constexpr T length() const;

        /// @brief Returns normalized (unit) Vector
        constexpr Vec4 normalized() const;
    };
    
    using Vec4i = Vec4<int>;
    using Vec4f = Vec4<float>;
    using Vec4d = Vec4<double>;
}

#include "Vec4.tpp"
