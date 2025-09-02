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

	VertexBuffer::VertexBuffer(Usage usage, Vertex* vertices, int count) : _handle(NoBuffer), _usage(usage)
	{
		glCreateBuffers(1, &_handle);
		glNamedBufferData(_handle, count * sizeof(Vertex), vertices, glUsageToEnum(usage));
	}

	////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(Usage usage) : VertexBuffer(usage, nullptr, 0) { }

	////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(Usage usage, int count) : VertexBuffer(usage, nullptr, count) { }

	////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(Usage usage, std::vector<Vertex>& vertices) : VertexBuffer(usage, vertices.data(), vertices.size())  { }

	////////////////////////////////////////////////////////////

    VertexBuffer::VertexBuffer(const VertexBuffer& other) : _handle(NoBuffer), _usage(other._usage)
    {
        int size = other.size();
        std::vector<Vertex> vertices = other.data(0, size);
        
		glCreateBuffers(1, &_handle);
		glNamedBufferData(_handle, size * sizeof(Vertex), vertices.data(), glUsageToEnum(other._usage));
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

	void VertexBuffer::update(int offset, Vertex* vertices, int count)
	{
		glNamedBufferSubData(_handle, offset * sizeof(Vertex), count * sizeof(Vertex), vertices);
	}

	////////////////////////////////////////////////////////////

	void VertexBuffer::update(int offset, std::vector<Vertex> vertices)
	{
		update(offset, vertices.data(), vertices.size());
	}

	////////////////////////////////////////////////////////////

	void VertexBuffer::reserve(int count)
	{
		int requiredCapacity = count * sizeof(Vertex);
		int currentCapacity = this->capacity();

		if (currentCapacity >= requiredCapacity) return;

		std::vector<Vertex> oldData = data();

		glNamedBufferData(_handle, requiredCapacity, oldData.data(), glUsageToEnum(_usage));
	}

	////////////////////////////////////////////////////////////

	std::vector<Vertex> VertexBuffer::data(int offset, int count) const
	{
		std::vector<Vertex> data(count);
		glGetNamedBufferSubData(_handle, offset * sizeof(Vertex), count * sizeof(Vertex), data.data());
		return data;
	}

	////////////////////////////////////////////////////////////

	std::vector<Vertex> VertexBuffer::data() const
	{
		return data(0, size());
	}

	////////////////////////////////////////////////////////////

	int VertexBuffer::capacity() const
	{
		int size;
		glGetNamedBufferParameteriv(_handle, GL_BUFFER_SIZE, &size);
		return size;
	}

	////////////////////////////////////////////////////////////

	int VertexBuffer::size() const
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
