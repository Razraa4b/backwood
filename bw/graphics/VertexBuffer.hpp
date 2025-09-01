#pragma once

#include <vector>
#include "Vertex.hpp"
#include "IResource.hpp"

namespace bw::low_level
{
    ///
    /// @class VertexBuffer
    /// @brief The class that wraps work with vertex buffers in the OpenGL API
    /// @implements IResource<unsigned int>
    /// 
	class VertexBuffer : public IResource<unsigned int>
	{
	public:
        ///
        /// @enum Usage
		/// @brief The type of vertex buffer data usage
		///
        enum Usage
		{
			Static,  // Never or very rarely updated
			Dynamic, // It updates quite often
			Stream   // Almost every frame is updated
		};

		/// @brief The handle for a non-existent vertex buffer
        static const unsigned int NoBuffer = 0;

        /// @brief Constructs a vertex buffer with specified usage, vertex data and count
        /// @param usage The usage pattern for the buffer
        /// @param vertices Pointer to the vertex data array
        /// @param count Number of vertices in the array
		VertexBuffer(Usage usage, Vertex* vertices, size_t count);
        
        /// @brief Constructs an empty vertex buffer with specified usage
        /// @param usage The usage pattern for the buffer
		VertexBuffer(Usage usage);
        
        /// @brief Constructs a vertex buffer with specified usage and capacity
        /// @param usage The usage pattern for the buffer
        /// @param count Capacity of the buffer in vertices
		VertexBuffer(Usage usage, size_t count);
        
        /// @brief Constructs a vertex buffer with specified usage and vertex data from vector
        /// @param usage The usage pattern for the buffer
        /// @param vertices Vector containing vertex data
		VertexBuffer(Usage usage, std::vector<Vertex>& vertices);

		VertexBuffer(const VertexBuffer& other);
		VertexBuffer(VertexBuffer&& moved) noexcept;

		~VertexBuffer();

		VertexBuffer& operator=(const VertexBuffer& other);
		VertexBuffer& operator=(VertexBuffer&& moved) noexcept;

        /// @brief Accesses a vertex at the specified index
        /// @param index Index of the vertex to access
        /// @return The vertex at the specified index
		Vertex operator[](int index) const;
        
        bool operator==(const VertexBuffer& other) const;
        bool operator!=(const VertexBuffer& other) const;

        /// @brief Updates a portion of the vertex buffer with new data
        /// @param offset Starting offset for the update
        /// @param vertices Pointer to the new vertex data
        /// @param count Number of vertices to update
		void update(size_t offset, Vertex* vertices, size_t count);
        
        /// @brief Updates a portion of the vertex buffer with new data from vector
        /// @param offset Starting offset for the update
        /// @param vertices Vector containing the new vertex data
		void update(size_t offset, std::vector<Vertex> vertices);

        /// @brief Reserves memory for the specified number of vertices. If there is already enough memory for the vertices, the operation will be canceled.
        /// @param count Number of vertices to reserve memory for
		void reserve(size_t count);

        /// @brief Retrieves a range of vertex data from the buffer
        /// @param offset Starting offset of the data to retrieve
        /// @param count Number of vertices to retrieve
        /// @return Vector containing the requested vertex data
		std::vector<Vertex> data(size_t offset, size_t count) const;
        
        /// @brief Retrieves all vertex data from the buffer
        /// @return Vector containing all vertex data
        /// @errors
		std::vector<Vertex> data() const;

        /// @brief Gets the total capacity of the buffer
        /// @return The capacity of the buffer in vertices
		size_t capacity() const;
        
        /// @brief Gets the current size of the buffer
        /// @return The current number of vertices in the buffer
		size_t size() const;

		// IResource interface implementation
        /// @brief Gets the native OpenGL handle for this buffer
        /// @return The OpenGL buffer handle
        unsigned int getNativeHandle() const override;
        
        /// @brief Releases the OpenGL resources associated with this buffer
		void release() const override;
	private:
		unsigned int _handle;
		Usage _usage;
	};
}
