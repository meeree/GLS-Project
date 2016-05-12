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
   static std::map<std::string, unsigned> cndTable;

   std::vector<Token> mTokenString;
   std::vector<Token>::iterator mIter;

   std::vector<Symbol> mAxiom;
   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> mTreeTable;
   std::vector<SymbolWithoutParams> mConstants; 

   bool strCheck ( std::string const &str ) const;

   void parseAxiom ();
   void parseConstants ();
   void parseProductions ();

   Symbol symExpr ();
   SymbolWithoutParams symWoParamsExpr ();

   Tree * ruleExpr ();
   Tree * ruleSymExpr ();
   Tree * logicExpr ();
   Tree * cndExpr ();

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
   std::vector<Symbol> getAxiom () const;
   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> getTreeTable () const;
   std::vector<SymbolWithoutParams> getConstants () const; 
};
