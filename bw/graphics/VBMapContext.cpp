#include <glad/glad.h>
#include "VBMapContext.hpp"
#include "VertexBuffer.hpp"

namespace bw::low_level
{
    GLenum mapAccessToGLenum(MapAccess access)
    {
        switch(access)
        {
            case MapAccess::ReadOnly:  return GL_READ_ONLY;
            case MapAccess::WriteOnly: return GL_WRITE_ONLY;
            default:                   return GL_READ_WRITE;
        }
    }

	////////////////////////////////////////////////////////////

    VBMapContext::VBMapContext(VertexBuffer& buffer) : _buffer(&buffer) { }
    
	////////////////////////////////////////////////////////////

    VBMapContext::VBMapContext(VBMapContext&& moved)
    {   
        this->_buffer = moved._buffer;
        this->_data = moved._data;

        moved._buffer = nullptr;
        moved._data = nullptr;
    }
    
	////////////////////////////////////////////////////////////

    VBMapContext& VBMapContext::operator=(VBMapContext&& moved)
    {
        unmap();

        this->_buffer = moved._buffer;
        this->_data = moved._data;

        moved._buffer = nullptr;
        moved._data = nullptr;

        return *this;
    }
    
	////////////////////////////////////////////////////////////

    Vertex& VBMapContext::operator[](int index)
    {
        return *(_data + index);
    }
    
	////////////////////////////////////////////////////////////

    const Vertex& VBMapContext::operator[](int index) const
    {
        return *(_data + index);
    }
    
	////////////////////////////////////////////////////////////

    void VBMapContext::map(MapAccess access)
    {
        if(!isMapped())
            _data = static_cast<Vertex*>(glMapNamedBuffer(_buffer->getNativeHandle(), mapAccessToGLenum(access)));
    }
    
	////////////////////////////////////////////////////////////

    void VBMapContext::unmap()
    {
        if(isMapped())
            glUnmapNamedBuffer(_buffer->getNativeHandle());
    }
    
	////////////////////////////////////////////////////////////

    bool VBMapContext::isMapped() const
    {
        int mapped;

        glGetNamedBufferParameteriv(_buffer->getNativeHandle(), GL_BUFFER_MAPPED, &mapped);
    
        return mapped;
    }
    
	////////////////////////////////////////////////////////////

    Vertex& VBMapContext::get(int index)
    {
        return (*this)[index];
    }

	////////////////////////////////////////////////////////////

    std::optional<Vertex&> VBMapContext::tryGet(int index)
    {
        int n = _buffer->size();
        if(index < 0 || index >= n) return;

        return (*this)[index];
    }
}
