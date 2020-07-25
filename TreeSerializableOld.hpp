#pragma once

//#include <cassert>
#include <memory>
#include <string>

#include <vector>

#include "Tree.hpp"
#include "Serializable.hpp"
#include "NodeSerializableOld.hpp"

template <typename Tdata>
class TreeSerializableOld : public Tree<NodeSerializableOld<Tdata>>, Serializable {
public:
  bool test_callback() override;
  std::string get_as_string() const override;

  virtual ~TreeSerializableOld() = default;
};

template <typename Tdata>
bool TreeSerializableOld<Tdata>::test_callback() {
  using NodeS = NodeSerializableOld<Tdata>;

  NodeS* parent = this->root.get();

  parent->children.emplace_back(new NodeS{parent});
  parent->children.emplace_back(new NodeS{parent});
  parent->children.emplace_back(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children[0].get());
  parent->children.emplace_back(new NodeS{parent});
  parent->children.emplace_back(new NodeS{parent});
  parent->children.emplace_back(new NodeS{parent});
  parent->children.emplace_back(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children[0]->children[0].get());
  parent->children.emplace_back(new NodeS{parent});
  parent->children.emplace_back(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children[1].get());
  parent->children.emplace_back(new NodeS{parent});
  parent->children.emplace_back(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children[2].get());

  for (size_t i = 0; i < 5; i++) {
    parent->children.emplace_back(new NodeS{parent});
    parent = dynamic_cast<NodeS*>(parent->children[0].get());
  };

  this->root->get_as_string();

  return true;
};

template <typename Tdata>
std::string TreeSerializableOld<Tdata>::get_as_string() const {
  return this->root->get_as_string();
};
