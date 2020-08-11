#pragma once

#include <regex>
#include <string>
#include <unordered_map>

#include "ChainRegex.hpp"

class Matchers {
 private:
  // class UmapContainer<std::string, std::pair<ChainRegex,Classifier> >
  // matchers;
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
    Iterator& operator*() { return; };

    bool operator==(const Iterator& cmp_to) { return (*this) == cmp_to; };

  } iterator;

  Matchers() {
    using R = ChainRegex;
    using G = R::Group;

    emplace("name of module", "\\w+");
    emplace("module declaration line",
            R::begin_line.then(R::space.zero().more())
                .then("module")
                .then(R::space.one().more())
                .then(G(get_regex("name of module")))
                .then(R::space.zero().more())
                .then(R(";").zero().one())
                .then(R::space.zero().more())
                .then(get_regex("any comment start"))
    );

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

  Matchers& emplace(const std::string& name, const ChainRegex& r) {
    matchers.emplace(name, r);
    set_classification(name, Classifier::UNCLASSIFIED);

    return *this;
  };

  Matchers& emplace(const std::string& name,
                    const ChainRegex& r,
                    Classifier classifier) {
    matchers.emplace(name, r);
    set_classification(name, classifier);

    return *this;
  };

  Matchers& set_classification(const std::string& name, Classifier to) {
    classification[name] = to;
    return *this;
  };

  ChainRegex operator[](const std::string& which) { return get_regex(which); };
};