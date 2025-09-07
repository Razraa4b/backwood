#include <glad/glad.h>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

namespace bw::low_level
{
    VertexArray::VertexArray() : _handle(NullVertexArray), _buffer(nullptr), _range({0, 0})
    {
        glCreateVertexArrays(1, &_handle);
    }

	////////////////////////////////////////////////////////////

    VertexArray::VertexArray(VertexBuffer& buffer, Range range) : _handle(NullVertexArray), _buffer(&buffer), _range(range)
    {
        glCreateVertexArrays(1, &_handle);
        bindTo(buffer, range);
    }
    
	////////////////////////////////////////////////////////////

    VertexArray::VertexArray(VertexBuffer& buffer) : VertexArray(buffer, { 0, buffer.size() }) { }
    
	////////////////////////////////////////////////////////////

    VertexArray::VertexArray(const VertexArray& other)
    {
        glCreateVertexArrays(1, &_handle);
        this->bindTo(*other._buffer, other._range);
    }

	////////////////////////////////////////////////////////////

    VertexArray::VertexArray(VertexArray&& moved) noexcept : _handle(moved._handle), _buffer(moved._buffer), _range(moved._range)
    {
        moved._handle = NullVertexArray;
        moved._buffer = nullptr;
        moved._range = {0, 0};
    }
    
	////////////////////////////////////////////////////////////

    VertexArray::~VertexArray()
    {
        release();
    }

    ////////////////////////////////////////////////////////////

    VertexArray& VertexArray::operator=(const VertexArray& other)
    {
        this->bindTo(*other._buffer, other._range);
        return *this;
    }

	////////////////////////////////////////////////////////////

    VertexArray& VertexArray::operator=(VertexArray&& moved) noexcept
    {
        if (this != &moved)
        {
            release();
            
            _handle = moved._handle;
            _buffer = moved._buffer;
            _range = moved._range;
            
            moved._handle = NullVertexArray;
            moved._buffer = nullptr;
            moved._range = {0, 0};
        }
        return *this;
    }
    
	////////////////////////////////////////////////////////////

    void VertexArray::bindTo(VertexBuffer& buffer)
    {
        bindTo(buffer, {0, buffer.size()});
    }
    
	////////////////////////////////////////////////////////////

    void VertexArray::bindTo(VertexBuffer& buffer, Range range)
    {
        _buffer = &buffer;
        _range = range;

        const GLuint bindingIndex = 0;
        const GLsizei stride = sizeof(Vertex);
        const GLintptr offset = range.count * stride;

        glVertexArrayVertexBuffer(_handle, bindingIndex, 
                                 buffer.getNativeHandle(), 
                                 offset, stride);

        // Position (location = 0)
        glVertexArrayAttribFormat(_handle, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glVertexArrayAttribBinding(_handle, 0, bindingIndex);
        glEnableVertexArrayAttrib(_handle, 0);

        // Color (location = 1)
        glVertexArrayAttribFormat(_handle, 1, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
        glVertexArrayAttribBinding(_handle, 1, bindingIndex);
        glEnableVertexArrayAttrib(_handle, 1);

        // Texture coordinates (location = 2)
        glVertexArrayAttribFormat(_handle, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texture));
        glVertexArrayAttribBinding(_handle, 2, bindingIndex);
        glEnableVertexArrayAttrib(_handle, 2);
    }
    
	////////////////////////////////////////////////////////////

    VertexBuffer& VertexArray::getCurrentBuffer()
    {
        return *_buffer;
    }
    
	////////////////////////////////////////////////////////////

    VertexArray::Range VertexArray::getRange() const
    {
        return _range;
    }
    
	////////////////////////////////////////////////////////////

    unsigned int VertexArray::getNativeHandle() const
    {
        return _handle;
    }
    
	////////////////////////////////////////////////////////////

    void VertexArray::release()
    {
        if (_handle != NullVertexArray)
        {
            glDeleteVertexArrays(1, &_handle);
            _handle = NullVertexArray;
        }
        _buffer = nullptr;
        _range = {0, 0};
    }
}
