#ifndef VEC2_TPP
#define VEC2_TPP

#include <memory>
#include <cmath>

namespace bw
{
    template <typename T>
    Vec2<T>::Vec2(Vec2<T>&& moved) noexcept : x(std::move(moved.x)), y(std::move(moved.y)) { }

    ////////////////////////////////////////////////////////////

    template <typename T>
    template <typename U>
    Vec2<T>::Vec2(Vec2<U>&& moved) : x(static_cast<T>(std::move(moved.x))), y(static_cast<T>(std::move(moved.y))) { }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec2<T>& Vec2<T>::operator=(const Vec2<T>& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec2<T>& Vec2<T>::operator=(Vec2<T>&& moved) noexcept
    {        
        if (this != &moved)
        {
            x = std::move(moved.x);
            y = std::move(moved.y);
        }
        return *this;
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    bool Vec2<T>::operator==(const Vec2<T>& other) const
    {
        return (this->x == other.x && this->y == other.y);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    bool Vec2<T>::operator!=(const Vec2<T>& other) const
    {
        return !(*this == other);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec2<T> Vec2<T>::operator+(const Vec2<T>& other)
    {
        return Vec2(this->x + other.x, this->y + other.y);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    Vec2<T> Vec2<T>::operator-(const Vec2<T>& other)
    {
        return Vec2(this->x - other.x, this->y - other.y);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    Vec2<T> Vec2<T>::operator*(const Vec2<T>& other)
    {
        return Vec2(this->x * other.x, this->y * other.y);
    }
    
    ////////////////////////////////////////////////////////////
    
    template <typename T>
    Vec2<T> Vec2<T>::operator/(const Vec2<T>& other)
    {
        return Vec2(this->x / other.x, this->y / other.y);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec2<T> Vec2<T>::operator+(const T& scalar)
    {
        return Vec2(this->x + scalar, this->y + scalar);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    Vec2<T> Vec2<T>::operator-(const T& scalar)
    {
        return Vec2(this->x - scalar, this->y - scalar);
    }

    ////////////////////////////////////////////////////////////
    
    template <typename T>
    Vec2<T> Vec2<T>::operator*(const T& scalar)
    {
        return Vec2(this->x * scalar, this->y * scalar);
    }
    
    ////////////////////////////////////////////////////////////
    
    template <typename T>
    Vec2<T> Vec2<T>::operator/(const T& scalar)
    {
        return Vec2(this->x / scalar, this->y / scalar);
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec2<T> Vec2<T>::zero() 
    { 
        return Vec2(T{}, T{}); 
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec2<T> Vec2<T>::one()
    { 
        return Vec2(static_cast<T>(1), static_cast<T>(1));
    }
    
    ////////////////////////////////////////////////////////////

    template <typename T>
    T Vec2<T>::length() const
    {
        return std::sqrt(x * x + y * y);
    }

    ////////////////////////////////////////////////////////////

    template <typename T>
    Vec2<T> Vec2<T>::normalized()
    {
        T len = length();
        if (len == T{})
            return *this;
        return *this / len; 
    }
}

#endif
