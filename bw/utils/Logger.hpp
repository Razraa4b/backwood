#pragma once

#include <functional>
#include "ILogger.hpp"

namespace bw
{
	class Logger : public ILogger
	{
	public:
		using LogCallback = std::function<void(LogLevel, const std::string&)>;

		Logger(Logger&&) = delete;

		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		static Logger& getInstance();

		void setMinimumLevel(LogLevel level);
		void setCallback(LogCallback callback);

		LogLevel getMinimumLevel() const;
		
		void log(LogLevel level, const std::string& message) const;
		void trace(const std::string& message) const override;
		void debug(const std::string& message) const override;
		void info(const std::string& message) const override;
		void warn(const std::string& message) const override;
		void error(const std::string& message) const override;
		void critical(const std::string& message) const override;
		void fatal(const std::string& message) const override;
	private:
		Logger();

		LogCallback _callback;
		LogLevel _minimumLevel;
	};

	inline bool isLoggingDisabled() 
	{
		return bw::Logger::getInstance().getMinimumLevel() == bw::LogLevel::Disabled;
	}
}
