#pragma once

#include <optional>

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
    /// @interface IBufferMapContext
    /// @brief Interface that provides access to functions for working with buffer map
    ///
    template<typename T>
    class IBufferMapContext
    {
    public:
        virtual ~IBufferMapContext() = default;

        /// @brief Maps the buffer to make it accessible
        virtual void map(MapAccess access) = 0;

        /// @brief Unmaps the buffer
        virtual void unmap() = 0;

        /// @brief Get map status
        /// @return True if mapped, otherwise false
        virtual bool isMapped() const = 0;

        /// @brief Get the element by the index. Only work with the enabled mapping
        /// @param index The element's index
        /// @return Correct or incorrect buffer element
        virtual T& get(int index) = 0;

        /// @brief Safely get the element by the index. Only work with the enabled mapping
        /// @param index The element's index
        /// @return Correct buffer element or none
        virtual std::optional<T*> tryGet(int index) = 0;
    };
}
