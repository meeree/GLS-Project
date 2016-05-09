#ifndef MEMORY_H
#define MEMORY_H
#include "memory.h"
#endif

void MemoryUnit::MemoryUnit () {
}
void MemoryUnit::setString ( std::vector<Symbol> const &newString ) {
   mString = newString;
}
void MemoryUnit::pushString ( Symbol const &pushSymbol ) {
   mString.push_back ( pushSymbol );
}
void MemoryUnit::setSymbol ( Symbol const &newSymbol ) {
   mSymbol = newSymbol;
}
std::vector<Symbol> const &MemoryUnit::getString () const {
   return mString;
}
Symbol const &MemoryUnit::getSymbol () const {
   return mSymbol;
}
