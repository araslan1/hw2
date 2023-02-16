#include "mydatastore.h"
#include <map>
#include <iostream>
#include "util.h"
using namespace std; 


void MyDataStore::addProduct(Product* p){
  products_.insert(p); 
}

void MyDataStore::addUser(User* u){
  user_cart[u]; 
}




vector<Product*> MyDataStore::search(vector<string>& terms, int type){
  vector<Product*> myvec; 
  // set<Product*>::iterator it; 
  // set<string>::iterator second_it; 
  // for (it = products_.begin(); it != products_.end(); it++){
  //   set<string> keys = (*it)->keywords(); 
  //   // cout << "KEYS" << endl; 
  //   // for (second_it = keys.begin(); second_it != keys.end(); second_it++){
  //   //   cout << (*second_it) << " "; 
  //   // }
  //   if (keys.find("Drama") != keys.end()){
  //     myvec.push_back(*it); 
  //   }
  // }
  // set<Product*>::iterator it; 
  // for (it = products_.begin(); it != products_.end(); it++){
  //   cout << "KEYWORDS" << endl; 
  //   set<string> curr = (*it)->keywords();
  //   cout << endl; 
  // }
  // for (it = products_.begin(); it != products_.end(); it++){
  //   cout << "NAME" << endl; 
  //   cout << (*it)->getName() << endl; 
  // for (int i = 0; i < terms.size(); i++){
  //   cout << terms[i] << endl; 
  // }
  if (type == 0){
    //this is AND
    set<Product*>::iterator it; 
    for (it = products_.begin(); it != products_.end(); it++){
      bool pass = true; 
      set<string> keys = (*it)->keywords(); 
      for (size_t i = 0; i < terms.size(); i++){
        if (keys.find(terms[i]) == keys.end()){
          pass = false;
          break; 
        }
      }
      if (pass == true){
        myvec.push_back(*it); 
      }
    }
  }else if (type == 1){
    //this is OR
    set<Product*>::iterator it; 
    set<string>::iterator second_it; 
    for (size_t i = 0; i < terms.size(); i++){
      for (it = products_.begin(); it != products_.end(); it++){
        set<string> keys = (*it)->keywords(); 
        if (keys.find(terms[i]) != keys.end()){
          myvec.push_back(*it); 
        }
      }
    }
  }
  return myvec; 
}


void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>\n"; 
  set<Product*>::iterator it; 
  for (it = products_.begin(); it != products_.end(); it++){
    (*it)->dump(ofile); 
  }
  ofile << "</products>\n";
  map<User*, vector<Product*>>::iterator second_it;
  ofile << "<users>\n"; 
  for (second_it = user_cart.begin(); second_it != user_cart.end(); second_it++){
    second_it->first->dump(ofile); 
  }
  ofile << "</users>\n";
}


void MyDataStore::addCart(std::vector<Product*>& hits, size_t index, std::string user){
  //add to Cart
  Product* new_product = hits[index]; 
  std::map<User*, std::vector<Product*>>::iterator it; 
  bool found = false; 
  for (it = user_cart.begin(); it != user_cart.end(); it++){
    string curr_name = it->first->getName(); 
    if (convToLower(curr_name) == convToLower(user)){
      found = true; 
      break; 
    }
  }
  if (found == false){
    cout << "Invalid request" << endl; 
    return; 
  }
  user_cart[it->first].push_back(new_product); 
} 


void MyDataStore::viewCart(std::string user){
  std::map<User*, std::vector<Product*>>::iterator it;
  bool found = false;  
  for (it = user_cart.begin(); it != user_cart.end(); it++){
    string curr_name = it->first->getName(); 
    if (convToLower(curr_name) == convToLower(user)){
      found = true; 
      break; 
    }
  }
  if (found == false){
    cout << "Invalid request" << endl; 
    return; 
  }
  vector<Product*> items = user_cart[it->first]; 
  for (size_t i = 0; i < items.size(); i++){
    cout << "Item " << i+1 << endl; 
    cout << items[i]->displayString() << endl;
    cout << endl; 
  }
}


void MyDataStore::buyCart(std::string user){
  std::map<User*, std::vector<Product*>>::iterator it;
  bool found = false;  
  for (it = user_cart.begin(); it != user_cart.end(); it++){
    string curr_name = it->first->getName(); 
    if (convToLower(curr_name) == convToLower(user)){
      found = true; 
      break; 
    }
  }
  if (found == false){
    cout << "Invalid request" << endl; 
    return; 
  }
  User* myUser = it->first; 
  vector<Product*> items = user_cart[it->first]; 
  for (size_t i = 0; i < items.size(); i++){
    double price = items[i]->getPrice(); 
    int qty = items[i]->getQty(); 
    if ((qty != 0) && ((myUser->getBalance()) >= price)){
      user_cart[it->first].erase(user_cart[it->first].begin()); 
      items[i]->subtractQty(1); 
      myUser->deductAmount(price); 
    }
  }
}

MyDataStore::~MyDataStore(){
  set<Product*>::iterator it; 
  for (it = products_.begin(); it != products_.end(); it++){
    delete (*it); 
  }
  std::map<User*, std::vector<Product*>>::iterator second_it;
  for (second_it = user_cart.begin(); second_it != user_cart.end(); second_it++){
    delete second_it->first;  
  }
}