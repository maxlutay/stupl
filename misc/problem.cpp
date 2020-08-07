
//#include "../LazyLogger.hpp"

#include "../Logger.hpp"

#include "../LanguageUnit.hpp"
#include "../LanguageModuleUnit.hpp"

#include <iostream>
#include <fstream>
#include <memory>

int main() {
  std::ofstream file{"logs/testresultsn.log"};

  if(!file) std::cout << "wtehek\n";

  auto hlu = std::make_unique<LanguageUnit>("hello");
  auto rlmu = std::make_unique<LanguageModuleUnit>("randomname", 0, 30);
  auto blu = std::make_unique<LanguageUnit>("bye");


  file << "hello file\n";

  Logger l {{&std::cout , &file}};

  l.log("simple  logger start \n");
  //l.log( hlu->get_as_string(), rlmu->get_as_string(), blu->get_as_string() );
  //l.log("\n" );
  // l.log({ *hlu}).log({*rlmu}).log({*blu});
  // l.log({"\n" });
   l.log<LanguageUnit>( *hlu, *rlmu, *blu);
   l.log("\n" );
  
  l.log ("simple logger end\n" );



  // LazyLogger ll{{&std::cout, &file}};

  // ll.append({"lazylogger start\n"});

  // ll.append({hlu->get_as_string(), rlmu->get_as_string(), blu->get_as_string()});

  // ll.append({std::string("m1"), std::string("m2\n"), std::string("m3"),
  //            std::string("m4")});

  // ll.log();

  // ll.log("lazylogger end\n");


}