#pragma once

namespace bw
{
	///
	/// @interface IWindowApi
	/// @brief Interface providing access to native window handles and graphics contexts
	///
	class IWindowApi
	{
	public:
		virtual ~IWindowApi() = default;

		/// @brief Get native platform-specific window handle
		/// @return Pointer to native window handle (HWND on Windows, SimpleWindow on X11, etc.)
		virtual void* getNativeHandle() = 0;

		/// @brief Get graphics rendering context
		/// @return Pointer to graphics context (OpenGL context, DirectX device, etc.)
		virtual void* getGraphicsContext() = 0;
	};
}
