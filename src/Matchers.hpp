#pragma once

#include <regex>
#include <string>
#include <unordered_map>

#include "RegexExtendedChainable.hpp"

class Matchers {
/* private:
  // class UmapContainer<std::string,
  // std::pair<RegexExtendedChainable,Classifier> > matchers;
  std::unordered_map<std::string, RegexExtendedChainable> matchers;

  enum class Classifier { START, END, UNCLASSIFIED };
  std::unordered_map<std::string, Classifier> classification;

  // drawback of high memory usage, chnaging to <Classifier,
  // container<std::string> >
  // uses less memory, but involves consistency management
  // consider using std::map<std::string, std::pair < std::regex, Classifier> >

  RegexExtendedChainable get_regex(const std::string& which) {
    return matchers[which];
  };

 public:
  class Iterator {
    Iterator& operator*() { return; };

    bool operator==(const Iterator& cmp_to) { return (*this) == cmp_to; };

  } iterator;

  Matchers() {
    using R = RegexExtendedChainable;
    using G = R::Group;
    using C = R::CaptureGroup;

    emplace("name of module", "\\w+");
    emplace("module declaration line",
            R::begin_line.then(R::space.zero().more())
                ..then("module")
                .then(R::space.one().more())
                .then(C("name",get_regex("name of module")))
                .then(R::space.zero().more())
                .then(R(";").zero().one())
                .then(R::space.zero().more())
                .then(get_regex("any comment start")));

    emplace("type", R::begin_line.then(R::space.zero().more())
                        .then("type")
                        .then(R::space.one().more())
                        .then(C(get_regex("type name")))
                        .then(R::space.one().more())
                        .then("is")
                        .then(

                            R::space.once().more().then(R::any).zero().more())
                        .zero()
                        .once()
                        .then(R::end));

    emplace("string oneliner double quotes", R::any.zero()
                                                 .more()
                                                 .then("\"")
                                                 .then(C(R::any.zero().more()))
                                                 .then("\"")
                                                 .then(R::any.zero().more())

    );

    emplace("string oneliner single quotes", R::any.zero()
                                                 .more()
                                                 .then("'")
                                                 .then(C(R::any.zero().more()))
                                                 .then("'")
                                                 .then(R::any.zero().more()));

    emplace("end", R::any.zero()
                       .more()
                       .then("end")
                       .then(R::space.zero().more())
                       .then(R(";").zero().once())
                       .then(R::any));

    emplace("function", "\\s*f(n)|(un(ction)?)\\s+(\\w+)\\s*");  // todo

    emplace("line comment //", R::any.once().more().then("//").then(
                                   R::any.once().more) "^(.*)//([\S\s]*)$");
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

  RegexExtendedChainable operator[](const std::string& which) {
    return get_regex(which);
  };




*/};




