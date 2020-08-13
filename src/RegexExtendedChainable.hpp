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
 private:
  class Primitive;
  class PrimitiveRepeatable;
  class Repeatable;
  class BasicRegex;

 public:
  class Group;
  class CaptureGroup;
  class RegexPart;
  class MatchResult;
  class primitives;

  static MatchResult match(std::string, BasicRegex);
};

class Regex::Group : public Regex::RegexPart {};
class Regex::CaptureGroup : public Regex::Group {
  // check if group
};

class Regex::RegexPart : public Regex::BasicRegex {
  std::unique_ptr<RegexPart> r_next{nullptr};

 public:
  RegexPart() = default;
  RegexPart(const RegexPart& other) {
    r_next = std::make_unique<RegexPart>(*other.r_next);
  };

  RegexPart operator=(const RegexPart& c) { return c; };
  RegexPart& next(RegexPart value_copy) {  // copying passed regex
    r_next = std::make_unique<RegexPart>(value_copy);
    return *r_next;
  };
};

class Regex::MatchResult {};

class Regex::Repeatable {
 private:
  bool zero_f = false, one_f = false, many_f = false;

 public:
  Repeatable& zero() {
    if (one_f)
      throw std::logic_error("cant set zero, one flag already set true");
    zero_f = true;
    return *this;
  };
  Repeatable& one() {
    if (zero_f)
      throw std::logic_error("can't set one, zero flag alredy set true");
    one_f = true;
    return *this;
  };
  Repeatable& more() {
    if (zero_f && one_f)
      throw std::logic_error("cant set many, set either zero or one");
    many_f = true;
    return *this;
  };
};

class Regex::Primitive : public Regex::RegexPart {
 public:
  Primitive(const std::string& s) : RegexPart(s){};
};

class Regex::PrimitiveRepeatable : public Regex::Primitive, public Regex::RegexPart, public Regex::Repeatable {
  using Primitive::Primitive;
};

class Regex::primitives {
  using R = Regex;

 public:
  static R::Primitive begin_line;
  static R::Primitive end_line;
  static R::PrimitiveRepeatable any;
  static R::PrimitiveRepeatable space;
};

Regex::Primitive Regex::primitives::begin_line{"^"};
Regex::Primitive Regex::primitives::end_line{"$"};
Regex::PrimitiveRepeatable Regex::primitives::any{"[\\S\\s]"};
Regex::PrimitiveRepeatable Regex::primitives::space{"\\s"};
