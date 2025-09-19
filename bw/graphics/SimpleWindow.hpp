#pragma once

#include <string>
#include "math/Rect.hpp"
#include "IWindowApi.hpp"
#include "IWindowBase.hpp"

namespace bw
{
	class Logger;
	struct WindowImpl;

	///
	/// @class SimpleWindow
	/// @brief Concrete window implementation API access and base functionality
	/// @implements IWindowBase, IWindowApi
	///
	class SimpleWindow : public IWindowBase, IWindowApi
	{
	public:
		/// @brief Construct window with title and rectangular area
		/// @param title SimpleWindow title/caption
		/// @param rect SimpleWindow position and size rectangle
		SimpleWindow(std::string title, RectI rect);

		/// @brief Construct window with title and size (centered position)
		/// @param title SimpleWindow title/caption
		/// @param size SimpleWindow dimensions
		SimpleWindow(std::string title, Vec2i size);

		/// @brief Construct window with default parameters
		SimpleWindow();

		SimpleWindow(const SimpleWindow&) = delete;
		SimpleWindow(SimpleWindow&&) = delete;

		~SimpleWindow();

		SimpleWindow& operator=(const SimpleWindow&) = delete;
		SimpleWindow& operator=(SimpleWindow&&) = delete;

		// IWindowBase interface implementation
        
        /// @brief Resize window to specified dimensions
		/// @param size New window size in pixels
		virtual void resize(Vec2i size) const override;
		
        /// @brief Move window to specified position
		/// @param position New window position in screen coordinates
		virtual void move(Vec2i position) const override;

		/// @brief Make window visible
		virtual void show() const override;
		
        /// @brief Hide window
		virtual void hide() const override;

		/// @brief Clear window content with specified color
		/// @param color RGBA color to clear with
		virtual void clear(Vec4i color) override;
		
        /// @brief Update window display (swap buffers, present render)
		virtual void update() override;

		/// @brief Check if window is currently visible
		/// @return True if window is visible, false otherwise
		virtual bool isVisible() const override;
		
        /// @brief Check if window is open and valid
		/// @return True if window is open, false if closed or invalid
		virtual bool isOpen() const override;

		/// @brief Closes current window
		virtual void close() const override;

		/// @brief Get current window position
		/// @return SimpleWindow position in screen coordinates
		virtual Vec2i getPosition() const;
		
		/// @brief Get current window size
		/// @return SimpleWindow dimensions in pixels
		virtual Vec2i getSize() const;

		/// @brief Get window title
		/// @return Current window title string
		virtual std::string getTitle() const;

		// IWindowApi interface implementation
        
		/// @brief Get native platform-specific window handle
		/// @return Pointer to native window handle (HWND on Windows, SimpleWindow on X11, etc.)
        virtual void* getNativeHandle() override;
        
		/// @brief Get graphics rendering context
		/// @return Pointer to graphics context (OpenGL context, DirectX device, etc.)
		virtual void* getGraphicsContext() override;
	protected:
		Logger& _logger;
		std::unique_ptr<WindowImpl> _impl;
	};
}
