#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif
#ifndef SYMBOL_H
#define SYMBOL_H
#include "symbol.h"
#endif
#ifndef vector
#include <vector>
#endif

class Tree {
protected:
   Tree () {}
public:
   virtual Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) = 0;
};

class StorageFuncTree: public Tree {
protected:
   Value * mReturnValue;
   StorageFuncTree () {}
   StorageFuncTree ( Value * const &returnValue ) : mReturnValue { returnValue } {}
   ~StorageFuncTree () { delete mReturnValue; } 
   virtual Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) = 0;
};

class Leaf : public Tree {
private:
   Value * mStoredValue;
public:
   ~Leaf () { delete mStoredValue; } 
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) const { return mStoredValue; } 
};
