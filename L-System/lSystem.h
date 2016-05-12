#ifndef SYMBOL_H
#define SYMBOL_H
#include "../ConfigReader/Symbol/symbol.h"
#endif
#ifndef PARSER_H
#define PARSER_H
#include "../ConfigReader/Parser/parser.h"
#endif

#ifndef vector
#include <vector>
#endif

class LSystem {
private:
   std::vector<Symbol> mString1;
   std::vector<Symbol> mString2;

   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> mTreeTable;
   std::vector<SymbolWithoutParams> mConstants; 

   bool constFill ( Symbol const &sym, std::vector<Symbol> &str2 );
   bool variableFill ( Symbol const &sym, std::vector<Symbol> &str2 );
   void updateSpecific ( std::vector<Symbol> const &str1, std::vector<Symbol> &str2 );

public:  
   LSystem ( std::vector<Symbol> const &axiom, std::map<SymbolWithoutParams, Tree*, TreeTableCompare> const &treeTable, std::vector<SymbolWithoutParams> const &constants ); 
   void update ();
   void printString () const;
};
