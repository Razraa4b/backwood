#pragma once

#include "IBufferMapContext.hpp"

namespace bw::low_level
{
    class ElementBuffer;

    ///
    /// @class EBMapContext
    /// @brief Class for working with mapping element buffers
    /// @implements IBufferMapContext<size_t>
    ///
    class EBMapContext : public IBufferMapContext<size_t>
    {
    public:
        EBMapContext(ElementBuffer& buffer);

        EBMapContext(const EBMapContext&) = delete;
        EBMapContext(EBMapContext&& moved);

        ~EBMapContext();

        EBMapContext& operator=(const EBMapContext&) = delete;
        EBMapContext& operator=(EBMapContext&& moved);

        size_t& operator[](int index);
        const size_t& operator[](int index) const;

        /// @brief Maps the buffer to make it accessible if it not mapped yet
        void map(MapAccess access) override;

        /// @brief Unmaps the buffer if it mapped
        void unmap() override;

        /// @brief Get map status
        /// @return True if mapped, otherwise false
        bool isMapped() const override;

        /// @brief Get the index by the index. Only work with the enabled mapping
        /// @param index The element index
        /// @return Correct or incorrect buffer size_t
        size_t& get(int index) override;

        /// @brief Safely get the index by the index. Only work with the enabled mapping
        /// @param index The element index
        /// @return Correct buffer element or none
        std::optional<size_t*> tryGet(int index) override;
    private:
        ElementBuffer* _buffer;
        size_t* _data;
    };
}
