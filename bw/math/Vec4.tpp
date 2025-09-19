#ifndef VEC4_TPP
#define VEC4_TPP

#include <memory>
#include <cmath>

namespace bw
{
    template <typename T>
    Vec4<T>::Vec4(Vec4<T>&& moved) noexcept : x(std::move(moved.x)), y(std::move(moved.y)), z(std::move(moved.z)), w(std::move(moved.w)) { }

    ////////////////////////////////////////////////////////////

    template <typename T>
    template <typename U>
    Vec4<T>::Vec4(Vec4<U>&& moved) : x(static_cast<T>(std::move(moved.x))), y(static_cast<T>(std::move(moved.y))), z(static_cast<T>(std::move(moved.z))), w(static_cast<U>(std::move(moved.w))) {}

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec4<T>& Vec4<T>::operator=(const Vec4<T>& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec4<T>& Vec4<T>::operator=(Vec4<T>&& moved)
    {        
        if (this != &moved)
        {
            x = std::move(moved.x);
            y = std::move(moved.y);
            z = std::move(moved.z);
            w = std::move(moved.w);
        }
        return *this;
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr bool Vec4<T>::operator==(const Vec4<T>& other) const
    {
        return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr bool Vec4<T>::operator!=(const Vec4<T>& other) const
    {
        return !(*this == other);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator+(const Vec4<T>& other) const
    {
        return Vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator-(const Vec4<T>& other) const
    {
        return Vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator*(const Vec4<T>& other) const
    {
        return Vec4(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
    }
    
    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator/(const Vec4<T>& other) const
    {
        return Vec4(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator+(const T& scalar) const
    {
        return Vec4(this->x + scalar, this->y + scalar, this->z + scalar, this->w + scalar);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator-(const T& scalar) const
    {
        return Vec4(this->x - scalar, this->y - scalar, this->z - scalar, this->w - scalar);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator*(const T& scalar) const
    {
        return Vec4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
    }
    
    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec4<T> Vec4<T>::operator/(const T& scalar) const
    {
        return Vec4(this->x / scalar, this->y / scalar, this->z / scalar, this->w / scalar);
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec4<T> Vec4<T>::zero() 
    { 
        return Vec4(T{}, T{}, T{}, T{}); 
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec4<T> Vec4<T>::one()
    { 
        return Vec4(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr T Vec4<T>::length() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr Vec4<T> Vec4<T>::normalized() const
    {
        T len = length();
        if (len == T{})
            return *this;
        return *this / len; 
    }
}

#endif
