#pragma once

#include "SyntaxTree.hpp"
#include "LineNumber.hpp"
#include "LanguageModuleUnit.hpp"
#include "LazyLogger.hpp"
#include "Matchers.hpp"

#include <fstream>

#include <regex>
#include <ostream>
#include <fstream>
#include <algorithm>

class ParserBlocks {
 private:
  // struct LineNumberStackEntry{
  //   LineNumber line;
  //   std::string filename;
  // };

  // std::vector<LineNumber> line_number_stack;  // for multiple file indexing

  Matchers matchers;

  const std::shared_ptr<LazyLogger> logger;

 public:
  ParserBlocks(std::shared_ptr<LazyLogger> ll) : logger(std::move(ll)){};
  // ParserBlocks(const ParserBlocks&) = default;

  std::unique_ptr<SyntaxTree> operator()(std::istream&);

 private:
  auto match_start_end_lines(std::istream&);
};

auto ParserBlocks::match_start_end_lines(std::istream& program) {
  std::vector<std::pair<LineNumber, LineNumber>> s_e_pairs;
  std::vector<LanguageUnit> result;

  std::string current_line;

  LineNumber counter = 0;

  std::vector<LineNumber> start_lines;

  while (std::getline(program, current_line)) {
    counter++;  // if headline index is 1

    // todo: implement innerfirst end policy

    //   bool start_match_flag =
    //       std::any_of(matchers.cbegin(), matchers.cend(),
    //                   [&current_line](auto& matcher) -> bool {
    //                     return ("end" != matcher.first) &&
    //                            std::regex_match(current_line,
    //                            matcher.second);
    //                   });

    //   if (start_match_flag) {
    //     s_e_pairs.emplace_back(counter, EmptyLineNumber);
    //   };

    //   bool end_match_flag = std::regex_match(current_line, matchers["end"]);

    //   if (end_match_flag) {
    //     if (s_e_pairs.empty()) {
    //       logger->append("'end' on line ", counter,
    //                     " does not have corresponding declaration\n");
    //     };

    //     if (s_e_pairs.back().second == EmptyLineNumber) {
    //       s_e_pairs.back().second = counter;
    //     };

    //     s_e_pairs.emplace_back(start_lines.back(), counter);
    //     start_lines.pop_back();

    //     // new
    //     if (EmptyLineNumber == s_e_pairs.back().second) {
    //       s_e_pairs.back().second = counter;
    //     } else {
    //       s_e_pairs.emplace_back()
    //     };
    //   };

    //   // counter++;//if headline index is 0
    // };

    // while (not start_lines.empty()) {
    //   logger->append("no matching end for declaration on line ",
    //                 std::to_string(start_lines.back()), ", end expected on
    //                 line ", counter, "\n");

    //   s_e_pairs.emplace_back(start_lines.back(), counter);
    //   start_lines.pop_back();
  };

  return result;
};

std::unique_ptr<SyntaxTree> ParserBlocks::operator()(std::istream& program) {
  using NodeT = SyntaxTree::Type_of_node;
  auto tree = std::make_unique<SyntaxTree>(new NodeT{nullptr});

  auto root = tree->root.get();
  auto parent = root;

  // auto s_e_lines = match_start_end_lines(program);

  // auto treebuilder = [&root, &parent,
  //                     &matchers = matchers](const auto& s_e_line) {
  //   std::smatch matched;
  //   std::regex_match(current_line, matched, matchers["module_start"]);

  //   std::string name_matched = matched.str(1);
  // };

  // std::for_each(s_e_lines.cbegin(), s_e_lines.cend(), treebuilder);

  /*
  std::string current_line;

  auto root = tree->root.get();
  auto parent = root;

  // int64_t start_counter = 0, end_counter = 0;
  int64_t start_end_counter = 0;

  while (std::getline(program, current_line)) {
    line_number_stack.back()++;

    std::smatch matched;
    bool module_match =
        std::regex_match(current_line, matched, matchers["module_start"]);

    std::string name_matched = matched.str(1);

    if (module_match) {  // if regex match line
      // push and look for end or children

      parent->children.construct_child(new NodeT{
          parent,
          new LanguageModuleUnit(name_matched, line_number_stack.back())});
      parent = dynamic_cast<NodeT*>(parent->children.back().get());

      start_end_counter++;

    };  // add module

    auto end_match = std::regex_match(current_line, matchers["end"]);
    if (end_match) {
      if (start_end_counter > 0) {
        parent = dynamic_cast<NodeT*>(parent->parent);
        start_end_counter--;
      } else {
      };
    };
  };

  if (start_end_counter > 0) {
    while (root != parent) {
      std::cout << "expected `end` for `" << parent->get_data().get_as_string()
                << "` on line <n> \n";
      parent = dynamic_cast<NodeT*>(parent->parent);
    };

    std::cout << "end missed " << start_end_counter << " times\n";
  } else if (start_end_counter < 0) {
    std::cout << "module missed for end <here>\n";
  } else {
    std::cout << "OK\n";
  };

  */

  logger->log();
  return tree;
};
