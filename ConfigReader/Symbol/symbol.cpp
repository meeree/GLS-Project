#include <iostream>
#ifndef SYMBOL_H
#define SYMBOL_H
#include "symbol.h"
#endif

Symbol::Symbol ( std::string const &name, std::map<std::string, double> const &params ) : mName { name }, mParams { params } {
}
Symbol::Symbol ( Symbol const &sym ) : mName { sym.mName }, mParams { sym.mParams } {
   std::cout<<"name: "<<sym.mName<<std::endl;
   std::cout<<"params: ";
   for (auto const &p: mParams) {
      std::cout<<p.first<<":"<<p.second<<",";
   }
   std::cout<<std::endl;
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
