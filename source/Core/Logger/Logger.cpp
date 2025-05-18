#include "Logger.h"

#include <spdlog/spdlog.h>

SDLPG::Core::Logger::Logger::Logger()
{
  _rawLoggerSink = std::make_shared<widget_logger_sink_mt>();
  spdlog::default_logger_raw()->sinks().push_back(_rawLoggerSink);
}

SDLPG::Core::Logger::Logger& SDLPG::Core::Logger::Logger::Instance()
{
  static SDLPG::Core::Logger::Logger logger;

#if (SDLPG_DEBUG)
  logger.SetLevel(SDLPG::Core::Logger::Level::Debug);
#endif

  return logger;
}

void SDLPG::Core::Logger::Logger::SetLevel(SDLPG::Core::Logger::Level level)
{
  switch (level)
  {
  case SDLPG::Core::Logger::Level::Debug:
    spdlog::set_level(spdlog::level::level_enum::debug);
    break;
  case SDLPG::Core::Logger::Level::Info:
    spdlog::set_level(spdlog::level::level_enum::info);
    break;
  case SDLPG::Core::Logger::Level::Warn:
    spdlog::set_level(spdlog::level::level_enum::warn);
    break;
  case SDLPG::Core::Logger::Level::Error:
    spdlog::set_level(spdlog::level::level_enum::err);
    break;
  case SDLPG::Core::Logger::Level::Critical:
    spdlog::set_level(spdlog::level::level_enum::critical);
    break;
  default:
    break;
  }
}

void SDLPG::Core::Logger::Logger::Log(const std::string& x, SDLPG::Core::Logger::Level level)
{
  switch (level)
  {
  case SDLPG::Core::Logger::Level::Debug:
    Debug(x);
    break;
  case SDLPG::Core::Logger::Level::Info:
    Info(x);
    break;
  case SDLPG::Core::Logger::Level::Warn:
    Warn(x);
    break;
  case SDLPG::Core::Logger::Level::Error:
    Error(x);
    break;
  case SDLPG::Core::Logger::Level::Critical:
    Critical(x);
    break;
  default:
    break;
  }
}

void SDLPG::Core::Logger::Logger::Info(const std::string& x)
{
  spdlog::info(x);
}

void SDLPG::Core::Logger::Logger::Debug(const std::string& x)
{
  spdlog::debug(x);
}

void SDLPG::Core::Logger::Logger::Warn(const std::string& x)
{
  spdlog::warn(x);
}

void SDLPG::Core::Logger::Logger::Error(const std::string& x)
{
  spdlog::error(x);
}

void SDLPG::Core::Logger::Logger::Critical(const std::string& x)
{
  spdlog::critical(x);
}

std::shared_ptr<widget_logger_sink_mt> SDLPG::Core::Logger::Logger::GetRawLoggerSink()
{
  return _rawLoggerSink;
}
