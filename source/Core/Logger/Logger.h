#pragma once

#include <string>

#include "Export.h"
#include "LoggerLevel.h"
#include "LoggerMessage.h"
#include "LoggerSink.h"

namespace LV::Core::Logger
{
  class SDLPG_LOGGER_API Logger
  {
  public:
    static Logger& Instance();

    std::shared_ptr<widget_logger_sink_mt> GetRawLoggerSink();

    static void SetLevel(LV::Core::Logger::Level level);

    static void Log(const std::string& x, LV::Core::Logger::Level level);
    static void Info(const std::string& x);
    static void Debug(const std::string& x);
    static void Warn(const std::string& x);
    static void Error(const std::string& x);
    static void Critical(const std::string& x);

  private:
    Logger();
    std::shared_ptr<widget_logger_sink_mt> _rawLoggerSink;
  };
} // namespace LV::Core::Logger

#define SDLPG_LOG_INFO LV::Core::Logger::LoggerMessage(LV::Core::Logger::Level::Info)._stream
#define SDLPG_LOG_DEBUG LV::Core::Logger::LoggerMessage(LV::Core::Logger::Level::Debug)._stream
#define SDLPG_LOG_WARN LV::Core::Logger::LoggerMessage(LV::Core::Logger::Level::Warn)._stream
#define SDLPG_LOG_ERROR LV::Core::Logger::LoggerMessage(LV::Core::Logger::Level::Error)._stream
#define SDLPG_LOG_CRITICAL LV::Core::Logger::LoggerMessage(LV::Core::Logger::Level::Critical)._stream
