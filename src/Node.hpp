#pragma once

#include <memory>

#include "NodeChildrenContainer.hpp"

#include <vector>

class Node {
 public:
  Node* parent;

  //std::vector<std::unique_ptr<Node> > children;
  NodeChildrenContainer<std::unique_ptr<Node> > children;


  Node(Node* parent) : parent(parent){};
  virtual ~Node() = default;
};