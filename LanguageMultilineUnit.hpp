

#include "./LanguageUnit.hpp"

#include "./LineNumber.hpp"

class LanguageMultilineUnit : public LanguageUnit {
 private:
  const LineNumber start_line;
  const LineNumber end_line;

 public:
  LanguageMultilineUnit(const std::string& content,
                        const LineNumber from,
                        const LineNumber to)
      : LanguageUnit(content), start_line(from), end_line(to){};

  virtual ~LanguageMultilineUnit() = default;

  LineNumber get_start_line_number() const { return start_line; };

  LineNumber get_end_line_number() const { return end_line; };

  LineNumber get_where_line_number() const { return get_start_line_number(); };

  virtual std::string get_as_string() const override {
    std::string result;
    result += LanguageUnit::get_as_string();
    result += " from line ";
    result += std::to_string(start_line);
    result += " to line ";
    result += std::to_string(end_line);

    return result;
  };
};
