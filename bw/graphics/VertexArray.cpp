// VertexArray.cpp
#include <glad/glad.h>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"

namespace bw::low_level
{
    VertexArray::VertexArray() : _handle(NullVertexArray), _vertexBuffer(nullptr), _elementBuffer(nullptr), _range({0, 0})
    {
        glCreateVertexArrays(1, &_handle);
    }

    ////////////////////////////////////////////////////////////

    VertexArray::VertexArray(VertexBuffer& buffer, Range range) : _handle(NullVertexArray), _vertexBuffer(&buffer), _elementBuffer(nullptr), _range(range)
    {
        glCreateVertexArrays(1, &_handle);
        bindTo(buffer, range);
    }
    
    ////////////////////////////////////////////////////////////

    VertexArray::VertexArray(VertexBuffer& buffer) : VertexArray(buffer, { 0, buffer.size() }) 
    { }
    
    ////////////////////////////////////////////////////////////

    VertexArray::VertexArray(const VertexArray& other) : _handle(NullVertexArray), _vertexBuffer(nullptr), _elementBuffer(nullptr), _range({0, 0})
    {
        glCreateVertexArrays(1, &_handle);
        if(other._vertexBuffer)
            this->bindTo(*other._vertexBuffer, other._range);
        if (other._elementBuffer) {
            this->bindTo(*other._elementBuffer);
        }
    }

    ////////////////////////////////////////////////////////////

    VertexArray::VertexArray(VertexArray&& moved) noexcept : _handle(moved._handle), _vertexBuffer(moved._vertexBuffer), _elementBuffer(moved._elementBuffer), _range(moved._range)
    {
        moved._handle = NullVertexArray;
        moved._vertexBuffer = nullptr;
        moved._elementBuffer = nullptr;
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
        if (this != &other) {
            this->bindTo(*other._vertexBuffer, other._range);
            if (other._elementBuffer) {
                this->bindTo(*other._elementBuffer);
            }
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////

    VertexArray& VertexArray::operator=(VertexArray&& moved) noexcept
    {
        if (this != &moved)
        {
            release();
            
            _handle = moved._handle;
            _vertexBuffer = moved._vertexBuffer;
            _elementBuffer = moved._elementBuffer;
            _range = moved._range;
            
            moved._handle = NullVertexArray;
            moved._vertexBuffer = nullptr;
            moved._elementBuffer = nullptr;
            moved._range = {0, 0};
        }
        return *this;
    }
    
    ////////////////////////////////////////////////////////////

    bool VertexArray::operator==(const VertexArray& other)
    {
        return this == &other;
    }
    
    ////////////////////////////////////////////////////////////

    bool VertexArray::operator!=(const VertexArray& other)
    {
        return !(*this == other);
    }
    
    ////////////////////////////////////////////////////////////

    void VertexArray::bindTo(VertexBuffer& buffer)
    {
        bindTo(buffer, {0, buffer.size()});
    }
    
    ////////////////////////////////////////////////////////////

    void VertexArray::bindTo(VertexBuffer& buffer, Range range)
    {
        _vertexBuffer = &buffer;
        _range = range;

        const int bindingIndex = 0;
        const int stride = sizeof(Vertex);
        const size_t offset = range.start * stride;

        glVertexArrayVertexBuffer(_handle, bindingIndex, buffer.getNativeHandle(), offset, sizeof(Vertex));

        // Position (location = 0)
        glVertexArrayAttribFormat(_handle, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
        glVertexArrayAttribBinding(_handle, 0, bindingIndex);
        glEnableVertexArrayAttrib(_handle, 0);

        // Color (location = 1)
        glVertexArrayAttribFormat(_handle, 1, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
        glVertexArrayAttribBinding(_handle, 1, bindingIndex);
        glEnableVertexArrayAttrib(_handle, 1);

        // Texture coordinates (location = 2)
        glVertexArrayAttribFormat(_handle, 2, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, texture));
        glVertexArrayAttribBinding(_handle, 2, bindingIndex);
        glEnableVertexArrayAttrib(_handle, 2);
    }

    ////////////////////////////////////////////////////////////

    void VertexArray::bindTo(ElementBuffer& elementBuffer)
    {
        _elementBuffer = &elementBuffer;
        glVertexArrayElementBuffer(_handle, elementBuffer.getNativeHandle());
    }

    ////////////////////////////////////////////////////////////

    VertexBuffer* VertexArray::getCurrentVertexBuffer()
    {
        return _vertexBuffer;
    }

    ////////////////////////////////////////////////////////////

    ElementBuffer* VertexArray::getCurrentElementBuffer()
    {
        return _elementBuffer;
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
            if(_elementBuffer) 
                glVertexArrayElementBuffer(_handle, ElementBuffer::NullElementBuffer);

            glDeleteVertexArrays(1, &_handle);
            _handle = NullVertexArray;
        }
        _vertexBuffer = nullptr;
        _elementBuffer = nullptr;
        _range = {0, 0};
    }
}
