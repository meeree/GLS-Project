#include <iostream>
#ifndef SYMBOL_H
#define SYMBOL_H
#include "symbol.h"
#endif

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
   for ( auto const &key: symW.second ) {
      if ( mParams.find ( key ) == mParams.end () ) {
         return false;
      }
   }
   return true;
}
