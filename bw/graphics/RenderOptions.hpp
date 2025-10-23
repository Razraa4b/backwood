#pragma once

#include "Primitive.hpp"

namespace bw
{
    namespace low_level
    {
        class ShaderProgram;
    };

    struct RenderOptions
    {
        low_level::Primitive primitive;
        const low_level::ShaderProgram* shaderProgram;
    };
}
