#pragma once

#include <memory>
#include <queue>
#include <stack>
#include <vector>

namespace bw::low_level
{

    ///
    /// @enum MapAccess
    /// @brief Enumeration defining access modes for buffer mapping
    ///
    enum MapAccess
    {
        ReadOnly,
        WriteOnly,
        ReadAndWrite  
    };

    ///
    /// @interface IBufferMappingContext
    /// @brief Interface that provides access to functions for working with buffer map
    ///
    class IBufferMappingContext
    {
    public:
        virtual ~IBufferMappingContext() = default;

        /// @brief Maps the buffer to make it accessible
        virtual void map(MapAccess access) = 0;

        /// @brief Unmaps the buffer
        virtual void unmap() = 0;
    };
}
