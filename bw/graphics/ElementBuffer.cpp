#include <stdexcept>
#include <glad/glad.h>
#include "ElementBuffer.hpp"

namespace bw::low_level
{
    GLenum eb_bufferUsageToGLEnum(BufferUsage usage)
    {
        switch(usage)
        {
            case BufferUsage::Static:  return GL_STATIC_DRAW;
            case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
            default:                   return GL_STREAM_DRAW;
        }
    }
    
	////////////////////////////////////////////////////////////

    ElementBuffer::ElementBuffer(BufferUsage usage) : _handle(NullElementBuffer)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, 0, nullptr, eb_bufferUsageToGLEnum(usage));
    }
     
	////////////////////////////////////////////////////////////

    ElementBuffer::ElementBuffer(BufferUsage usage, std::span<size_t> initializer) : _handle(NullElementBuffer)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, initializer.size() * sizeof(size_t), 
                          initializer.data(), eb_bufferUsageToGLEnum(usage));
    }
    
	////////////////////////////////////////////////////////////

    ElementBuffer::ElementBuffer(BufferUsage usage, size_t reserveSize) : _handle(NullElementBuffer)
    {
        glCreateBuffers(1, &_handle);
        glNamedBufferData(_handle, reserveSize * sizeof(size_t), nullptr, eb_bufferUsageToGLEnum(usage));
    }
    
	////////////////////////////////////////////////////////////

    ElementBuffer::ElementBuffer(const ElementBuffer& other) : _handle(NullElementBuffer)
    {
        glCreateBuffers(1, &_handle);
        this->reserve(other.size());
        other.copyTo(*this);
    }
                       
	////////////////////////////////////////////////////////////

    ElementBuffer::ElementBuffer(ElementBuffer&& moved) noexcept : _handle(NullElementBuffer)
    {
        _handle = moved._handle;
        moved._handle = NullElementBuffer;
    }
    
	////////////////////////////////////////////////////////////
    
    ElementBuffer::~ElementBuffer()
    {
        release();
    }

	////////////////////////////////////////////////////////////
    
    ElementBuffer& ElementBuffer::operator=(const ElementBuffer& other)
    {
        if(this != &other)
        {
            other.copyTo(*this);
        }
        return *this;
    }

	////////////////////////////////////////////////////////////

    ElementBuffer& ElementBuffer::operator=(ElementBuffer&& moved) noexcept
    {
        if(this != &moved)
        {
            this->release();

            _handle = moved._handle;
            moved._handle = NullElementBuffer;   
        }
        return *this;
    }

	////////////////////////////////////////////////////////////
    
    bool ElementBuffer::operator==(const ElementBuffer& other) const
    {
        return this == &other;
    }
	
    ////////////////////////////////////////////////////////////

    bool ElementBuffer::operator!=(const ElementBuffer& other) const
    {
        return !(*this == other);
    }

	////////////////////////////////////////////////////////////
        
    void ElementBuffer::reserve(size_t size)
    {
        size_t currentSize = this->size();
        if (size <= currentSize) return;

        std::vector<size_t> oldData { data() };
        glNamedBufferData(_handle, size * sizeof(size_t), oldData.data(), eb_bufferUsageToGLEnum(getUsage()));
    }
    
	////////////////////////////////////////////////////////////

    void ElementBuffer::update(size_t offset, std::span<size_t> indices)
    {
        glNamedBufferSubData(_handle, offset  * sizeof(size_t), indices.size()  * sizeof(size_t), indices.data());
    }

	////////////////////////////////////////////////////////////
    
    void ElementBuffer::update(std::span<size_t> indices)
    {
        update(0, indices);
    }

	////////////////////////////////////////////////////////////
    
    void ElementBuffer::copyTo(IBufferStorage<size_t>& buffer) const
    {
        if (auto* elementBuffer = dynamic_cast<ElementBuffer*>(&buffer)) 
        {
            if (elementBuffer->capacity() < capacity()) {
                elementBuffer->reserve(this->size());
            }
            glCopyNamedBufferSubData(_handle, elementBuffer->_handle, 0, 0, capacity());
        }
        else 
        {
            std::vector<size_t> data = this->data();
            buffer.update(data);
        }
    }

	////////////////////////////////////////////////////////////
    
    std::vector<size_t> ElementBuffer::data() const
    {
        return data(0, size());
    }

	////////////////////////////////////////////////////////////

    std::vector<size_t> ElementBuffer::data(size_t offset, size_t size) const
    {
        std::vector<size_t> container(size);
        glGetNamedBufferSubData(_handle, offset  * sizeof(size_t), size * sizeof(size_t), container.data());
        return container;
    }
    
	////////////////////////////////////////////////////////////
    
    size_t ElementBuffer::size() const
    {
        return capacity() / sizeof(size_t);
    }
    
	////////////////////////////////////////////////////////////
        
    size_t ElementBuffer::capacity() const
    {
        GLint64 capacity;

        glGetNamedBufferParameteri64v(_handle, GL_BUFFER_SIZE, &capacity);

        return static_cast<size_t>(capacity);
    }

	////////////////////////////////////////////////////////////

    BufferUsage ElementBuffer::getUsage() const
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
        
	unsigned int ElementBuffer::getNativeHandle() const
    {
        return _handle;
    }
    
	////////////////////////////////////////////////////////////
		
    void ElementBuffer::release()
    {
        if(_handle != NullElementBuffer)
        {
            glDeleteBuffers(1, &_handle);
            _handle = NullElementBuffer;
        }
    }
}
