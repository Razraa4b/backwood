#include <stdexcept>
#include <glad/glad.h>
#include "VertexBufferMappingContext.hpp"
#include "VertexBuffer.hpp"

namespace bw::low_level
{
    GLenum glAccessToEnum(MapAccess access)
    {
        switch(access)
        {
            case MapAccess::ReadOnly:  return GL_READ_ONLY;
            case MapAccess::WriteOnly: return GL_WRITE_ONLY;
            default:                   return GL_READ_WRITE;
        }
    }

    ////////////////////////////////////////////////////////////

    VertexBufferMappingContext::VertexBufferMappingContext(VertexBuffer& buffer) 
        : _buffer(&buffer), _isMapped(false), _data(nullptr) { }
    
    ////////////////////////////////////////////////////////////

    VertexBufferMappingContext::VertexBufferMappingContext(VertexBufferMappingContext&& moved) noexcept
        : _buffer(moved._buffer), _data(moved._data), _isMapped(moved._isMapped)
    {
        moved._buffer = nullptr;
        moved._data = nullptr;
    }

	////////////////////////////////////////////////////////////

    VertexBufferMappingContext::~VertexBufferMappingContext()
    {
        if(_isMapped)
        {
            unmap();
        }
    }
    
	////////////////////////////////////////////////////////////
    
    const Vertex& VertexBufferMappingContext::operator[](int index) const
    {
        if(!_data || !_isMapped)
        {
            throw std::runtime_error("Buffer is not mapped or mapping failed");
        }
        return _data[index];
    }

	////////////////////////////////////////////////////////////

    Vertex& VertexBufferMappingContext::operator[](int index)
    {
        if(!_data || !_isMapped)
            throw std::runtime_error("Buffer not mapped");
        return *(_data + index);
    }
    
    ////////////////////////////////////////////////////////////

    void VertexBufferMappingContext::map(MapAccess access) 
    {
        _data = static_cast<Vertex*>(glMapNamedBuffer(_buffer->getNativeHandle(), glAccessToEnum(access)));
        _isMapped = true;
    }

    ////////////////////////////////////////////////////////////

    void VertexBufferMappingContext::unmap()
    {
        glUnmapNamedBuffer(_buffer->getNativeHandle());
        _isMapped = false;
        _data = nullptr;
    }

    ////////////////////////////////////////////////////////////

    Vertex* VertexBufferMappingContext::getPurePointer()
    {
        return _data;
    }
    
    ////////////////////////////////////////////////////////////

    bool VertexBufferMappingContext::isMapped() const
    {
        return _isMapped;
    }
}
