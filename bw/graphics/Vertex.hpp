#pragma once

#include "math/Vec3.hpp"
#include "math/Vec4.hpp"

namespace bw::low_level
{
	struct Vertex
	{
		Vec3f position;
		Vec4f color;
		Vec4f texture;
	
		Vertex(Vec3f position, Vec4f color, Vec4f texture) : position(position), color(color), texture(texture) { }
		Vertex(Vec3f position, Vec4f color) : position(position), color(color) { }
		Vertex() : Vertex({ 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }) {}
	};
}
