#ifndef VEC3_TPP
#define VEC3_TPP

#include <memory>
#include <cmath>
 
namespace bw
{
    template <typename T>
    Vec3<T>::Vec3(Vec3<T>&& moved) noexcept : x(std::move(moved.x)), y(std::move(moved.y)), z(std::move(moved.z)) { }

    ////////////////////////////////////////////////////////////

    template <typename T>
    template <typename U>
    Vec3<T>::Vec3(Vec3<U>&& moved) : x(static_cast<T>(std::move(moved.x))), y(static_cast<T>(std::move(moved.y))), z(static_cast<T>(std::move(moved.z))) { }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec3<T>& Vec3<T>::operator=(const Vec3<T>& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec3<T>& Vec3<T>::operator=(Vec3<T>&& moved)
    {        
        if (this != &moved)
        {
            x = std::move(moved.x);
            y = std::move(moved.y);
            z = std::move(moved.z);
        }
        return *this;
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr bool Vec3<T>::operator==(const Vec3<T>& other) const
    {
        return (this->x == other.x && this->y == other.y && this->z == other.z);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr bool Vec3<T>::operator!=(const Vec3<T>& other) const
    {
        return !(*this == other);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator+(const Vec3<T>& other) const
    {
        return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator-(const Vec3<T>& other) const
    {
        return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator*(const Vec3<T>& other) const
    {
        return Vec3(this->x * other.x, this->y * other.y, this->z * other.z);
    }
    
    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator/(const Vec3<T>& other) const
    {
        return Vec3(this->x / other.x, this->y / other.y, this->z / other.z);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator+(const T& scalar) const
    {
        return Vec3(this->x + scalar, this->y + scalar, this->z + scalar);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator-(const T& scalar) const
    {
        return Vec3(this->x - scalar, this->y - scalar, this->z - scalar);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator*(const T& scalar) const
    {
        return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
    }
    
    ////////////////////////////////////////////////////////////
    
    template <typename T>
    constexpr Vec3<T> Vec3<T>::operator/(const T& scalar) const
    {
        return Vec3(this->x / scalar, this->y / scalar, this->z / scalar);
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec3<T> Vec3<T>::zero() 
    { 
        return Vec3(T{}, T{}, T{}); 
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec3<T> Vec3<T>::one()
    { 
        return Vec3(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr T Vec3<T>::length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    constexpr Vec3<T> Vec3<T>::normalized() const
    {
        T len = length();
        if (len == T{})
            return *this;
        return *this / len; 
    }
}

#endif
