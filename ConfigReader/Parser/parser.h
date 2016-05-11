#ifndef map
#include <map>
#endif
#ifndef vector
#include <vector>
#endif
#ifndef utility
#include <utility>
#endif
#ifndef string
#include <string>
#endif
#ifndef SYMBOL_H
#define SYMBOL_H
#include "../Symbol/symbol.h"
#endif

class Tree;
class Token;

struct TreeTableCompare {
   bool operator ()( SymbolWithoutParams const &sym1, SymbolWithoutParams const &sym2 ) const;
};

class Parser {
private:
   std::vector<Token> mTokenString;
   std::vector<Token>::iterator mIter;

   std::vector<Symbol> mAxiom;
   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> mTreeTable;
   std::vector<SymbolWithoutParams> mConstants; 

   bool strCheck ( std::string const &str ) const;

   void parseAxiom ();
   void parseConstants ();
   void parseVariables ();
   void parseProductions ();

   Tree * andExpr ();
   Tree * cndExpr ();
   Tree * stringExpr ();
   Tree * addExpr ();
   Tree * mulExpr ();
   Tree * powExpr ();
   Tree * brackExpr ();
   Tree * staticNumExpr ();
   Tree * dynamicNumExpr ();

public:
   Parser ( std::vector<Token> const &tokenString );
   ~Parser ();
   void mainParse ();
};
