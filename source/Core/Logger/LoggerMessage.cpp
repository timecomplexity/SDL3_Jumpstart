#include "LoggerMessage.h"

#include "Logger.h"

SDLPG::Core::Logger::LoggerMessage::LoggerMessage(SDLPG::Core::Logger::Level level) : _level(level)
{
}

SDLPG::Core::Logger::LoggerMessage::~LoggerMessage()
{
  SDLPG::Core::Logger::Logger::Instance().Log(_stream.str(), _level);
}
