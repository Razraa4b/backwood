#pragma once

#include <span>
#include <vector>
#include "IBufferMapContext.hpp"

namespace bw::low_level
{
    ///
    /// @enum BufferUsage
    /// @brief Buffer usage type
    ///
    enum BufferUsage
    {
        Static,  // The data does not change, or it is very rare
        Dynamic, // The data changes quite often
        Stream   // The data is updated non-stop
    };

    ///
    /// @interface IBufferStorage
    /// @brief Interface that represents abstract buffer storage in OpenGL API
    /// @tparam T Buffer data type
    ///
    template <typename T>
    class IBufferStorage
    {
    public:
        virtual ~IBufferStorage() = default;
    
        ///
        /// @brief Reserve memory for the buffer without initializing it and deleting old data
        /// @param size Number of elements to reserve capacity for
        ///
        virtual void reserve(size_t size) = 0;
        
        ///
        /// @brief Update buffer contents with new data
        /// @param data Span containing the new data to update the buffer with
        ///
        virtual void update(std::span<T> data) = 0;
        
        ///
        /// @brief Copy contents of this buffer to another buffer
        /// @param buffer Destination buffer to copy data to
        ///
        virtual void copyTo(IBufferStorage& buffer) const = 0;

        ///
        /// @brief Get a copy of the buffer data
        /// @return Vector containing a copy of all buffer data
        ///
        virtual std::vector<T> data() const = 0;
        
        ///
        /// @brief Get the current max number of elements buffer can store
        /// @return Size of the buffer in number of elements
        ///
        virtual size_t size() const = 0;
        
        ///
        /// @brief Get the total capacity of the buffer
        /// @return Maximum number of elements the buffer can hold without reallocation
        ///
        virtual size_t capacity() const = 0;
    };
}
