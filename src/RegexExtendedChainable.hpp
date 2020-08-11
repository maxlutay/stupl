#pragma once

#include <regex>
#include <string>
#include <memory>

class RegexExtendedChainable {
 public:
  static RegexExtendedChainable space{"\\s"};
  static RegexExtendedChainable any{"."};
  static RegexExtendedChainable begin_line{"^"};
  static RegexExtendedChainable end_line{"$"};

 private:
  std::shared_ptr<RegexExtendedChainable> next;
  const std::list<RegexExtendedChainable> templates_sequence;
  std::unoredered_map<std::string, Group> direct_child_groups;

  bool zero = false;
  bool once = false;
  bool many = false;
  bool never = false;

 public:
  RegexExtendedChainable(const char* s) : templates_sequence({s}){};

  RegexExtendedChainable(const std::string& s) : templates_sequence({s}){};

  RegexExtendedChainable(std::regex r){};


  template <typename Ts...>
  RegexExtendedChainable(Ts... templates) {
    static_assert(true);  // todo check Ts... either char* or string or group
  };

  // todo: implement chaining
  // ie allow multiple specialization with variadic arguments by strings and
  // references to other RegexExtendedChainablees

  const std::regex& get_std_regex() const {
    //  const function return declaration for keeping const qualifier and not
    //  using const_cast as function itself is const
    return dynamic_cast<const std::regex&>(*this);
  };

  operator std::regex() const { return get_std_regex(); };

  RegexExtendedChainable& zero() {
    zero = true;
    return *this;
  };
  RegexExtendedChainable& once() {
    once = true;
    return *this;
  };
  RegexExtendedChainable& more() {
    many = true;
    return *this;
  };

  RegexExtendedChainable& then(const RegexExtendedChainable&& next_regex){
    next = next_regex;
    return *next;
  };

  class Group : RegexExtendedChainable {
    std::string name{""};
    Group(std::string name, RegexExtendedChainable pattern)
        : name(name), RegexExtendedChainable(pattern){};

    Group(RegexExtendedChainable pattern) : RegexExtendedChainable(pattern){};
  };

  using CharSequence = std::string;
};