#include <iostream>
#include <stdexcept>
#include <glad/glad.h>
#include "VertexBuffer.hpp"

namespace bw::low_level
{
    GLenum vb_bufferUsageToGLEnum(BufferUsage usage)
    {
        switch(usage)
        {
            case BufferUsage::Static:  return GL_STATIC_DRAW;
            case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
            default:                   return GL_STREAM_DRAW;
        }
    }
    
	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(BufferUsage usage) : _handle(NullVertexBuffer)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, 0, nullptr, vb_bufferUsageToGLEnum(usage));
    }
     
	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(BufferUsage usage, std::span<Vertex> initializer) : _handle(NullVertexBuffer)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, initializer.size() * sizeof(Vertex), 
                          initializer.data(), vb_bufferUsageToGLEnum(usage));
    }
    
	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(BufferUsage usage, size_t reserveSize) : _handle(NullVertexBuffer)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, reserveSize * sizeof(Vertex), nullptr, vb_bufferUsageToGLEnum(usage));
    }
    
	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(const VertexBuffer& other) : _handle(NullVertexBuffer)
    {
        glCreateBuffers(1, &_handle);
        this->reserve(other.size());
        other.copyTo(*this);
    }
    
	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(VertexBuffer&& moved) noexcept : _handle(NullVertexBuffer)
    {
        _handle = moved._handle;
        moved._handle = NullVertexBuffer;
    }
    
	////////////////////////////////////////////////////////////
    
    VertexBuffer::~VertexBuffer()
    {
        release();
    }

	////////////////////////////////////////////////////////////
    
    VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
    {
        if(this != &other)
        {
            other.copyTo(*this);
        }
        return *this;
    }

	////////////////////////////////////////////////////////////

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& moved) noexcept
    {
        if(this != &moved)
        {
            this->release();

            _handle = moved._handle;
            moved._handle = NullVertexBuffer;   
        }
        return *this;
    }

	////////////////////////////////////////////////////////////
    
    bool VertexBuffer::operator==(const VertexBuffer& other) const
    {
        return _handle == other._handle;
    }
	
    ////////////////////////////////////////////////////////////

    bool VertexBuffer::operator!=(const VertexBuffer& other) const
    {
        return !(*this == other);
    }

	////////////////////////////////////////////////////////////
        
    void VertexBuffer::reserve(size_t size)
    {
        size_t currentSize = this->size();
        if (size <= currentSize) return;

        std::vector<Vertex> oldData { data() };
        glNamedBufferData(_handle, size * sizeof(Vertex), oldData.data(), vb_bufferUsageToGLEnum(getUsage()));
    }
    
	////////////////////////////////////////////////////////////

    void VertexBuffer::update(size_t offset, std::span<Vertex> vertices)
    {
        glNamedBufferSubData(_handle, offset  * sizeof(Vertex), vertices.size()  * sizeof(Vertex), vertices.data());
    }

	////////////////////////////////////////////////////////////
    
    void VertexBuffer::update(std::span<Vertex> vertices)
    {
        update(0, vertices);
    }

	////////////////////////////////////////////////////////////
    
    void VertexBuffer::copyTo(IBufferStorage<Vertex>& buffer) const
    {
        if (auto* vertexBuffer = dynamic_cast<VertexBuffer*>(&buffer)) 
        {
            size_t currentCapacity = this->capacity();

            if (vertexBuffer->capacity() < currentCapacity) {
                vertexBuffer->reserve(currentCapacity / sizeof(Vertex));
            }
            glCopyNamedBufferSubData(_handle, vertexBuffer->_handle, 0, 0, currentCapacity);
        }
        else 
        {
            std::vector<Vertex> data = this->data();
            buffer.update(data);
        }
    }

	////////////////////////////////////////////////////////////
    
    std::vector<Vertex> VertexBuffer::data() const
    {
        return data(0, size());
    }

	////////////////////////////////////////////////////////////

    std::vector<Vertex> VertexBuffer::data(size_t offset, size_t size) const
    {
        std::vector<Vertex> container(size);
        glGetNamedBufferSubData(_handle, offset  * sizeof(Vertex), size * sizeof(Vertex), container.data());
        return container;
    }
    
	////////////////////////////////////////////////////////////
    
    size_t VertexBuffer::size() const
    {
        return capacity() / sizeof(Vertex);
    }
    
	////////////////////////////////////////////////////////////
        
    size_t VertexBuffer::capacity() const
    {
        GLint64 capacity;

        glGetNamedBufferParameteri64v(_handle, GL_BUFFER_SIZE, &capacity);

        return static_cast<size_t>(capacity);
    }

	////////////////////////////////////////////////////////////

    BufferUsage VertexBuffer::getUsage() const
    {
        GLint usage;

        glGetNamedBufferParameteriv(_handle, GL_BUFFER_USAGE, &usage);

        switch(usage)
        {
            case GL_STATIC_DRAW:  return BufferUsage::Static;
            case GL_DYNAMIC_DRAW: return BufferUsage::Dynamic;
            default:              return BufferUsage::Stream;
        }
    }
    
	////////////////////////////////////////////////////////////
        
	unsigned int VertexBuffer::getNativeHandle() const
    {
        return _handle;
    }
    
	////////////////////////////////////////////////////////////
	
    void VertexBuffer::release()
    {
        if(_handle != NullVertexBuffer)
        {
            glDeleteBuffers(1, &_handle);
            _handle = NullVertexBuffer;
        }
    }
}
