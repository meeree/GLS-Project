#ifndef TREE_H 
#define TREE_H 
#include "./ConfigReader/Tree/tree.h"
#endif 
#ifndef NODE_H
#define NODE_H
#include "./ConfigReader/Node/node.h"
#endif
#ifndef TOKEN_H
#define TOKEN_H
#include "./ConfigReader/Token/token.h"
#endif
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "./ConfigReader/Tokenizer/tokenizer.h"
#endif
#ifndef VALUE_H
#define VALUE_H
#include "./ConfigReader/Value/value.h"
#endif
#ifndef PARSER_H
#define PARSER_H
#include "./ConfigReader/Parser/parser.h"
#endif
#ifndef LSYSTEM_H
#define LSYSTEM_H
#include "./L-System/lSystem.h"
#endif

LSystem createLsys ( Parser const &p ) {
   std::vector<Symbol> axiom { p.getAxiom () };
   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> treeTable { p.getTreeTable () };
   std::vector<SymbolWithoutParams> constants { p.getConstants () }; 
   LSystem l { axiom, treeTable, constants };
   return l;
}

int main () {
   std::ifstream fl;
   fl.open ( "/home/jhazelden/GLS-Project/fl.txt" );
   Tokenizer t;
   t.tokenizeFile ( fl );
   Parser p { t.getTokenString () };
   p.mainParse ();
   LSystem l { createLsys ( p ) };   
   l.update (); 
//      l.printString ();
}
