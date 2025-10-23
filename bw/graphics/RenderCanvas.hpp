#pragma once

#include "RenderOptions.hpp"

namespace bw
{
    namespace low_level
    {
        class VertexArray;
    }

    /// @class RenderCanvas
	/// @brief Represents the base class of the canvas for drawing primitives on it.
	class RenderCanvas
	{
	public:
        /// @brief Draws an `array` on the canvas using the `render options`
        /// @param options Rendering options
        /// @param array Vertex array object
        virtual void draw(const RenderOptions& options, const low_level::VertexArray& array);
        
        /// @brief Draws an `array` on the canvas by `primitive`
        /// @param primitive Primitive to draw
        /// @param array Vertex array object
        virtual void draw(low_level::Primitive primitive, const low_level::VertexArray& array);  
	};
}
