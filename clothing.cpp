#include "clothing.h"
#include "util.h"
#include <iostream>
#include <string>
using namespace std; 

Clothing::Clothing(const string category, const string name, double price, int qty, string size, string brand) :
    Product(category, name, price, qty){
      size_ = size;
      brand_ = brand; 
      lower_brand_ = convToLower(brand);
      lower_name_ = convToLower(name); 
  }

set<string> Clothing::keywords() const{
  set<string> myset; 
  set<string> brand = parseStringToWords(convToLower(lower_brand_)); 
  set<string> name = parseStringToWords(convToLower(lower_name_)); 
  myset = setUnion(brand, name);
  // set<string>::iterator second_it;
  // for (second_it = myset.begin(); second_it != myset.end(); second_it++){
  //   cout << *second_it << " "; 
  // } 
  return myset; 
}


string Clothing::displayString() const{
  string mystring = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
  return mystring; 
}

void Clothing::dump(ostream& os) const{
  os << "clothing" << "\n" << name_ << "\n" << to_string(price_) << "\n" << to_string(qty_) << "\n" << size_ << "\n" << brand_ << endl;
}
