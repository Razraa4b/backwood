#pragma once

#include <optional>

namespace bw
{
	///
	/// @interface IResource
	/// @brief Interface representing a graphical resource
	///
	template<typename THandle>
	class IResource
	{
	public:
        virtual ~IResource() = default;

		/// @brief Gets resource native handle
		/// @return Resource handle
		virtual THandle getNativeHandle() const = 0;
		
        /// @brief Releases resource data
        virtual void release() const = 0;
	};
}
