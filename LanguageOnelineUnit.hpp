

#include "./LanguageUnit.hpp"

#include "./LineNumber.hpp"

class LanguageOnelineUnit : public LanguageUnit {
 private:
  const LineNumber where_line;

 public:
  LanguageOnelineUnit(const std::string& content, const LineNumber where)
      : LanguageUnit(content), where_line(where){};

  ~LanguageOnelineUnit() = default;

  LineNumber get_start_line_number() const { return where_line; };
  LineNumber get_end_line_number() const { return where_line; };
  LineNumber get_where_line_number() const { return where_line; };
};
