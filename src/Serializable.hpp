#pragma once
#include <string>
#include <iostream> //class "<<" global operator overloading

class Serializable {
 public:
  virtual std::string get_as_string() const = 0;
  virtual ~Serializable() = default;
  operator std::string() const { return get_as_string(); };
};


std::ostream& operator<<(std::ostream& os, const Serializable& s){
  os << s.get_as_string();
  return os;
};