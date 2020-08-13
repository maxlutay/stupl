

#include "RegexExtendedChainable.hpp"

#include <string>

int main() {
  using RP = Regex::RegexPart;
  using RCG = Regex::CaptureGroup;
  using Rp = Regex::primitives;

  // auto module_decl_regex = RP::begin_line.next(R::space.zero().more())
  //                              .next("module")
  //                              .next(RP::space.once().more())
  //                              .next(RCG("\\w+"))
  //                              .next(RP::space.zero().more())
  //                              .next(RCG(";").zero().once())
  //                              .next(RP::space.zero().more())
  //                              .next(RP::any.once().more());

  // auto result = Regex::match(test_s1, module_decl_regex);

  auto rgx = RP::begin_line.next(RP::any.one().more())
                 .next("module")
                 .next(RP::any.zero().more())
                 .next(RP::end_line);

  std::string test_s0{""};
  auto result0 = Regex::match(test_s0, rgx);  // exception or fail

  std::string test_s1{"        module     hello ; //bye"};
  auto result1 = Regex::match(test_s1, rgx);  // ok -> hello
};