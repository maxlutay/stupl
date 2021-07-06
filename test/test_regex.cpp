

#include "Regex/Regex.hpp"

#include <string>

int test_regex() {
  using RCG = Regex::CaptureGroup;
  using Rp = Regex::primitives;

  // auto module_decl_regex = Regex::Chain{}
  //                              .next(Rp::begin_line)
  //                              .next(R::space.zero().more())
  //                              .next("module")
  //                              .next(Rp::space.once().more())
  //                              .next(RCG("\\w+"))
  //                              .next(Rp::space.zero().more())
  //                              .next(RCG(";").zero().once())
  //                              .next(Rp::space.zero().more())
  //                              .next(Rp::any.once().more())
  //                              .regex();

  // auto result = Regex::match(test_s1, module_decl_regex);

  auto rgx = Regex::Chain{}
                 .next(Rp::begin_line)
                 .next(Rp::any.one().more())
                 .next("module")
                 .next(Rp::any.zero().more())
                 .next(Rp::end_line)
                 .complete();

  std::string test_s0{""};
  auto result0 = Regex::match_first(test_s0, rgx);  // exception or fail // or NoMatch

  std::string test_s1{"        module     hello ; //bye"};
  auto result1 = Regex::match_first(test_s1, rgx);  // ok -> hello
};
