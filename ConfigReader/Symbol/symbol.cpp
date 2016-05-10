#ifndef SYMBOL_H
#define SYMBOL_H
#include "symbol.h"
#endif

Symbol::Symbol ( Symbol const &sym ) : mName { sym.mName }, mParams { sym.mParams } {
}
Symbol::Symbol ( std::string const &name, std::map<std::string, double> const &params ) : mName { name }, mParams { params } {
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
