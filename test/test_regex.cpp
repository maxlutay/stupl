

#include "Regex/Regex.hpp"

#include <string>

int test_regex() {
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

  auto rgx = Rp::begin_line.next(Rp::any.one().more())
                 .next("module")
                 .next(Rp::any.zero().more())
                 .next(Rp::end_line);

  std::string test_s0{""};
  auto result0 = Regex::match_first(test_s0, rgx);  // exception or fail

  std::string test_s1{"        module     hello ; //bye"};
  auto result1 = Regex::match_first(test_s1, rgx);  // ok -> hello
};