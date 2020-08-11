#pragma once

#include "EnumerableUnique.hpp"
#include "Serializable.hpp"
#include "DataNode.hpp"

template <typename Tdata>
class NodeSerializable : public DataNode<Serializable>,
                         Serializable,
                         EnumerableUnique {
 public:
  std::string get_as_string() const override;
  NodeSerializable<Tdata>(NodeSerializable* parent) : DataNode(parent){};
  NodeSerializable<Tdata>(NodeSerializable* parent, Tdata* d)
      : DataNode(parent, d){};  // implicit cast to Serializable
};

template <typename Tdata>
std::string NodeSerializable<Tdata>::get_as_string() const {
  using Сhildren_const_iterator = decltype(std::cbegin(children));

  struct FirstCurrentLast {
    const Сhildren_const_iterator first;
    Сhildren_const_iterator current;
    const Сhildren_const_iterator after_last;
  };

  std::vector<FirstCurrentLast> stack;

  auto print_stack = [&stack]() {
    std::cout << "/stack.size= " << stack.size() << "\n";

    std::string row1, row2, row3;
    for (auto&& it : stack) {
      row1.append(std::to_string(0)).append("_.");
      row2.append(std::to_string(it.current - it.first)).append("_.");
      row3.append(std::to_string(it.after_last - it.first)).append("_.");
    };

    std::cout << "first  |" << row1 << ";\n";
    std::cout << "current|" << row2 << ";\n";
    std::cout << "last   |" << row3 << ";\n\n";
  };

  std::string accumulator;
  accumulator.reserve(128);  // experimental speedup value
  accumulator.append("Node#").append(std::to_string(this->uid));

  if (this->data)
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
    auto af_last = its.after_last;

    // print_stack();

    if (current == af_last) {
      // TODO: check circular dependency
      stack.pop_back();

      depth_string.pop_back();
      depth_string.pop_back();

      continue;
    };

    if (current < af_last) {
      if (current == (af_last - 1)) {
        depth_string.pop_back();
        depth_string.push_back('`');
      };

      auto ns = dynamic_cast<NodeSerializable*>(current->get());

      accumulator.append(depth_string)
          .append("-Node#")
          .append(std::to_string(ns->uid));

      if (ns->data)
        accumulator.append("{").append(ns->data->get_as_string()).append("}");

      accumulator.append("\n");

      if (current == (af_last - 1)) {
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
