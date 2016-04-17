#ifndef vector
#include <vector>
#endif

class Symbol;
class Value;

class Tree {
protected:
   std::vector<Tree*> const &mChildren;
   Value * const &mTreeEval;
public:
   virtual Value * const &evaluateTree ( Symbol * const &symbolContext, std::vector<Symbol*> &stringContext ) = 0;
   Tree ( std::vector<Tree*> const &children ) : mChildren { children } {}
   virtual ~Tree ();
};
