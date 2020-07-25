#pragma once

#include <chrono>
#include <iostream>
#include <string>

class Testable {
 protected:
  virtual bool test_callback() = 0;
 public:
  void test(const std::string& test_name);
  virtual ~Testable(){};
};

void Testable::test(const std::string& test_name) {
  std::string testheader;
  testheader.append(">test \"").append(test_name).append("\" : ");

  std::cout << testheader << "start\n";

  auto from_time = std::chrono::steady_clock::now();

  try {
    if (test_callback()) {
      std::cout << testheader << "passed\n";
    } else {
      std::cout << testheader << "failed\n";
    };

  } catch (const std::exception& e) {
    std::cout << testheader << "failed with exception: "<< e.what() <<"\n";
  };

  std::cout << testheader << "elapsed "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::steady_clock::now() - from_time)
                   .count()
            << "ms\n";

  std::cout << testheader << "end\n";
};