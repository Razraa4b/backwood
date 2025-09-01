#include <exception>
#include <glad/glad.h>
#include "VertexBuffer.hpp"

namespace bw::low_level
{
	GLenum glUsageToEnum(VertexBuffer::Usage usage)
	{
		switch (usage)
		{
			case VertexBuffer::Static:  return GL_STATIC_DRAW;
			case VertexBuffer::Dynamic: return GL_DYNAMIC_DRAW;
			default:                    return GL_STREAM_DRAW;
		}
	}

	////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(Usage usage, Vertex* vertices, size_t count) : _handle(NoBuffer), _usage(usage)
	{
		glGenBuffers(1, &_handle);

		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(Vertex), vertices, glUsageToEnum(usage));
		glBindBuffer(GL_ARRAY_BUFFER, NoBuffer);
	}

	////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(Usage usage) : VertexBuffer(usage, nullptr, 0) { }

	////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(Usage usage, size_t count) : VertexBuffer(usage, nullptr, count) { }

	////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(Usage usage, std::vector<Vertex>& vertices) : VertexBuffer(usage, vertices.data(), vertices.size())  { }

	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(const VertexBuffer& other) : _handle(NoBuffer), _usage(other._usage)
    {
        int size = other.size();
        std::vector<Vertex> vertices = other.data(0, size);
        
		glGenBuffers(1, &_handle);
        
		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), vertices.data(), glUsageToEnum(other._usage));
		glBindBuffer(GL_ARRAY_BUFFER, NoBuffer);
    }

	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(VertexBuffer&& moved) noexcept : _handle(moved._handle), _usage(moved._usage)
    {
        moved._handle = NoBuffer;
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
            release();

            int size = other.size();
            std::vector<Vertex> vertices = other.data(0, size);
        
            if(size < vertices.size())
            {
                size = vertices.size();
                this->reserve(vertices.size());
            }

		    this->update(0, vertices);
        }

        return *this;
    }

	////////////////////////////////////////////////////////////

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& moved) noexcept
    {
        if(this != &moved)
        {
            release();

            _handle = std::move(moved._handle);
            _usage = std::move(moved._usage);

            moved._handle = NoBuffer;
        }

        return *this;
    }
	
	////////////////////////////////////////////////////////////

	Vertex VertexBuffer::operator[](int index) const
	{
		return data(index, 1)[0];
	}

	////////////////////////////////////////////////////////////

    bool VertexBuffer::operator==(const VertexBuffer& other) const
    {
        return this->_handle == other._handle;
    }
    
	////////////////////////////////////////////////////////////

    bool VertexBuffer::operator!=(const VertexBuffer& other) const
    {
        return !(*this == other);
    }

	////////////////////////////////////////////////////////////

	void VertexBuffer::update(size_t offset, Vertex* vertices, size_t count)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		
		glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(Vertex), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, NoBuffer);
	}

	////////////////////////////////////////////////////////////

	void VertexBuffer::update(size_t offset, std::vector<Vertex> vertices)
	{
		update(offset, vertices.data(), vertices.size());
	}

	////////////////////////////////////////////////////////////

	void VertexBuffer::reserve(size_t count)
	{
		size_t requiredCapacity = count * sizeof(Vertex);
		size_t currentCapacity = this->capacity();

		if (currentCapacity >= requiredCapacity) return;

		std::vector<Vertex> oldData = data();

		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glBufferData(GL_ARRAY_BUFFER, requiredCapacity, oldData.data(), glUsageToEnum(_usage));
		glBindBuffer(GL_ARRAY_BUFFER, NoBuffer);
	}

	////////////////////////////////////////////////////////////

	std::vector<Vertex> VertexBuffer::data(size_t offset, size_t count) const
	{
		std::vector<Vertex> data(count);

		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glGetBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), count * sizeof(Vertex), data.data());
		glBindBuffer(GL_ARRAY_BUFFER, NoBuffer);
		
		return data;
	}

	////////////////////////////////////////////////////////////

	std::vector<Vertex> VertexBuffer::data() const
	{
		return data(0, size());
	}

	////////////////////////////////////////////////////////////

	size_t VertexBuffer::capacity() const
	{
		int size;

		glBindBuffer(GL_ARRAY_BUFFER, _handle);
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glBindBuffer(GL_ARRAY_BUFFER, NoBuffer);
		
		return size;
	}

	////////////////////////////////////////////////////////////

	size_t VertexBuffer::size() const
	{
		return capacity() / sizeof(Vertex);
	}

	////////////////////////////////////////////////////////////

	unsigned int VertexBuffer::getNativeHandle() const
	{
		return _handle;
	}

	////////////////////////////////////////////////////////////

	void VertexBuffer::release() const
	{
		if (_handle != NoBuffer)
			glDeleteBuffers(1, &_handle);
	}
}
