#pragma once

#include <string>

namespace bw
{
	///
	/// @enum LogLevel
	/// @brief Enumeration of logging severity levels
	///
	enum LogLevel
	{
		Trace,   /// Information about each step in the process
		Debug,   /// General debugging information  
		Info,    /// Informational messages
		Warn,    /// Warning conditions
		Error,   /// Error conditions
		Crit,    /// Critical conditions
		Fatal,   /// Fatal errors leading to termination
		Disabled /// Set as a minimum level for disabling logs
	};

	////////////////////////////////////////////////////////////

	///
	/// @class ILogger
	/// @brief Interface that provides functions for logs
	///
	class ILogger
	{
	public:
		virtual ~ILogger() = default;

		virtual void log(LogLevel level, const std::string& message) const = 0;
		virtual void trace(const std::string& message) const = 0;
		virtual void debug(const std::string& message) const = 0;
		virtual void info(const std::string& message) const = 0;
		virtual void warn(const std::string& message) const = 0;
		virtual void error(const std::string& message) const = 0;
		virtual void critical(const std::string& message) const = 0;
		virtual void fatal(const std::string& message) const = 0;
	};
}
