#pragma once

#include "IBufferStorage.hpp"
#include "IResource.hpp"

namespace bw::low_level
{
    class ElementBuffer : public virtual IBufferStorage<size_t>, 
                          public virtual IResource<unsigned int>
    {
    public:
        /// @brief Constant for a non-existent element buffer
        static const unsigned int NullElementBuffer = 0;

        /// @brief Initializes and creates an empty buffer with no memory
        /// @param usage Buffer usage type
        ElementBuffer(BufferUsage usage);
        
        /// @brief Initializes and creates a buffer, and then fills it with the data
        /// @param usage Buffer usage type
        /// @param initializer Initialization data
        ElementBuffer(BufferUsage usage, std::span<size_t> initializer);
        
        /// @brief Initializes and creates a buffer, then reserves memory for future data
        /// @param usage Buffer usage type
        /// @param reserveSize Number of indices for which memory will be allocated
        ElementBuffer(BufferUsage usage, size_t reserveSize);

        ElementBuffer(const ElementBuffer& other);
        ElementBuffer(ElementBuffer&& moved) noexcept;

        ~ElementBuffer();
        
        ElementBuffer& operator=(const ElementBuffer& other);
        ElementBuffer& operator=(ElementBuffer&& moved) noexcept;

        bool operator==(const ElementBuffer& other) const;
        bool operator!=(const ElementBuffer& other) const;

        /// @brief Reserve memory for the element buffer without initializing it and deleting old data
        /// @param size Number of elements to reserve capacity for
        void reserve(size_t size) override;
        
        /// @brief Update element buffer contents with new data
        /// @param data Span containing the new data to update the element buffer with
        void update(std::span<size_t> indices) override;

        /// @brief Update element buffer contents with new data
        /// @param offset Offset from the beginning of the previous data
        /// @param data Span containing the new data to update the element buffer with
        void update(size_t offset, std::span<size_t> indices);        

        /// @brief Copy contents of this element buffer to another buffer
        /// @param buffer Destination element buffer to copy data to
        void copyTo(IBufferStorage<size_t>& buffer) const override;

        /// @brief Get a copy of the element buffer data
        /// @return Vector containing a copy of all element buffer data
        std::vector<size_t> data() const override;        

        /// @brief Get a copy of the element buffer data
        /// @return Vector containing a copy of the data of the specified range in the element buffer
        /// @param offset Offset from the beginning of the data
        /// @param size Count of the indices
        std::vector<size_t> data(size_t offset, size_t size) const;
        
        /// @brief Get the current max number of indices buffer can store
        /// @return Size of the element buffer in number of indices
        size_t size() const override;
        
        /// @brief Get the total capacity of the element buffer
        /// @return Maximum memory the buffer can hold without reallocation
        size_t capacity() const override;

        /// @brief Get the current usage type of the element buffer
        /// @return size_t buffer usage type
        BufferUsage getUsage() const;
        
		/// @brief Gets element buffer native handle
		/// @return OpenGL element buffer handle
		unsigned int getNativeHandle() const override;
		
        /// @brief Releases element buffer memory
        void release() override;
    private:
        unsigned int _handle;
    };
}
