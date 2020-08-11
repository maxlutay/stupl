#pragma once

#include <regex>
#include <string>
#include <unordered_map>

#include "RegexExtendedChainable.hpp"

class Matchers {
 private:
  // class UmapContainer<std::string, std::pair<RegexExtendedChainable,Classifier> >
  // matchers;
  std::unordered_map<std::string, RegexExtendedChainable> matchers;

  enum class Classifier { START, END, UNCLASSIFIED };
  std::unordered_map<std::string, Classifier> classification;

  // drawback of high memory usage, chnaging to <Classifier,
  // container<std::string> >
  // uses less memory, but involves consistency management
  // consider using std::map<std::string, std::pair < std::regex, Classifier> >

  RegexExtendedChainable get_regex(const std::string& which) { return matchers[which]; };

 public:
  class Iterator {
    Iterator& operator*() { return; };

    bool operator==(const Iterator& cmp_to) { return (*this) == cmp_to; };

  } iterator;

  Matchers() {
    using G = RegexExtendedChainable::Group;
    using R = RegexExtendedChainable;

    emplace("name of module", "\\w+");
    emplace("module declaration line", R::begin_line, R::space.zero().more(),
            "module", R::space.one().more(), G(get_regex("name of module")),
            space.zero().more(), R(";").zero().one(), space.zero().more()
            get_regex("any comment start") );

    emplace("type", "\\s*type\\s+", G(get_regex("type name")), "\\s+is.*");
    emplace("string_oneliner",
            "[\\S\\s]*(\"[\\S\\s]*\")|('[\\S\\s]*')[\\S\\s]*");
    emplace("function", "\\s*f(n)|(un(ction)?)\\s+(\\w+)\\s*");
    emplace("end", "^\\s*end\\s*;?.*");

    emplace("line comment //", "^(.*)//([\S\s]*)$");
    emplace("line comment #", "^(.*)#([\S\s]*)$");
    emplace("multiline comment /* start", "(.*)/\\*(.*)");
    emplace("multiline comment */ end", "(.*)\\*/(.*)");
  };

  Matchers& emplace(const std::string& name, const RegexExtendedChainable& r) {
    matchers.emplace(name, r);
    set_classification(name, Classifier::UNCLASSIFIED);

    return *this;
  };

  Matchers& emplace(const std::string& name,
                    const RegexExtendedChainable& r,
                    Classifier classifier) {
    matchers.emplace(name, r);
    set_classification(name, classifier);

    return *this;
  };

  Matchers& set_classification(const std::string& name, Classifier to) {
    classification[name] = to;
    return *this;
  };

  RegexExtendedChainable operator[](const std::string& which) { return get_regex(which); };
};