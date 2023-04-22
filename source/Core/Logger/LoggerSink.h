#pragma once

#include <queue>

#include <spdlog/spdlog.h>
#include <spdlog/details/log_msg.h>
#include <spdlog/sinks/base_sink.h>

#include <iostream>

// Sink intended to be used to feed spdlog into logger widget
template <typename Mutex>
class LoggerSink : public spdlog::sinks::base_sink<Mutex>
{
public:
  LoggerSink() = default;

  void GetMessage(std::vector<std::string>& messages)
  {
    while (!_messages.empty())
    {
      messages.push_back(_messages.front());
      _messages.pop();
    }
  }

protected:
  void sink_it_(const spdlog::details::log_msg& msg) override
  {
    spdlog::memory_buf_t formatted;
    spdlog::sinks::base_sink<std::mutex>::formatter_->format(msg, formatted);

    _messages.push(fmt::to_string(formatted));
  }

  virtual void flush_() override
  {
    // I don't think we need to do anything with this right now?
  }

private:
  std::queue<std::string> _messages;
};

#include <spdlog/details/null_mutex.h>
#include <mutex>
using widget_logger_sink_mt = LoggerSink<std::mutex>;
using widget_logger_sink_st = LoggerSink<spdlog::details::null_mutex>;
