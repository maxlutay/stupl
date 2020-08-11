#pragma once

#include <regex>
#include <string>

class ChainRegex : public std::regex {
 public:
  using std::regex::regex;

  ChainRegex(const char* s) : std::regex(s){};
  ChainRegex(const std::string& s) : std::regex(s){};

  // todo: implement chaining
  // ie allow multiple specialization with variadic arguments by strings and
  // references to other ChainRegexes

  const std::regex& get_std_regex() const {
    //  const function return declaration for keeping const qualifier and not
    //  using const_cast as function itself is const
    return dynamic_cast<const std::regex&>(*this);
  };

};