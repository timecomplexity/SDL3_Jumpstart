#pragma once

#include <string>

#include "Export.h"
#include "LoggerLevel.h"
#include "LoggerMessage.h"
#include "LoggerSink.h"

namespace SDLPG::Core::Logger
{
  class SDLPG_LOGGER_API Logger
  {
  public:
    static Logger& Instance();

    std::shared_ptr<widget_logger_sink_mt> GetRawLoggerSink();

    static void SetLevel(SDLPG::Core::Logger::Level level);

    static void Log(const std::string& x, SDLPG::Core::Logger::Level level);
    static void Info(const std::string& x);
    static void Debug(const std::string& x);
    static void Warn(const std::string& x);
    static void Error(const std::string& x);
    static void Critical(const std::string& x);

  private:
    Logger();
    std::shared_ptr<widget_logger_sink_mt> _rawLoggerSink;
  };
} // namespace SDLPG::Core::Logger

#define SDLPG_LOG_INFO SDLPG::Core::Logger::LoggerMessage(SDLPG::Core::Logger::Level::Info)._stream
#define SDLPG_LOG_DEBUG SDLPG::Core::Logger::LoggerMessage(SDLPG::Core::Logger::Level::Debug)._stream
#define SDLPG_LOG_WARN SDLPG::Core::Logger::LoggerMessage(SDLPG::Core::Logger::Level::Warn)._stream
#define SDLPG_LOG_ERROR SDLPG::Core::Logger::LoggerMessage(SDLPG::Core::Logger::Level::Error)._stream
#define SDLPG_LOG_CRITICAL SDLPG::Core::Logger::LoggerMessage(SDLPG::Core::Logger::Level::Critical)._stream
