#include <glad/glad.h>
#include "EBMapContext.hpp"
#include "ElementBuffer.hpp"

namespace bw::low_level
{
    GLenum eb_mapAccessToGLenum(MapAccess access)
    {
        switch(access)
        {
            case MapAccess::ReadOnly:  return GL_READ_ONLY;
            case MapAccess::WriteOnly: return GL_WRITE_ONLY;
            default:                   return GL_READ_WRITE;
        }
    }

	////////////////////////////////////////////////////////////

    EBMapContext::EBMapContext(ElementBuffer& buffer) : _buffer(&buffer) { }
    
	////////////////////////////////////////////////////////////

    EBMapContext::EBMapContext(EBMapContext&& moved)
    {   
        this->_buffer = moved._buffer;
        this->_data = moved._data;

        moved._buffer = nullptr;
        moved._data = nullptr;
    }

	////////////////////////////////////////////////////////////
       
    EBMapContext::~EBMapContext()
    {
        unmap();
    }
    
	////////////////////////////////////////////////////////////

    EBMapContext& EBMapContext::operator=(EBMapContext&& moved)
    {
        unmap();

        this->_buffer = moved._buffer;
        this->_data = moved._data;

        moved._buffer = nullptr;
        moved._data = nullptr;

        return *this;
    }
    
	////////////////////////////////////////////////////////////

    size_t& EBMapContext::operator[](int index)
    {
        return *(_data + index);
    }
    
	////////////////////////////////////////////////////////////

    const size_t& EBMapContext::operator[](int index) const
    {
        return *(_data + index);
    }
    
	////////////////////////////////////////////////////////////

    void EBMapContext::map(MapAccess access)
    {
        if(!isMapped())
            _data = static_cast<size_t*>(glMapNamedBuffer(_buffer->getNativeHandle(), eb_mapAccessToGLenum(access)));
    }
    
	////////////////////////////////////////////////////////////

    void EBMapContext::unmap()
    {
        if(isMapped())
            glUnmapNamedBuffer(_buffer->getNativeHandle());
    }
    
	////////////////////////////////////////////////////////////

    bool EBMapContext::isMapped() const
    {
        int mapped;

        glGetNamedBufferParameteriv(_buffer->getNativeHandle(), GL_BUFFER_MAPPED, &mapped);
    
        return mapped;
    }
    
	////////////////////////////////////////////////////////////

    size_t& EBMapContext::get(int index)
    {
        return (*this)[index];
    }

	////////////////////////////////////////////////////////////

    std::optional<size_t*> EBMapContext::tryGet(int index)
    {
        if(!_data) return std::nullopt;

        int n = _buffer->size();
        if(index < 0 || index >= n) return std::nullopt;

        return _data + index;
    }
}
