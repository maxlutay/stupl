#pragma once

// using LineNumber = int64_t; //basically this but with exception in constructor and derived class

#include <exception>

class LineNumber {
  using LineNumberStorageType = int64_t;
  LineNumberStorageType value;

 public:
  LineNumber() : value(0){};

  LineNumber(LineNumberStorageType value) : value(value) {
    if (value < 0)
      throw std::logic_error("LineNumber should be >= 0");
  };

  LineNumber(const LineNumber&) = default;
  LineNumber& operator=(const LineNumber&) = default;

  LineNumber(LineNumber&&) = default;
  LineNumber& operator=(LineNumber&&) = default;

  bool operator==(const LineNumber& comparable) const {
    return value == comparable.value;
  };

  bool operator<(const LineNumber& comparable) const {
    return value < comparable.value;
  };
  bool operator<=(const LineNumber& comparable) const {
    return value <= comparable.value;
  };

  bool operator>(const LineNumber& comparable) const {
    return value > comparable.value;
  };

  bool operator>=(const LineNumber& comparable) const {
    return value >= comparable.value;
  };

  operator LineNumberStorageType() const { return value; };

  LineNumber& operator++() {
    value++;
    return *this;
  };

  LineNumber operator++(int){
    LineNumber tmp(*this);
    operator++();
    return tmp;
  }

  LineNumber& operator+=(const LineNumber& l) { value += l.value; };

  friend LineNumber operator+(LineNumber ln1, const LineNumber& ln2) {
    return ln1 += ln2;
  };
};

struct EmptyLineNumber : LineNumber {
  const bool invalid = true;
  EmptyLineNumber() : LineNumber(0){};

  bool operator==(const EmptyLineNumber& el){
    return invalid == el.invalid;//wtf xD ?
  };

  bool operator+=(const EmptyLineNumber&) = delete;
  

};

static EmptyLineNumber EmptyLineNumber{};  // initialization