

#include "RegexExtendedChainable.hpp"

#include <string>

int main() {

  std::string test_s0{""};
  std::string test_s1{"        module     hello ; //bye"};

  using RE = Regex::RegexExtended;
  using G = Regex::CaptureGroup;
  using RP = Regex::Primitives;

  // auto module_decl_regex = RP::begin_line.next(R::space.zero().more())
  //                              .next("module")
  //                              .next(RP::space.once().more())
  //                              .next(G("\\w+"))
  //                              .next(RP::space.zero().more())
  //                              .next(G(";").zero().once())
  //                              .next(RP::space.zero().more())
  //                              .next(RP::any.once().more());

  // auto result = Regex::match(test_s1, module_decl_regex);


  auto rgx = RP::begin_line.next(RP::any.more()).next(RP::end_line);

  auto result0 = Regex::match(test_s0,rgx);
  auto result1 = Resul::match(test_s1,rgx);

};