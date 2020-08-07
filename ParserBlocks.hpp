#pragma once

#include <fstream>
#include "SyntaxTree.hpp"
#include "LineNumber.hpp"
#include "./LanguageModuleUnit.hpp"


#include <array>
#include <tuple>
#include <regex>
#include <istream>
#include <map>

class ParserBlocks {
 private:
  // struct LineNumberStackEntry{
  //   LineNumber line;
  //   std::string filename;
  // };

  //std::vector<LineNumber> line_number_stack;  // for multiple file indexing

  std::map<std::string, std::regex> matchers;

  LazyLogger logger{std::cout};

 public:
  ParserBlocks();
  ParserBlocks(const ParserBlocks&) = default;

  std::unique_ptr<SyntaxTree> operator()(std::istream&);

 private:
  std::vector<const std::pair<LineNumber, LineNumber>> match_start_end_lines(
      std::istream&) const;
};

ParserBlocks::ParserBlocks() {
  matchers.emplace("module", "\\s*module\\s+(\\w+)\\s*;?.*");
  matchers.emplace("type", "\\s*type\\s+(\\w+)\\s+is.*");
  matchers.emplace("string_oneliner",
                   "[\\S\\s]*(\"[\\S\\s]*\")|('[\\S\\s]*')[\\S\\s]*");
  matchers.emplace("function", "\\s*f(n)|(un(ction)?)\\s+(\\w+)\\s*");

  matchers.emplace("end", "^\\s*end\\s*;?.*");

  //line_number_stack.push_back(-1);
};

auto ParserBlocks::match_start_end_lines(std::istream& program) const {
  std::vector<const std::pair<LineNumber, LineNumber>> result{};

  std::string current_line;

  LineNumber counter_line = 0;

  std::vector<LineNumber> start_lines;

  while (std::getline(program, current_line)) {
    bool start_match_flag = std::regex_match(current_line, matchers["module"]);
    start_match_flag |= std::regex_match(current_line, matchers["function"]);
    start_match_flag |= std::regex_match(current_line, matchers["type"]);

    if (start_match_flag) {
      start_lines.push_back(counter);
    };

    bool end_match_flag = std::regex_match(current_line, matchers["end"]);

    if (end_match_flag) {
      result.emplace_back(start_lines.back(), counter_line);
      start_lines.pop_back();
    };

    counter++;
  };

  if(not start_lines.empty()) {
      result.emplace_back(start_lines.back(), counter);
      start_lines.pop_back();
      logger.append("no matching end for declaration on line")
      .append(std::to_string(counter))

  };

};

std::unique_ptr<SyntaxTree> ParserBlocks::operator()(std::istream& program) {
  using NodeT = SyntaxTree::Tnode;
  auto tree = std::make_unique<SyntaxTree>(new NodeT{nullptr});

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

  return tree;
};
