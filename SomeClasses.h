#pragma once

#include <iostream>
#include <string>

class SomeBase {
public:
  SomeBase(const std::string& str_in)
    :str_data(str_in) {}

  virtual void PrintContents() const {
    std::cout << "This is SomeBase function" << std::endl;
  }

  const std::string getData() const { return str_data; }

  void SetData(const std::string& str_in) { str_data = str_in; }

private:
  std::string str_data;
};

class SomeClass : public SomeBase {
public:
  SomeClass(const std::string& str_in)
    :SomeBase(str_in)
  {
    std::cout << "SomeeClass::SomeClass(const std::string & str_in) called !!" << std::endl;
  }
  SomeClass(const SomeBase& any_in)
    :SomeBase(any_in.getData()) 
  {
    std::cout << "SomeClass(const SomeBase & any_in) called !!" << std::endl; 
  }
  void PrintContents() const override final {
    std::cout << "This is SomeClass function: Contents:" << getData() << std::endl;
  }
};

class AnotherClass : public SomeBase {
public:
  AnotherClass(const SomeClass& str_in)
    :SomeBase(str_in.getData())
  {
    std::cout << "AnotherClass::AnotherClass(const SomeClass& str_in) called !!" << std::endl;
  }

  void PrintContents() const override final {
    std::cout << "This is AnotherClass function: Contents:" << getData() << std::endl;
  }

  operator SomeClass() const {
    std::cout << "TheOtherClass::operator SomeClasse() called !!" << std::endl;
    return SomeClass(getData());
  }
};

class ThirdPartyClass {
public:
  ThirdPartyClass(const SomeClass& str_in)
    :str_data(str_in.getData())
  {
    std::cout << "ThirdPartyClass::ThirdPartyClass(const SomeClass& str_in) called !!" << std::endl;
  }

  void PrintContents() const {
    std::cout << "This is ThirdPartyClass function: Contents:" << str_data << std::endl;
  }

  operator SomeClass() const {
    std::cout << "ThirdPartyClass::operator SomeClasse() called !!" << std::endl;
    return SomeClass(str_data);
  }

private:
  std::string str_data;
};