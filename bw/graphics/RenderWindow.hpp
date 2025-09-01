#pragma once

#include "RenderCanvas.hpp"
#include "SimpleWindow.hpp"

namespace bw
{
	///
	/// @class RenderWindow
	/// @brief Concrete window implementation combining rendering, API access and base functionality
	/// @implements SimpleWindow, RenderCanvas
	///
	class RenderWindow : public SimpleWindow, RenderCanvas
	{
	public:
		using SimpleWindow::SimpleWindow;
	};
}
