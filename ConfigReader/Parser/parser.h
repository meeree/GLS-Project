#ifndef _PARSER__H_INCLUDED__
#define _PARSER__H_INCLUDED__

#include <map>
#include <vector>
#include <utility>
#include <string>
#include "../Symbol/symbol.h"
#include "../Compare/compare.h"

class Tree;
struct TreeTableCompare;
class Token;

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
   Parser () = default;
   Parser ( std::vector<Token> const &tokenString );
   ~Parser ();
   void mainParse ();
   std::vector<Symbol> getAxiom () const;
   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> getTreeTable () const;
   std::vector<SymbolWithoutParams> getConstants () const; 
};

#endif
