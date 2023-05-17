
#include "SomeClasses.h"
#include <bitset>

#define SHOWNAMEANDRUN(STR) \
  printTitle(#STR); STR


inline void printTitle(const std::string & title) {
  std::cout << "\n============  " << title <<"  ============\n";
}

template <typename T>
inline void showBits(T inp) {
  long long unsigned int inp_as_int;
  std::memcpy(&inp_as_int, &inp, sizeof(float)); // 2.
  std::bitset<sizeof(T) * 8> x(inp_as_int);
  std::cout << x <<std::endl;
}

// The order of C style casting
// const_cast
// static_cast
// static_cast followed by const_cast
// reinterpret_cast
// reinterpret_cast followed by const_cast

int main() { 
  std::cout << "<<<<<<<<<<< Static Cast examples >>>>>>>>>>>>>> " << std::endl;

  SHOWNAMEANDRUN(SomeClass some1("Abcabd"));
  some1.PrintContents();

  // This does not compile. AnotherClass have no constructor 
  // having input parameters which can be converted from const char *
  // AnotherClass another1("aasdfasdf");

  SHOWNAMEANDRUN(AnotherClass another1(some1));

  SHOWNAMEANDRUN(ThirdPartyClass thirdparty1(some1));

  SHOWNAMEANDRUN(SomeClass some2(thirdparty1));

  SHOWNAMEANDRUN(SomeClass some3(another1));

  SHOWNAMEANDRUN(auto some4 = static_cast<SomeClass> (thirdparty1));

  SHOWNAMEANDRUN(auto some5 = static_cast<SomeClass> (another1));

  SHOWNAMEANDRUN(auto thirdparty2 = (ThirdPartyClass) some1);
  SHOWNAMEANDRUN(auto thirdparty3 = ThirdPartyClass (some1) );

  // This does not compile. This explicitly call conversion constructor 
  // of SomeClass that can match to accept the parameter ThirdPartyClass type.
  // (Match to here meahs : First find the conversion constructor from ThirdPartyClass to SomeClass
  // If there is no such conversion constructor next is to find conversion
  // constructor whose input parameter type is somthing that ThirdPartyClass can be convert to.)
  // SomeClass(thirdparty1);
  
  SHOWNAMEANDRUN(auto ancde = (SomeClass) thirdparty1);

  SHOWNAMEANDRUN(AnotherClass another2(SomeClass("aasdfasdf")));

  std::cout << std::endl << "<<<<<<<<<<< Dynamic Cast examples >>>>>>>>>>>>>> " << std::endl;

  SomeClass* ptr_some1 = &some1;
  
  // Upcast: ptr_base2's static type is SomeBase* object but 
  // actually points to SomeClass* object. in this case dynamic type of 
  // ptr_base2 is SomeClass*
  // static_cast shows the same results
  // C++ also provide implicit static cast from derived to base pointer
  // Therefore no need to use dynamic_cast
  SomeBase* ptr_base2 = ptr_some1;

  // reference version of upcasting
  SomeBase& ref_base2 = some1;

  // This does not compile because int is not a base class of SomeClass
  // int* ptr_int = ptr_some1;
  
  // Of course not possible because there is no conversion ctor or conversion operator
  // int* ptr_int = static_cast<int *>(ptr_some1);

  // dynamic_cast success 
  // ptr_base2's static type is SomeBase* but bound to the SomeClass* dynamic type
  SHOWNAMEANDRUN(auto ptr_some3 = dynamic_cast<SomeClass*>(ptr_base2));
  std::cout << ptr_some3 << std::endl;
  
  // Caution ! possible but it is the reinterpret_cast not dynamic_cast
  // Sometimes the pointer value of base and derived values may different to each other.
  SHOWNAMEANDRUN(auto ptr_some5 = (SomeClass*)ptr_base2);
  std::cout << ptr_some5 << std::endl;


  // dynamic_cast failure 1
  // ThirdPartyClass* is not a derivative of SomeBase;
  SHOWNAMEANDRUN(auto ptr_thirdparty2 = dynamic_cast<ThirdPartyClass*>(ptr_base2));
  std::cout << ptr_thirdparty2 << std::endl;

  SHOWNAMEANDRUN(SomeBase base1("BaseBase"));
  SomeBase* ptr_base1 = &base1;

  // dynamic_cast failure 2
  // the dynamic type of ptr_base1 is SomeBase* not SomeClass*;
  SHOWNAMEANDRUN(auto ptr_some2 = dynamic_cast<SomeClass*>(ptr_base1));
  std::cout << ptr_some2 << std::endl;

  // This is what we didn't expected
  SHOWNAMEANDRUN(auto ptr_some4 = (SomeClass*)ptr_base1);
  std::cout << ptr_some4 << std::endl;

  std::cout << std::endl << "<<<<<<<<<<< Reinterpret cast examples >>>>>>>>>>>>>> " << std::endl;

  SHOWNAMEANDRUN(long long int_val_1 = -1);
  showBits(int_val_1);

  SHOWNAMEANDRUN(long long int_val0 = 0);
  showBits(int_val0);

  SHOWNAMEANDRUN(long long int_val1 = 1);
  showBits(int_val1);
  
  SHOWNAMEANDRUN(long long int_val10000 = 10000);
  showBits(int_val10000);

  SHOWNAMEANDRUN(float float_val_1 = -1.0);
  showBits(float_val_1);

  SHOWNAMEANDRUN(float float_val0 = 0.0);
  showBits(float_val0);

  SHOWNAMEANDRUN(float float_val1 = 1.0);
  showBits(float_val1);
  
  SHOWNAMEANDRUN(float float_val10000 = 10000.0);
  showBits(float_val10000);

  SHOWNAMEANDRUN(showBits(static_cast<float> (int_val10000)));

  // In C++ reinterpret_cast can only perform a specific set of conversions, 
  // explicitly listed in the language specification. 
  // In short, reinterpret_cast can only perform pointer-to-pointer conversions 
  // and reference-to-reference conversions 
  // (plus pointer-to-integer and integer-to-pointer conversions)
  SHOWNAMEANDRUN(showBits(reinterpret_cast<void *> (int_val10000)));

  SHOWNAMEANDRUN(int * ptr_int_arr1 =  reinterpret_cast<int *>((sizeof(int) * 5)));
  std::cout << ptr_int_arr1 << std::endl;
   
  // C - style conversion as reinterpret_cast
  SHOWNAMEANDRUN(int* ptr_int_arr2 = (int*)((sizeof(int) * 5)));
  std::cout << ptr_int_arr2 << std::endl;

  // const cast
  std::cout << std::endl << "<<<<<<<<<<< Const Cast >>>>>>>>>>>>>> " << std::endl;
  

  SHOWNAMEANDRUN(const SomeClass c_some1("Abcabd"));
  c_some1.PrintContents();
  
  // this incurs compile error because SetData is not a const member function,
  // but is tried to used in const object
  // c_some1.SetData("TTTTTTTTTTT")

  const_cast<SomeClass*>(&c_some1)->SetData("TTTTTTTTTTTT");
  c_some1.PrintContents();

  // C-style used as const cast
  ((SomeClass*)(&c_some1))->SetData("YYYYYYYYYYYYY");
  c_some1.PrintContents();


  std::cout << std::endl << "<<<<<<<<<<< C style Error case >>>>>>>>>>>>>> " << std::endl;
  // C-style used as const cast
  auto a = (ThirdPartyClass*)(&c_some1);
  a->PrintContents();


  return 0;
}