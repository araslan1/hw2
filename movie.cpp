#include "movie.h"
#include "util.h"
#include <iostream>
#include <string>


Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
    Product("movie", name, price, qty){
      genre_ = genre;
      rating_ = rating; 
      lower_genre_ = convToLower(genre); 
      lower_name_ = convToLower(name); 
  }

std::set<std::string> Movie::keywords() const{
  std::set<std::string> myset; 
  std::set<std::string> genre = parseStringToWords(convToLower(lower_genre_)); 
  std::set<std::string> name = parseStringToWords(convToLower(lower_name_)); 
  myset = setUnion(genre, name); 
  // std::set<std::string>::iterator second_it;
  // for (second_it = myset.begin(); second_it != myset.end(); second_it++){
  //   std::cout << *second_it << " "; 
  // }
  return myset; 
}


std::string Movie::displayString() const{
  std::string mystring = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
  return mystring; 
}

void Movie::dump(std::ostream& os) const{
  os << "movie" << "\n" << name_ << "\n" << std::to_string(price_) << "\n" << std::to_string(qty_) << "\n" << genre_ << "\n" << rating_ << std::endl;
}
