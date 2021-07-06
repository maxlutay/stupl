
#include <string>
#include <memory>
#include <functional>
#include <stdexcept>

class Regex {
 public:
  class Chain;

  class Group;
  using CaptureGroup = Group;
  class NonCaptureGroup;

  struct CurrentChar {
    bool is_first;
    bool is_last;
    bool is_first_in_line;
    bool is_last_in_line;

    char value;
  };

  class primitives {
    using Primitive = std::function<bool(CurrentChar const)>;

   public:
    // inline static is c++17 feature
    inline static Primitive any = [](const CurrentChar cc) { return true; };
    inline static Primitive begin_line = [](const CurrentChar cc) {
      return cc.is_first_in_line;
    };
    inline static Primitive end_line = [](const CurrentChar cc) {
      return cc.is_last_in_line;
    };
    inline static Primitive begin = [](const CurrentChar cc) {
      return cc.is_first;
    };
    inline static Primitive end = [](const CurrentChar cc) {
      return cc.is_last;
    };

    primitives() = delete;
  };  // end primitives

  class MatchResult;
  class NoMatch;

  static MatchResult match_first(const std::string& text, const Regex r) {
    // since some future version use <stringview> instead of const std::string&

    MatchResult tmp;

    try {
      tmp.matches.push_back(r.to_fsm().match(text));
    } catch (std::runtime_error& err) {
    };

  };  // end match_first

  static MatchResult match_all(const std::string& text, const Regex r) {
    // since some future version use <stringview> instead of const std::string&

    MatchResult tmp;

    bool match_expression_possible = true;

    while (match_expression_possible) {
      try {
        tmp.matches.push_back(r.to_fsm().match(text));
        match_expression_possible = false;  // match only once
      } catch (std::runtime_error& err) {
        match_expression_possible = false;
      };
    };

    return tmp;

  };  // end match_all

  class MatchResult {
    using GroupsMatches = std::vector<std::string>;
    using ExpressionMatches = std::vector<GroupsMatches>;
    /*
        //ExpressionMatches is for matched regular expression result
        //one regular expression can match multiple parts of some string
        // e.g. r"a([b-y]*)z+" globally in "abczzazaaagz" should contain
        // [ [`abczz`,`bc`],[`az`], [`agz`,`g`] ]
        //first group match
    */
    ExpressionMatches matches;

   public:
    friend MatchResult Regex::match_first(const std::string&, const Regex);
    friend MatchResult Regex::match_all(const std::string&, const Regex);
  };  // end match_all

  class NoMatch : private MatchResult, public std::false_type {};
};
