
#include <string>
#include <memory>
#include <functional>

class Regex {
 public:
  class RegexChain;

  class Group;
  class CaptureGroup;

  static class primitives {
    class Primitive;

   public:
    Primitive any;
    
    
    Primitive start_line;
    Primitive end_line;
    Primitive start;
    Primitive end;

  } primitives;

  class MatchResult {
    friend MatchResult match_first(std::string, Regex) const;

    using GroupsMatches = std::vector<std::string>;
    using ExpressionMatches = std::vector<GroupsMatches>;

    ExpressionMatches matches;

   public:
  };

  MatchResult match_first(const std::string& text, Regex r) const {
    MatchResult tmp;

    bool match_expression_possible = true;

    while (match_expression_possible) {
      try {
        tmp.matches.push(r.to_fsm().match(text));
        match_expression_possible = false;  // match only once
      } catch (std::runtime_error& err) {
        match_expression_possible = false;
      };
    };

    return tmp;
  };

  MatchResult match_all(std::string text, Regex r) const;
};
