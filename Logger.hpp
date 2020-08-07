#pragma once


#include <vector>
#include <ostream>
#include <sstream>
#include <memory>


#include <array>

class Logger {
 protected:
  std::vector<std::ostream*> to;

  std::ostringstream buffer_from;

 public:

  template <typename ...Ts
  >
  Logger& log(Ts... to_log) {


    static_assert( (... and (std::is_convertible_v<Ts, std::string> or std::is_constructible_v<std::string, Ts>) ) ,"!");


    ( (buffer_from << std::string{to_log} ) , ... ) ;

    auto logs = buffer_from.str();
    buffer_from.str("");

    for (auto* os : to) {
      *os << logs;
    };

    return *this;
  };

  Logger(std::initializer_list<std::ostream*> output_streams) {
    for (auto* os : output_streams) {
      to.push_back(os);
    };
  };

  virtual ~Logger() = default;
};
