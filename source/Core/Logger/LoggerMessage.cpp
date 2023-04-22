#include "LoggerMessage.h"

#include "Logger.h"

LV::Core::Logger::LoggerMessage::LoggerMessage(LV::Core::Logger::Level level) : _level(level)
{
}

LV::Core::Logger::LoggerMessage::~LoggerMessage()
{
  LV::Core::Logger::Logger::Instance().Log(_stream.str(), _level);
}
