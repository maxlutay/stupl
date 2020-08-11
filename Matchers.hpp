#pragma once

#include <regex>
#include <string>
#include <unordered_map>

#include "ChainRegex.hpp"

class Matchers {

 private:
  std::unordered_map<std::string, ChainRegex> matchers;

  enum class Classifier { START, END, UNCLASSIFIED };
  std::unordered_map<std::string, Classifier> classification;

  // drawback of high memory usage, chnaging to <Classifier,
  // container<std::string> >
  // uses less memory, but involves consistency management
  // consider using std::map<std::string, std::pair < std::regex, Classifier> >

  ChainRegex get_regex(const std::string& which) { return matchers[which]; };

 public:
  class Iterator {

    Iterator& operator*(){
      return;
    };

    bool operator==(const Iterator& cmp_to){
      return (*this)==cmp_to;
    };

  } iterator;

  Matchers() {
    emplace("module", "\\s*module\\s+(\\w+)\\s*;?.*");
    emplace("type", "\\s*type\\s+(\\w+)\\s+is.*");
    emplace("string_oneliner",
            "[\\S\\s]*(\"[\\S\\s]*\")|('[\\S\\s]*')[\\S\\s]*");
    emplace("function", "\\s*f(n)|(un(ction)?)\\s+(\\w+)\\s*");
    emplace("end", "^\\s*end\\s*;?.*");
  };

  Matchers& emplace(const std::string& name, const ChainRegex& r) {
    matchers.emplace(name, r);
    set_classification(name, Classifier::UNCLASSIFIED);

    return *this;
  };

  Matchers& set_classification(const std::string& name, Classifier to) {
    classification[name] = to;
    return *this;
  };

  Iterator begin() { return iterator.begin(); };
  Iterator cbegin() const { return iterator.cbegin(); };

  Iterator end() { return iterator.end(); };
  Iterator cend() const { return iterator.cend(); };

  ChainRegex operator[](const std::string& which) { return get_regex(which); };
};