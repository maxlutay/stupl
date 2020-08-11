#pragma once

#include <regex>
#include <string>
#include <memory>

class ChainRegex {
 public:
  static ChainRegex space{"\\s"};
  static ChainRegex any{"."};
  static ChainRegex begin_line{"^"};
  static ChainRegex end_line{"$"};

 private:
  std::shared_ptr<ChainRegex> next;
  const std::list<ChainRegex> templates_sequence;
  std::unoredered_map<std::string, Group> direct_child_groups;

  bool zero = false;
  bool once = false;
  bool many = false;
  bool never = false;

 public:
  ChainRegex(const char* s) : templates_sequence({s}){};

  ChainRegex(const std::string& s) : templates_sequence({s}){};

  ChainRegex(std::regex r){};


  template <typename Ts...>
  ChainRegex(Ts... templates) {
    static_assert(true);  // todo check Ts... either char* or string or group
  };

  // todo: implement chaining
  // ie allow multiple specialization with variadic arguments by strings and
  // references to other ChainRegexes

  const std::regex& get_std_regex() const {
    //  const function return declaration for keeping const qualifier and not
    //  using const_cast as function itself is const
    return dynamic_cast<const std::regex&>(*this);
  };

  operator std::regex() const { return get_std_regex(); };

  ChainRegex& zero() {
    zero = true;
    return *this;
  };
  ChainRegex& once() {
    once = true;
    return *this;
  };
  ChainRegex& more() {
    many = true;
    return *this;
  };

  ChainRegex& then(const ChainRegex&& next_regex){
    next = next_regex;
    return *next;
  };

  class Group : ChainRegex {
    std::string name{""};
    Group(std::string name, ChainRegex pattern)
        : name(name), ChainRegex(pattern){};

    Group(ChainRegex pattern) : ChainRegex(pattern){};
  };

  using CharSequence = std::string;
};