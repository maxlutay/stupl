#pragma once
#include <string>

class Serializable {
 public:
  virtual std::string get_as_string() const = 0;
  virtual ~Serializable() = default;
};