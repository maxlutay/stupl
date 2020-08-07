#pragma once

#include "Logger.hpp"
#include "Testable.hpp"

#include <sstream>

class LazyLogger : public Logger
//, Testable
{
 private:
  std::stringstream accumulator;

  // virtual bool test_callback() override;

 protected:
 public:
  using Logger::Logger;

  virtual ~LazyLogger() = default;

  template <typename T>
  std::enable_if<std::is_convertible_v<T, std::string> or
                 std::is_constructible_v<std::string, T>> LazyLogger&
      append(std::initializer_list<T>) ;

  LazyLogger& log();

  template <typename T>
  std::enable_if<std::is_convertible_v<T, std::string> or
                 std::is_constructible_v<std::string, T>>  LazyLogger&
      log(std::initializer_list<T>) ;
};

template <typename T>
std::enable_if<std::is_convertible_v<T, std::string> or
               std::is_constructible_v<std::string, T>>
    LazyLogger& LazyLogger::append(std::initializer_list<T> messages) {
  for (auto& m : messages) {
    accumulator << std::to_string(m);
  };
  return *this;
};

template <typename T>
std::enable_if<std::is_convertible_v<T, std::string> or
               std::is_constructible_v<std::string, T>>
    LazyLogger& LazyLogger::log(std::initializer_list<T> messages) {
  append(messages);
  return log();
};

LazyLogger& LazyLogger::log() {
  auto s = accumulator.str();
  accumulator.str("");
  for (auto* stream : to) {
    *stream << s;
  };
  return *this;
};
