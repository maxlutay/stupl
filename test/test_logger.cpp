

#include "../Logger.hpp"
#include "../LazyLogger.hpp"

#include "../LanguageUnit.hpp"
#include "../LanguageModuleUnit.hpp"

#include <iostream>
#include <fstream>
#include <memory>
#include <chrono>

#include <iomanip>
#include <ctime>

int main() {
  std::ofstream file{"logs/testresultsn.log"};

  if (!file)
    std::cout << "wtehek\n";

  auto hlu = std::make_unique<LanguageUnit>("hello");
  auto rlmu = std::make_unique<LanguageModuleUnit>("randomname", 0, 30);
  auto blu = std::make_unique<LanguageUnit>("bye");

  auto put_now_datetime = []() -> auto {
    auto t =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return std::put_time(std::gmtime(&t), "%F %T");
  };

  LazyLogger ll{&std::cout, &file};

  ll.log("---logs start\t", put_now_datetime(), "---\n");


  ll.log("lazylogger start \n");
  ll.log(*hlu, "\n", *rlmu, "\n", *blu).log("\n");
  ll.log("lazylogger end\n");

  ll.log("---logs end\t", put_now_datetime(), "---\n");

}