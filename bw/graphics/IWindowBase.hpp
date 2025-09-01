#pragma once

#include "math/Vec2.hpp"
#include "math/Vec4.hpp"

namespace bw
{
	///
	/// @interface IWindowBase
	/// @brief Interface defining basic window operations and properties
	///
	class IWindowBase
	{
	public:
		virtual ~IWindowBase() = default;
		
		/// @brief Resize window to specified dimensions
		/// @param size - New window size in pixels
		virtual void resize(Vec2i size) const = 0;

		/// @brief Move window to specified position
		/// @param position - New window position in screen coordinates
		virtual void move(Vec2i position) const = 0;

		/// @brief Make window visible
		virtual void show() const = 0;

		/// @brief Hide window
		virtual void hide() const = 0;

		/// @brief Clear window content with specified color
		/// @param color - RGBA color to clear with
		virtual void clear(Vec4i color) = 0;

		/// @brief Update window display (swap buffers, present render)
		virtual void update() = 0;

		/// @brief Check if window is currently visible
		/// @return True if window is visible, false otherwise
		virtual bool isVisible() const = 0;

		/// @brief Check if window is open and valid
		/// @return True if window is open, false if closed or invalid
		virtual bool isOpen() const = 0;
	
		/// @brief Closes current window
		virtual void close() const = 0;
	};
}
