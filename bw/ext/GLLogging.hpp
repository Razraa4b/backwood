#pragma once

#include "utils/Logger.hpp"

#define GL_LOG(level, message) bw::Logger::getInstance().log(level, std::format("[GL] {}", message))
#define GL_TRACE(message) bw::Logger::getInstance().trace(std::format("[GL] {}", message))
#define GL_DEBUG(message) bw::Logger::getInstance().debug(std::format("[GL] {}", message))
#define GL_INFO(message) bw::Logger::getInstance().info(std::format("[GL] {}", message))
#define GL_WARN(message) bw::Logger::getInstance().warn(std::format("[GL] {}", message))
#define GL_ERROR(message) bw::Logger::getInstance().error(std::format("[GL] {}", message))
#define GL_CRITICAL(message) bw::Logger::getInstance().critical(std::format("[GL] {}", message))
#define GL_FATAL(message) bw::Logger::getInstance().fatal(std::format("[GL] {}", message))
