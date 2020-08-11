#pragma once

#include "Logger.hpp"
#include "Testable.hpp"
#include "is_to_stream_writable.hpp"

#include <sstream>

class LazyLogger : private Logger
//, public Testable
{
 private:
  // virtual bool test_callback() override;

 protected:
 public:
  using Logger::Logger;

  virtual ~LazyLogger() = default;

  template <typename... Ts>
  LazyLogger& append(Ts...);

  template <typename... Ts>
  LazyLogger& log();

  template <typename... Ts>
  LazyLogger& log(Ts...);
};

template <typename... Ts>
LazyLogger& LazyLogger::append(Ts... message) {
  static_assert((... and (is_to_stream_writable_v<decltype(buffer_from), Ts>)),
                "custom");

  ((buffer_from << message), ...);
  return *this;
};

template <typename... Ts>
LazyLogger& LazyLogger::log(Ts... message) {
  (append(message), ...);
  return log();
};
template <typename... Ts>
LazyLogger& LazyLogger::log() {
  Logger::log();
  return *this;
};
