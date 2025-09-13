#pragma once

namespace bw
{
	///
    /// @struct Bounds
	/// 
	/// @brief
	/// Template struct representing axis-aligned bounding box
    /// Represents a rectangular boundary defined by four edges:
    /// - top, right, bottom, left
    /// Useful for collision detection, UI layout, and spatial queries
	/// 
	/// @tparam T Type of boundary components
    ///
	template<typename T>
	struct Bounds
	{
		T top;
		T right;
		T bottom;
		T left;
		
		Bounds(T top, T right, T bottom, T left) : top(top), right(right), bottom(bottom), left(left) { }
	
		bool operator==(const Bounds& other) const
		{
			return top == other.top && right == other.right &&
				   bottom == other.bottom && left == other.left;
		}

		bool operator!=(const Bounds& other) const
		{
			return !(*this == other);
		}
	};

	using BoundsI = Bounds<int>;
	using BoundsD = Bounds<double>;
	using BoundsF = Bounds<float>;
}
