

#include <algorithm>
#include <array>
#include <fstream>
#include <list>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using ProgramLine = std::pair<const size_t, const std::string>;

class ProgramLines : std::vector<const ProgramLine> {
 private:
  using container = std::vector<const ProgramLine>;
  container text_lines;

 public:
  using container::begin;
  using container::emplace_back;
  using container::end;
};

class Compiler final {
 private:
  const std::vector<const std::string> BLOCK_NAMES{"module", "class",
                                                   "fn"};  // should be here ??

 private:
  ProgramLines read_file_to_lines(const std::string& filename) const {
    ProgramLines lines;
    std::ifstream filestream{filename};
    std::string buffer;
    buffer.reserve(100);

    size_t line_number = 0;
    while (std::getline(filestream, buffer)) {
      if (!buffer.empty()) {
        lines.emplace_back(line_number, buffer);  // push copy of buffer
        buffer.clear();
      };
      ++line_number;  // increment anyway
    };

    return lines;  // hope nrvo
  };

  void resolve_macro(){
      // todo: macro processing
  };

  auto lines_to_blocks(const ProgramLines& lines) {
    BlockTree block_structure;

    size_t current_line_number = 0;
    std::for_each(std::begin(lines), std::end(lines),
                  [&block_structure](auto& line) {
                    if (has_end_in(line.second)) {
                      if (current_line_number <)
                    }
                    if (auto name = get_block_name_in(line)) {
                      blocks.emplace_back(name);
                      blocks.back().line_from = current_line_number;
                      ++current_line_number;
                    };
                  });
    // todo

    return block_structure;
  };

  std::optional<const std::string&> get_block_name_in(const std::string& line) {
    for (auto& block_name : BLOCK_NAMES) {
      auto found_at = line.find(block_name);
      if (found_at != std::string::npos) {
        return std::optional<std::string>{
            line.substr(found_at, block_name.length)};
      };
    };
    return std::nullopt;
  };

  auto blocks_to_ast(const BlockTree& blocks){

  };

  const std::stringstream compile() const {
    // write llvm/asm/bytecode to stream
    std::stringstream ss_write_to;

    return ss_write_to;
  };

 public:
  Compiler& source_from_file(const std::string& from_filename) {
    auto lines = read_file_to_lines(from_filename);
    auto blocks = lines_to_blocks(lines);
  };

  Compiler& compile_to_file(const std::string& to_filename) {
    std::ofstream file{ to_filename };
    const std::stringstream compiled_program = compile();
  
    file <<  compiled_program.rdbuf() << std::endl;

    return *this;
  };

  Compiler& compile_to_file() {
    compile_to_file("a.myout");
    return *this;
  };
  
};

class BlockTree {
  std::list<Block&> blocks;

  Block* current = nullptr;
};

class Block : TreeNode<Block, std::list<std::unique_ptr<Block> > > {
 public:
  const std::string name;

  size_t line_from, line_to;

  Block(const std::string& name, size_t start_line)
      : name(name), line_from(start_line){};

  Block& add_child(Block& childblock) {
    children.emplace_back(childblock);
    return *children.back().get();
  };
};

template <class T, class TContainer = std::list<T*> >
class TreeNode {
 protected:
  T* parent;  // not ownership

  TContainer children;

 public:
  virtual void add_child(std::unique_ptr<T>&& child) {
    TContainer.push_back(child);
  };
};

// int main(int argc, char** argv) {
//   if (argc < 1) {
//     throw std::runtime_error("no required parameters");
//   };
//   // parse rest command-line arguments


//   Compiler main_program;

//   main_program.source_from_file(argv[0]).compile_to_file();
// }