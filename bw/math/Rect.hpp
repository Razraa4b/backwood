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

		bool operator==(const Rect& other) const
		{
			return position == other.position && size == other.size;
		}

		bool operator!=(const Rect& other) const
		{
			return !(*this == other);
		}

		/// @brief Calculate area of the rectangle
		T area() const { return size.x * size.y; }
	};

	using Recti = Rect<int>;
	using Rectd = Rect<double>;
	using Rectf = Rect<float>;
}
