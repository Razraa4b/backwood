#pragma once

#include "IBufferStorage.hpp"
#include "IResource.hpp"
#include "Vertex.hpp"

namespace bw::low_level
{
    /// 
    /// @class VertexBuffer
    /// @brief Class that wraps the functionality of vertex buffers in the OpenGL API
    /// @implements IBufferStorage<Vertex>, IResource<unsigned int>
    ///
    class VertexBuffer : public virtual IBufferStorage<Vertex>, 
                         public virtual IResource<unsigned int>
    {
    public:
        /// @brief Constant for a non-existent vertex buffer
        static const unsigned int NullVertexBuffer = 0;

        /// @brief Initializes and creates an empty buffer with no memory
        /// @param usage Buffer usage type
        VertexBuffer(BufferUsage usage);
        
        /// @brief Initializes and creates a buffer, and then fills it with the data
        /// @param usage Buffer usage type
        /// @param initializer Initialization data
        VertexBuffer(BufferUsage usage, std::span<Vertex> initializer);
        
        /// @brief Initializes and creates a buffer, then reserves memory for future data
        /// @param usage Buffer usage type
        /// @param reserveSize Number of vertices for which memory will be allocated
        VertexBuffer(BufferUsage usage, size_t reserveSize);

        VertexBuffer(const VertexBuffer& other);
        VertexBuffer(VertexBuffer&& moved) noexcept;

        ~VertexBuffer();
        
        VertexBuffer& operator=(const VertexBuffer& other);
        VertexBuffer& operator=(VertexBuffer&& moved) noexcept;

        bool operator==(const VertexBuffer& other) const;
        bool operator!=(const VertexBuffer& other) const;

        /// @brief Reserve memory for the vertex buffer without initializing it and deleting old data
        /// @param size Number of elements to reserve capacity for
        void reserve(size_t size) override;
        
        /// @brief Update vertex buffer contents with new data
        /// @param data Span containing the new data to update the vertex buffer with
        void update(std::span<Vertex> vertices) override;

        /// @brief Update vertex buffer contents with new data
        /// @param offset Offset from the beginning of the previous data
        /// @param data Span containing the new data to update the vertex buffer with
        void update(size_t offset, std::span<Vertex> vertices);        

        /// @brief Copy contents of this vertex buffer to another buffer
        /// @param buffer Destination vertex buffer to copy data to
        void copyTo(IBufferStorage<Vertex>& buffer) const override;

        /// @brief Get a copy of the vertex buffer data
        /// @return Vector containing a copy of all vertex buffer data
        std::vector<Vertex> data() const override;        

        /// @brief Get a copy of the vertex buffer data
        /// @return Vector containing a copy of the data of the specified range in the vertex buffer
        /// @param offset Offset from the beginning of the data
        /// @param size Count of the vertices
        std::vector<Vertex> data(size_t offset, size_t size) const;
        
        /// @brief Get the current number of elements in the vertex buffer
        /// @return Size of the vertex buffer in number of elements
        size_t size() const override;
        
        /// @brief Get the total capacity of the vertex buffer
        /// @return Maximum memory the buffer can hold without reallocation
        size_t capacity() const override;

        /// @brief Get the current usage type of the vertex buffer
        /// @return Vertex buffer usage type
        BufferUsage getUsage() const;
        
		/// @brief Gets vertex buffer native handle
		/// @return OpenGL vertex buffer handle
		unsigned int getNativeHandle() const override;
		
        /// @brief Releases vertex buffer memory
        void release() const override;
    private:
        unsigned int _handle;
    };
}
