#include <vector>




template <typename ChildT>
class NodeChildrenContainer{
  private:

  std::vector<ChildT> storage;

  public:

  auto& at(uint64_t index) const {
    return storage.at(index);
  };

  auto& front() const{
    return storage.front();
  };

  auto& back() const {
    return storage.back();
  };

  NodeChildrenContainer& add(const ChildT& what) {
    storage.push_back(what);
    return *this;
  };

  template <class... Args>
  NodeChildrenContainer& construct_child(Args&&... args){
    storage.emplace_back(std::forward<Args>(args)...);
    return *this;
  };


  auto begin() const {
    return std::cbegin(storage);
  };

  auto end() const {
    return std::cend(storage);
  };

  auto empty(){
    return storage.empty();
  };

};
