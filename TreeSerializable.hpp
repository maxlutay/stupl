#pragma once

//#include <cassert>
#include <memory>
#include <string>

#include <vector>

#include "Tree.hpp"
#include "Serializable.hpp"
#include "NodeSerializable.hpp"

template <typename Tdata>
class TreeSerializable : public Tree<NodeSerializable<Tdata>>, Serializable {
public:

  using Tree<NodeSerializable<Tdata>>::Tree;//inheriting constructors

  bool test_callback() override;
  std::string get_as_string() const override;

  virtual ~TreeSerializable() = default;
};

template <typename Tdata>
bool TreeSerializable<Tdata>::test_callback() {


  using NodeS = NodeSerializable<Tdata>;

  NodeS* parent = this->root.get();

  parent->children
  .construct_child(new NodeS{parent})
  .construct_child(new NodeS{parent})
  .construct_child(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children.front().get());
  parent->children
  .construct_child(new NodeS{parent})
  .construct_child(new NodeS{parent})
  .construct_child(new NodeS{parent})
  .construct_child(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children.front()->children.front().get());
  parent->children
  .construct_child(new NodeS{parent})
  .construct_child(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children.at(1).get());
  parent->children.construct_child(new NodeS{parent})
  .construct_child(new NodeS{parent});

  parent = dynamic_cast<NodeS*>(this->root->children.at(2).get());

  for (size_t i = 0; i < 5; i++) {
    parent->children.construct_child(new NodeS{parent});
    parent = dynamic_cast<NodeS*>(parent->children.front().get());
  };

  this->root->get_as_string();

  return true;

};


template <typename Tdata>
std::string TreeSerializable<Tdata>::get_as_string() const {
  return this->root->get_as_string();
};
