#pragma once

#include <regex>
#include <string>
#include <memory>

//!!! not ready, very much work needed
/*
class RegexExtendedChainable {
 public:
  static RegexExtendedChainable space{"\\s"};
  static RegexExtendedChainable any{"."};
  static RegexExtendedChainable begin_line{"^"};
  static RegexExtendedChainable end_line{"$"};

  static MatchResult match(const std::string& s, RegexExtendedChainable r){

  };

 private:
  std::shared_ptr<RegexExtendedChainable> next;
  const std::list<RegexExtendedChainable> templates_sequence;
  std::unoredered_map<std::string, Group> direct_child_groups;

  bool zero_repeat_flag = false;
  bool once_repeat_flag = false;
  bool many_repeat_flag = false;
  // bool never = false;

 public:
  RegexExtendedChainable(const char* s) : templates_sequence({s}){};

  RegexExtendedChainable(const std::string& s) : templates_sequence({s}){};

  RegexExtendedChainable(std::regex r){};

  // todo: implement chaining
  // ie allow multiple specialization with variadic arguments by strings and
  // references to other RegexExtendedChainablees

  std::regex get_std_regex() const {
    //  const function return declaration for keeping const qualifier and not
    //  using const_cast as function itself is const
    return std::regex{};
  };

  operator std::regex() const { return get_std_regex(); };

  RegexExtendedChainable& zero() {
    zero_repeat_flag = true;
    return *this;
  };

  RegexExtendedChainable& once() {
    once_repeat_flag = true;
    return *this;
  };
  RegexExtendedChainable& more() {
    many_repeat_flag = true;
    return *this;
  };

  RegexExtendedChainable& then(RegexExtendedChainable next_regex) {
    next = std::make_shared<RegexExtendedChainable>(next_regex);
    return *next;
  };

  class Group {
   public:
    std::string name{""};
    RegexExtendedChainable pattern;

    Group(std::string name, RegexExtendedChainable pattern)
        : name(name), pattern(pattern){};

    Group(RegexExtendedChainable pattern) : pattern(pattern){};
  };

  class CaptureGroup : Group {
   public:
    std::string captured;
    using Group::Group;
  };

  using CharSequence = std::string;

  class MatchResult {
   public:
    std::map<std::pair<uint64_t, std::string>, std::string> result;
  };
};
*/


class Regex {
  // consider making class fully immutable all-copy
  class Group;
  class CaptureGroup;
  class RegexExtended;
  class MatchResult;
  class Primitives;

  static MatchResult match(std::string, RegexExtended);
};


class Regex::Group{};
class Regex::CaptureGroup : public Regex::Group{};

class Regex::RegexExtended {
  RegexExtended next;

public:
  RegexExtended& next(RegexExtended value_copy) {  // copying passed regex
    next = value_copy;
    return &next;
  };
};

class Regex::MatchResult{};
class Regex::Primitives{};

