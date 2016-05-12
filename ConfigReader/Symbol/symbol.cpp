#include "symbol.h"
#include <iostream>

Symbol::Symbol ( std::string const &name, std::map<std::string, double> const &params ) : mName { name }, mParams { params } {
}
Symbol::Symbol ( Symbol const &sym ) : mName { sym.mName }, mParams { sym.mParams } {
}
void Symbol::setName ( std::string const &newName ) {
   mName = newName;
}
void Symbol::addParam ( std::string const &paramName, double const &paramVal ) {
   mParams[paramName] = paramVal;
}
std::string Symbol::getName () const {
   return mName;
}
double Symbol::getParam ( std::string const &key ) const {
   return mParams.at ( key );
}
bool Symbol::check ( SymbolWithoutParams const &symW ) const {
   if ( getName () != symW.first ) {
      return false;
   } 
   if ( mParams.size() != symW.second.size() ) {
      return false;
   }
   for ( auto const &paramName: symW.second ) {
      if ( mParams.find ( paramName ) == mParams.end () ) {
         return false;
      }
   }
   return true;
}
void Symbol::print () const {
   std::cout<<mName<<'(';
   int i { 0 };
   for ( auto const &param: mParams ) {
      std::cout<<param.second;
      if ( i < mParams.size () - 1 ) {
         std::cout<<',';
      }
      ++i;
   }
   std::cout<<')';
}
