#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Testable.hpp"


template <typename Tnode>
class Tree : public Testable {
 public:
 
  using Tnode = Tnode;

  const std::unique_ptr<Tnode> root;
  virtual bool test_callback() = 0;

  Tree() : root(new Tnode{nullptr}){};
  Tree(Tnode* root_node ) : root(root_node){};

  Tree(const Tree&) = default;
  Tree& operator= (const Tree&) = default;

  virtual ~Tree() = default;
};
