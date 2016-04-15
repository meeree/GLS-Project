#ifndef map 
#include <map>
#endif 
#ifndef string
#include <string>
#endif 

class Symbol {
private:
   std::string mName;
   std::map<std::string, double> mParams;
public:
   Symbol ( std::string const &name, std::map<std::string, double> const &params ) : mName { name }, mParams { params } {}
   double const &getParam ( std::string const &key ) const { return mParams.at(key); } 
   std::string const &getName () const { return mName; } 
};

