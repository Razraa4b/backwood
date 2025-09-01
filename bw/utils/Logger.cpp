#include <iostream>
#include <format>
#include <chrono>
#include "utils/Logger.hpp"

namespace bw
{
	Logger::Logger() : _minimumLevel(LogLevel::Trace) 
	{
		_callback = [](LogLevel level, const std::string& message) {
			auto now = std::chrono::system_clock::now();
			auto time = std::chrono::system_clock::to_time_t(now);

			std::cout << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
				now.time_since_epoch()) % 1000;
			std::cout << "." << std::setfill('0') << std::setw(3) << milliseconds.count() << " ";

			switch (level) {
				case LogLevel::Trace: std::cout << "[TRACE] "; break;
				case LogLevel::Debug: std::cout << "[DEBUG] "; break;
				case LogLevel::Info: std::cout << "[INFO] "; break;
				case LogLevel::Warn: std::cout << "[WARN] "; break;
				case LogLevel::Error: std::cout << "[ERROR] "; break;
				case LogLevel::Crit: std::cout << "[CRITICAL] "; break;
				case LogLevel::Fatal: std::cout << "[FATAL] "; break;
				default: break;
			}

			std::cout << message << std::endl;
		};
	}

	////////////////////////////////////////////////////////////

	Logger& Logger::getInstance() 
	{
		static Logger instance;
		return instance;
	}

	////////////////////////////////////////////////////////////

	void Logger::setMinimumLevel(LogLevel level) 
	{
		_minimumLevel = level;
	}

	////////////////////////////////////////////////////////////

	void Logger::setCallback(LogCallback callback) 
	{
		_callback = std::move(callback);
	}

	////////////////////////////////////////////////////////////

	LogLevel Logger::getMinimumLevel() const
	{ 
		return _minimumLevel;
	}

	////////////////////////////////////////////////////////////

	void Logger::log(LogLevel level, const std::string& message) const
	{
		if (_callback && level >= _minimumLevel && level != LogLevel::Disabled)
		{
			_callback(level, message);
		}
	}

	////////////////////////////////////////////////////////////

	void Logger::trace(const std::string& message) const { log(LogLevel::Trace, message); }
	void Logger::debug(const std::string& message) const { log(LogLevel::Debug, message); }
	void Logger::info(const std::string& message) const { log(LogLevel::Info, message); }
	void Logger::warn(const std::string& message) const { log(LogLevel::Warn, message); }
	void Logger::error(const std::string& message) const { log(LogLevel::Error, message); }
	void Logger::critical(const std::string& message) const { log(LogLevel::Crit, message); }
	void Logger::fatal(const std::string& message) const { log(LogLevel::Fatal, message); }
}
