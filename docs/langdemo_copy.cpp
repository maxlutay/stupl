
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <chrono>

class Serializable {
 public:
  virtual std::string get_as_string() const = 0;
  virtual ~Serializable(){};
};

static uint64_t ID_GLOBAL = 0;

class Tree {
 public:
  class Node : public Serializable {
    uint64_t uid = ID_GLOBAL++;

    Node* parent;

   public:
    std::vector<std::unique_ptr<Node> > children;

    Node(Node* parent) : parent(parent){};

    std::string get_as_string() const override {
      static std::string depth_string;

      std::stringstream accumulator;


      if (depth_string.capacity() == 0) {
        depth_string.reserve(128);
      };

      accumulator<< "Node#" << uid << "\n";

      depth_string.push_back(' ');
      depth_string.push_back('|');

      auto pointer_to_child_first = std::cbegin(children);
      auto pointer_to_child_last = std::cend(children) - 1;
      auto pointer_to_child_current = pointer_to_child_first;

      if (children.size() > 1) {
        for (; pointer_to_child_current < pointer_to_child_last;
             pointer_to_child_current += 1) {

          accumulator << depth_string << "-" << (*pointer_to_child_current)->get_as_string() ;
        };
      };


      if (pointer_to_child_current == pointer_to_child_last) {

        depth_string.pop_back();


        accumulator << depth_string << "`-";

        depth_string.push_back(' ');

        accumulator << (*pointer_to_child_last)->get_as_string() ;

      };


      depth_string.pop_back();
      depth_string.pop_back();

      return accumulator.str();
    };
  };

  const std::unique_ptr<Node> root;

  Tree() :root(std::make_unique<Node>(new Node{nullptr})){};
};

//int main() {
  using Node = Tree::Node;

auto from_time = std::chrono::steady_clock::now();


  Tree e;

  auto parent = e.root.get();

  parent->children.emplace_back(new Node{parent});
  parent->children.emplace_back(new Node{parent});
  parent->children.emplace_back(new Node{parent});

  parent = e.root->children[0].get();
  parent->children.emplace_back(new Node{parent});
  parent->children.emplace_back(new Node{parent});
  parent->children.emplace_back(new Node{parent});

  parent = e.root->children[1].get();
  parent->children.emplace_back(new Node{parent});
  parent->children.emplace_back(new Node{parent});



  parent = e.root->children[0]->children[1].get();
  parent->children.emplace_back(new Node{parent});
  parent->children.emplace_back(new Node{parent});


  parent = e.root->children[2].get();


  std::cout << "gj";

  for(size_t i = 0; i < 1500; i++) {
    parent->children.emplace_back(new Node{parent});
    parent = parent->children[0].get();

  }


  //std::cout <<
   e.root->get_as_string();

  std::cout << "elapsed " << std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::steady_clock::now() - from_time).count() << "ms \n";

  std::cout << "\n end";
}