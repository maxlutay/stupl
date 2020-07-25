#pragma once

#include "Serializable.hpp"

#include <vector>
#include <ostream>
#include <memory>

class Logger {
 protected:
  std::vector<std::ostream*>to;


 public:
  
  template<typename T>
  std::enable_if<std::is_convertible_v<T,std::string> or std::is_constructible_v<std::string,T>>
  Logger& log(std::initializer_list<T>) = 0;

  Logger(std::initializer_list<std::ostream*> output_streams) {
    for(auto* os : output_streams){
      to.push_back(os);
    }
  };

  virtual ~Logger() = default;
};
