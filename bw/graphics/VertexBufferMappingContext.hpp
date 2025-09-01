#pragma once

#include "IBufferMappingContext.hpp"
#include "Vertex.hpp"

namespace bw::low_level
{
    class VertexBuffer;

    ///
    /// @class VertexBufferMappingContext
    /// @brief 
    ///
    /// @implements IBufferMappingContext<Vertex>
    ///
    class VertexBufferMappingContext : IBufferMappingContext
    {
    public:
        VertexBufferMappingContext(VertexBuffer& buffer);
        ~VertexBufferMappingContext();
    
        /// @brief Subscript operator for accessing elements
        /// @param index Index of the element to access
        /// @return Reference to the element at the specified index
        Vertex& operator[](int index);

        /// @brief Const subscript operator for accessing elements
        /// @param index Index of the element to access
        /// @return Const re ference to the element at the specified index
        const Vertex& operator[](int index) const;

        /// @brief Maps the buffer to make it accessible
        void map(MapAccess access) override;

        /// @brief Unmaps the buffer
        void unmap() override;

        /// @brief Gets C-like pointer to start of array
        /// @return Pointer to start of data array 
        Vertex* getPurePointer();

        /// @brief Gets buffer mapped state
        /// @return True if buffer mapped, otherwise false
        bool isMapped() const;
    private:
        VertexBuffer& _buffer;
        bool _isMapped;
        Vertex* _data;
    };
}
