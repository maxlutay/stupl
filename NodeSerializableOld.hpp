#pragma once




#include "EnumerableUnique.hpp"
#include "Serializable.hpp"
#include "Node.hpp"



template <typename Tdata>
class NodeSerializableOld : public Node, Serializable, EnumerableUnique {
  std::unique_ptr<Serializable> data;

 public:
  std::string get_as_string() const override;

  NodeSerializableOld<Tdata>(NodeSerializableOld* parent) : Node(parent) {};

  NodeSerializableOld<Serializable>(NodeSerializableOld* parent) :Node(parent){};
  NodeSerializableOld<Serializable>(NodeSerializableOld* parent, Serializable data)
      : Node(parent), data(std::make_unique(data)) {};

  virtual ~NodeSerializableOld<Tdata>() = default;
};




template <typename Tdata>
std::string NodeSerializableOld<Tdata>::get_as_string() const {



  using Сhildren_const_iterator = decltype(std::cbegin(children));

  struct FirstCurrentLast {
    const Сhildren_const_iterator first;
    Сhildren_const_iterator current;
    const Сhildren_const_iterator last;
  };

  std::vector<FirstCurrentLast> stack;

  std::string accumulator;
  accumulator.reserve(128);  // experimental speedup value
  accumulator.append("Node#").append(std::to_string(this->uid));

  if (data)
    accumulator.append("{").append(data->get_as_string()).append("}");

  accumulator.append("\n");

  std::string depth_string;
  depth_string.reserve(128);
  depth_string.append(" |");

  stack.push_back({std::cbegin(this->children), std::cbegin(this->children),
                   std::cend(this->children)});

  while (!stack.empty()) {
    auto& its = stack.back();
    auto& current = its.current;
    auto last = its.last;

    if (current == last) {
      stack.pop_back();

      depth_string.pop_back();
      depth_string.pop_back();

      continue;
    };

    if (current < last) {
      if (current == (last - 1)) {
        depth_string.pop_back();
        depth_string.push_back('`');
      };

      accumulator.append(depth_string)
          .append("-Node#")
          .append(std::to_string(
              dynamic_cast<NodeSerializableOld*>(current->get())->uid))
          .append("\n");

      if (current == (last - 1)) {
        depth_string.pop_back();
        depth_string.push_back(' ');
      };
    };

    if (!current->get()->children.empty()) {
      depth_string.push_back(' ');
      depth_string.push_back('|');

      stack.push_back({std::cbegin(current->get()->children),
                       std::cbegin(current->get()->children),
                       std::cend(current->get()->children)});

      stack.at(stack.size() - 2).current++;
      // cause itrs.current++ is invalidated by push_back
    } else {
      current++;
    };

  };  // end while

  return accumulator;
};

