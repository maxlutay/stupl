


#include "./LanguageMultilineUnit.hpp"

class LanguageModuleUnit : public LanguageMultilineUnit {

public: 
  using LanguageMultilineUnit::LanguageMultilineUnit;

  virtual std::string get_as_string() const override;

};




std::string LanguageModuleUnit::get_as_string() const{
  //TODO: stringbuilder!!
  std::string result{""};
  result += "module ";

  result += LanguageMultilineUnit::get_as_string();

  return result;
};





