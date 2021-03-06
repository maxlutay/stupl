#pragma once


#include <vector>
#include <ostream>
#include <sstream>
#include <string>


#include "./is_to_stream_writable.hpp"

class Logger {
 protected:
  std::vector<std::ostream*> to;

  std::ostringstream buffer_from;

 public:

  template <typename ...Ts>
  Logger& log(Ts... to_log) {


    static_assert( (... and (is_to_stream_writable_v<decltype(buffer_from), Ts>))  ,"custom type constraints in Logger.log");


    ( (buffer_from << to_log ) , ... ) ;

    auto logs = buffer_from.str();
    buffer_from.str("");

    for (auto* os : to) {
      *os << logs;
    };

    return *this;
  };


  template <typename ...Tostream>
  Logger(Tostream*... output_streams) {
    static_assert( (... and (std::is_base_of_v<std::ostream, Tostream>) ) , "custom type constraints");

    ( (to.push_back(output_streams) ) , ... );

  };


  template <typename ...Tostream>
  Logger& add_ouput_streams(Tostream*... output_streams) {
    static_assert( (... and (std::is_base_of_v<std::ostream, Tostream>) ) , "custom type constraints");

    ( (to.push_back(output_streams) ) , ... );
  return *this;
  };



  virtual ~Logger() = default;
};
