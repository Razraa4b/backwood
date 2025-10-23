#include "RenderCanvas.hpp"
#include "RenderOptions.hpp"
#include "ShaderProgram.hpp"
#include "VertexArray.hpp"
#include <glad/glad.h>

using namespace bw::low_level;

namespace bw
{
    GLenum primitiveToGLenum(Primitive primitive)
    {
        switch(primitive)
        {
            case Primitive::Points:        return GL_POINTS;
            case Primitive::Lines:         return GL_LINES;
            case Primitive::LineStrip:     return GL_LINE_STRIP;
            case Primitive::LineLoop:      return GL_LINE_LOOP;
            case Primitive::Triangles:     return GL_TRIANGLES;
            case Primitive::TriangleStrip: return GL_TRIANGLE_STRIP;
            case Primitive::TriangleFan:   return GL_TRIANGLE_FAN;
            case Primitive::Quads:         return GL_QUADS;
            default:                       return GL_NONE;
        }
    }

    ////////////////////////////////////////////////////////////

    void RenderCanvas::draw(const RenderOptions& options, const low_level::VertexArray& array)
    {
        auto range = array.getRange();
        auto handle = array.getNativeHandle();

        if(options.shaderProgram)
            options.shaderProgram->use();

        glBindVertexArray(handle);
        glDrawArrays(primitiveToGLenum(options.primitive), range.start, range.count);
        glBindVertexArray(low_level::VertexArray::NullVertexArray);
    }

    ////////////////////////////////////////////////////////////

    void RenderCanvas::draw(Primitive primitive, const low_level::VertexArray& array)
    {
        // we repeat the code without calling the already created implementation 
        // in order not to create an extra instance of RenderOptions.
        
        auto range = array.getRange();
        auto handle = array.getNativeHandle();

        glBindVertexArray(handle);
        glDrawArrays(primitiveToGLenum(primitive), range.start, range.count);
        glBindVertexArray(low_level::VertexArray::NullVertexArray);
    }
}
