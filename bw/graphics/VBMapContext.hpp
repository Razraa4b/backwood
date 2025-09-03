#pragma once

#include "IBufferMapContext.hpp"
#include "Vertex.hpp"

namespace bw::low_level
{
    class VertexBuffer;

    ///
    /// @class VBMapContext
    /// @brief 
    /// @implements IBufferMapContext<Vertex>
    ///
    class VBMapContext : public IBufferMapContext<Vertex>
    {
    public:
        VBMapContext(VertexBuffer& buffer);

        VBMapContext(const VBMapContext& other) = delete;
        VBMapContext(VBMapContext&& moved);

        ~VBMapContext();

        VBMapContext& operator=(const VBMapContext& other) = delete;
        VBMapContext& operator=(VBMapContext&& moved);

        Vertex& operator[](int index);
        const Vertex& operator[](int index) const;

        /// @brief Maps the buffer to make it accessible if it not mapped yet
        void map(MapAccess access) override;

        /// @brief Unmaps the buffer if it mapped
        void unmap() override;

        /// @brief Get map status
        /// @return True if mapped, otherwise false
        bool isMapped() const override;

        /// @brief Get the vertex by the index. Only work with the enabled mapping
        /// @param index The vertex's index
        /// @return Correct or incorrect buffer vertex
        Vertex& get(int index) override;

        /// @brief Safely get the vertex by the index. Only work with the enabled mapping
        /// @param index The vertex's index
        /// @return Correct buffer vertex or none
        std::optional<Vertex*> tryGet(int index) override;
    private:
        VertexBuffer* _buffer;
        Vertex* _data;
    };
}
