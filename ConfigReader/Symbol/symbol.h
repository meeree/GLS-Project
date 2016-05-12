#ifndef __SYMBOL_H_INCLUDED__
#define __SYMBOL_H_INCLUDED__

#include <map>
#include <string>
#include <vector>

typedef std::pair<std::string, std::vector<std::string> > SymbolWithoutParams;

class Symbol {
private:
   std::string mName;
   std::map<std::string, double> mParams;
public:
   Symbol () = default;
   Symbol ( Symbol const &sym );
   Symbol ( std::string const &name, std::map<std::string, double> const &params );
   void setName ( std::string const &newName );
   void addParam ( std::string const &paramName, double const &paramVal );
   std::string getName () const;
   double getParam ( std::string const &key ) const;
   bool check ( SymbolWithoutParams const &symW ) const;
   void print () const;
};

#endif
