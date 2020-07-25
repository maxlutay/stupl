
#include "../LazyLogger.hpp"

#include "../LanguageUnit.hpp"
#include "../LanguageModuleUnit.hpp"

#include <iostream>
#include <fstream>
#include <memory>

int main() {
  std::fstream file{"./testresult.log"};

  auto hlu = std::make_unique<LanguageUnit>("hello");
  auto rlmu = std::make_unique<LanguageModuleUnit>("randomname", 0, 30);
  auto blu = std::make_unique<LanguageUnit>("bye");

  LazyLogger ll{{&std::cout, &file}};

  ll.append({hlu->get_as_string(), rlmu->get_as_string(), blu->get_as_string()});

  ll.append({std::string("m1"), std::string("m2\n"), std::string("m3"),
             std::string("m4")});

  ll.log();
}