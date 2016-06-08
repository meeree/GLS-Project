#ifndef _COMPARE__H_INCLUDED__
#define _COMPARE__H_INCLUDED__

#include "../Symbol/symbol.h" 

struct TreeTableCompare {
   bool operator ()( SymbolWithoutParams const &sym1, SymbolWithoutParams const &sym2 ) const;
};

#endif
