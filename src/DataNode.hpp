#pragma once

#include <memory>

#include "Node.hpp"

template <typename Tdata>
class DataNode : public Node {
 protected:
  const std::unique_ptr<Tdata> data;

 public:
  DataNode<Tdata>(DataNode* parent) : Node(parent){};
  DataNode<Tdata>(DataNode* parent, Tdata* data)
      : Node(parent), data(data){};
    
  Tdata& get_data() const{
      return *data.get();
  };
};
