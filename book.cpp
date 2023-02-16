#include "book.h"
#include "util.h"
#include <iostream>
#include "product.h"

using namespace std; 

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author) :
    Product(category, name, price, qty){
      ISBN_ = ISBN;
      author_ = author; 
      lower_author_ = convToLower(author); 
      lower_name_ = convToLower(name); 
  }

set<string> Book::keywords() const{
  set<string> myset; 
  set<string> author = parseStringToWords(lower_author_); 
  set<string> name = parseStringToWords(lower_name_); 
  myset = setUnion(author, name); 
  myset.insert(ISBN_);
  // set<string>::iterator second_it;
  // for (second_it = myset.begin(); second_it != myset.end(); second_it++){
  //   cout << *second_it << " "; 
  // }
  return myset; 
}


string Book::displayString() const{
  string mystring = name_ + "\n" + "Author: " + author_ + " ISBN: " + ISBN_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
  return mystring; 
}

void Book::dump(ostream& os) const{
  os << "book" << "\n" << name_ << "\n" << to_string(price_) << "\n" << to_string(qty_) << "\n" << ISBN_ << "\n" << author_ << endl;
}
