#include "datastore.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
#include <map>

class MyDataStore : public DataStore
{
  public:
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addCart(std::vector<Product*>& hits, size_t index, std::string user); 
    void viewCart(std::string user);
    void buyCart(std::string user); 
    ~MyDataStore(); 
  private: 
    std::set<Product*> products_; 
    std::map<User*, std::vector<Product*>> user_cart; // should i tbe product* ? 
};

