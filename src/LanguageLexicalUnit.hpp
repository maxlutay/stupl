#pragma once

#include "LanguageUnit.hpp"

class LanguageLexicalUnit : public LanguageUnit {
  using LanguageUnit::LanguageUnit;//inheriting all constructors
  virtual ~LanguageLexicalUnit() = default;
};