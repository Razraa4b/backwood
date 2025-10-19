#pragma once

#include "Vec2.hpp"

namespace bw
{
	///
	/// @struct Rect  
	/// @brief Template struct representing a 2D rectangle
	///
	/// Represents a rectangle with position and size
	/// Suitable for UI elements, collision boxes, and spatial regions
	///
	/// @tparam T Type of rectangle components
	/// 
	template<typename T>
	struct Rect
	{
		Vec2<T> position;
		Vec2<T> size;

		Rect(Vec2<T> position, Vec2<T> size) : position(position), size(size) { }
		Rect(T xPos, T yPos, T width, T height) : Rect({ xPos, yPos }, { width, height }) { }
		Rect() { }

		constexpr bool operator==(const Rect& other) const
		{
			return position == other.position && size == other.size;
		}

		constexpr bool operator!=(const Rect& other) const
		{
			return !(*this == other);
		}

        /// @brief Calculate perimeter of the rectangle
        /// @return Perimeter of rectangle
        constexpr T perimeter() const { return size.x * 2 + size.y * 2; }

		/// @brief Calculate area of the rectangle
		/// @return Area of rectangle
        constexpr T area() const { return size.x * size.y; }
	};

	using RectI = Rect<int>;
	using RectD = Rect<double>;
	using RectF = Rect<float>;
}
