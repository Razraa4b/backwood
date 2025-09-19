#pragma once

#define BW_PI 3.14159

namespace bw
{
	///
    /// @struct Circle
    /// @brief Template struct representing a 2D circle
	/// 
    /// Represents a circle with center point and radius
    /// Provides basic circle properties and measurements
    ///
	/// @tparam T Type of circle components
	/// 
	template<typename T>
	struct Circle
	{
		Vec2<T> center;
		T radius;

		Circle(Vec2<T> center, T radius) : center(center), radius(radius) { }
		Circle(T xCenter, T yCenter, T radius) : Circle({ xCenter, yCenter }, radius) { }
		Circle() : Circle({ T{}, T{} }, T{}) { }

		constexpr operator==(const Circle& other) const
		{
			return center == other.center && radius == other.radius;
		}

		constexpr bool operator!=(const Circle&  other) const
		{
			return !(*this == other);
		}

		/// @brief Calculate diameter of the circle
		constexpr T diameter() const { return radius * 2 };

		/// @brief Calculate circumference of the circle
		constexpr T circumference() const { return diameter() * BW_PI; }

		/// @brief Calculate area of the circle
		constexpr T area() const { return radius * radius * BW_PI; }
	};

	using CircleI = Circle<int>;
	using CircleD = Circle<double>;
	using CircleF = Circle<float>;
}
