#pragma once

#include "./Serializable.hpp"
#include "./LineNumber.hpp"

#include <string>

class LanguageUnit : public Serializable {
 private:
 const std::string content;

 public:
  LanguageUnit(const std::string& c)
      : content(c){};

  virtual std::string get_as_string() const override {
    //TODO: Replace with stringbuilder?
    std::string result;
    result += "`";
    result += content;
    result += "`";

    return result;
  };


  virtual operator std::string() const {
    return get_as_string();
  };

  virtual ~LanguageUnit() = default;
};
