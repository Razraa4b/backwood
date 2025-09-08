// VertexArray.hpp
#pragma once

#include <vector>
#include "IResource.hpp"
#include "Vertex.hpp"

namespace bw::low_level
{
    class VertexBuffer;
    class ElementBuffer;

    ///
    /// @class VertexArray
    /// @brief Class that wraps the functionality of vertex arrays in the OpenGL API
    /// @implements IResource<unsigned int>
    ///
    class VertexArray : public IResource<unsigned int>
    {
    public:
        ///
        /// @struct Range
        /// @brief Structure representing the range of data that the vertex sees
        ///
        struct Range
        {
            /// @brief Start index
            size_t start;
            /// @brief Vertex count
            size_t count;

            Range(size_t start, size_t count) : start(start), count(count) { }
            Range() : Range(0, 0) { }
        };

        /// @brief Constant for a non-existent vertex array
        static const unsigned int NullVertexArray = 0;

        /// @brief Creates and initializes vertex array
        VertexArray();
        
        /// @brief Creates and initializes vertex array and binds vertex buffer with range
        /// @param buffer Vertex buffer to bind
        /// @param range Available range of vertices
        VertexArray(VertexBuffer& buffer, Range range);
        
        /// @brief Creates and initializes vertex array and binds vertex buffer
        /// @param buffer Vertex buffer to bind
        VertexArray(VertexBuffer& buffer);

        VertexArray(const VertexArray& other);
        VertexArray(VertexArray&& moved) noexcept;

        ~VertexArray();

        VertexArray& operator=(const VertexArray& other);
        VertexArray& operator=(VertexArray&& moved) noexcept;

        bool operator==(const VertexArray& other);
        bool operator!=(const VertexArray& other);

        /// @brief Binds vertex array to vertex buffer
        /// @param buffer Vertex buffer to bind
        void bindTo(VertexBuffer& buffer);

        /// @brief Binds vertex array to vertex buffer with range
        /// @param buffer Vertex buffer to bind
        /// @param range Available range of vertices
        void bindTo(VertexBuffer& buffer, Range range);

        /// @brief Binds element buffer to vertex array
        /// @param elementBuffer Element buffer to bind
        void bindTo(ElementBuffer& elementBuffer);

        /// @brief Gets current binded vertex buffer
        /// @return Current vertex buffer (nullptr possible)
        VertexBuffer* getCurrentVertexBuffer();

        /// @brief Gets current binded element buffer
        /// @return Current element buffer or nullptr if not bound (nullptr possible)
        ElementBuffer* getCurrentElementBuffer();

        /// @brief Gets current vertex range
        /// @return Current range
        Range getRange() const;

        /// @brief Gets vertex array native handle
        /// @return OpenGL vertex array handle
        unsigned int getNativeHandle() const override;
        
        /// @brief Deletes vertex array
        void release() override;

    private:
        unsigned int _handle;
        VertexBuffer* _vertexBuffer;
        ElementBuffer* _elementBuffer;
        Range _range;
    };
}
