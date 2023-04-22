#pragma once

#include <sstream>
#include <string>

#include "Export.h"
#include "LoggerLevel.h"

namespace LV::Core::Logger
{
  class LV_LOGGER_API LoggerMessage
  {
  public:
    LoggerMessage() = delete;
    LoggerMessage(LV::Core::Logger::Level level);
    virtual ~LoggerMessage();

    std::stringstream _stream;
    LV::Core::Logger::Level _level;
  };
} // namespace LV::Core
