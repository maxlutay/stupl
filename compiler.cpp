
#include <fstream>
#include <memory>
#include <utility>
#include <iostream>

#include "SyntaxTree.hpp"
#include "LanguageLexicalUnit.hpp"

#include "ParserBlocks.hpp"


int main() {

  std::string filename {"test/modules.stupl"};





  std::ofstream ofs_logs{"logs/testresultsn.log"};
  auto logger = std::make_shared<LazyLogger>(&std::cout, &ofs_logs);


  ParserBlocks parser_from_file_to_blocks{logger};


  auto source_program = std::ifstream{filename};
  auto blocks_tree = parser_from_file_to_blocks(source_program);

  std::cout << *blocks_tree;

/*
  std::fstream file{filename};

  using NodeT = SyntaxTree::Tnode;
  std::unique_ptr<SyntaxTree> tse{ new SyntaxTree{new NodeT(nullptr) }};

  auto root = tse->root.get();
  auto parent = root;


  parent->children.emplace_back(new NodeT(parent,new LanguageUnit{"module communicating"}));

  parent = dynamic_cast<NodeT*>( parent->children[0].get() );
  parent->children.emplace_back(new NodeT(parent, new LanguageLexicalUnit("fn hello(@to:std.string)->void") ));

  parent = dynamic_cast<NodeT*>( parent->children[0].get() );
  parent->children.emplace_back(new NodeT(parent,new LanguageLexicalUnit("//fn hello body") ));

  parent = dynamic_cast<NodeT*>(parent->parent);

  parent->children.emplace_back(new NodeT(parent, new LanguageLexicalUnit("fn bye(@to:std.string)->void") ));

  parent = dynamic_cast<NodeT*>( parent->children[1].get() );
  parent->children.emplace_back(new NodeT(parent,new LanguageLexicalUnit("//fn bye body") ));

  std::cout << root->get_as_string();

*/

};