#pragma once

#include <sstream>
#include <string>

#include "Export.h"
#include "LoggerLevel.h"

namespace SDLPG::Core::Logger
{
  class SDLPG_LOGGER_API LoggerMessage
  {
  public:
    LoggerMessage() = delete;
    LoggerMessage(SDLPG::Core::Logger::Level level);
    virtual ~LoggerMessage();

    std::stringstream _stream;
    SDLPG::Core::Logger::Level _level;
  };
} // namespace SDLPG::Core
