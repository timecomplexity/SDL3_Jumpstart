#include "Logger.h"

#include <spdlog/spdlog.h>

LV::Core::Logger::Logger::Logger()
{
  _rawLoggerSink = std::make_shared<widget_logger_sink_mt>();
  spdlog::default_logger_raw()->sinks().push_back(_rawLoggerSink);
}

LV::Core::Logger::Logger& LV::Core::Logger::Logger::Instance()
{
  static LV::Core::Logger::Logger logger;

#if (LV_DEBUG)
  logger.SetLevel(LV::Core::Logger::Level::Debug);
#endif

  return logger;
}

void LV::Core::Logger::Logger::SetLevel(LV::Core::Logger::Level level)
{
  switch (level)
  {
  case LV::Core::Logger::Level::Debug:
    spdlog::set_level(spdlog::level::level_enum::debug);
    break;
  case LV::Core::Logger::Level::Info:
    spdlog::set_level(spdlog::level::level_enum::info);
    break;
  case LV::Core::Logger::Level::Warn:
    spdlog::set_level(spdlog::level::level_enum::warn);
    break;
  case LV::Core::Logger::Level::Error:
    spdlog::set_level(spdlog::level::level_enum::err);
    break;
  case LV::Core::Logger::Level::Critical:
    spdlog::set_level(spdlog::level::level_enum::critical);
    break;
  default:
    break;
  }
}

void LV::Core::Logger::Logger::Log(const std::string& x, LV::Core::Logger::Level level)
{
  switch (level)
  {
  case LV::Core::Logger::Level::Debug:
    Debug(x);
    break;
  case LV::Core::Logger::Level::Info:
    Info(x);
    break;
  case LV::Core::Logger::Level::Warn:
    Warn(x);
    break;
  case LV::Core::Logger::Level::Error:
    Error(x);
    break;
  case LV::Core::Logger::Level::Critical:
    Critical(x);
    break;
  default:
    break;
  }
}

void LV::Core::Logger::Logger::Info(const std::string& x)
{
  spdlog::info(x);
}

void LV::Core::Logger::Logger::Debug(const std::string& x)
{
  spdlog::debug(x);
}

void LV::Core::Logger::Logger::Warn(const std::string& x)
{
  spdlog::warn(x);
}

void LV::Core::Logger::Logger::Error(const std::string& x)
{
  spdlog::error(x);
}

void LV::Core::Logger::Logger::Critical(const std::string& x)
{
  spdlog::critical(x);
}

std::shared_ptr<widget_logger_sink_mt> LV::Core::Logger::Logger::GetRawLoggerSink()
{
  return _rawLoggerSink;
}
