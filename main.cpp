#include "./ConfigReader/Tree/tree.h"
#include "./ConfigReader/Node/node.h"
#include "./ConfigReader/Token/token.h"
#include "./ConfigReader/Tokenizer/tokenizer.h"
#include "./ConfigReader/Value/value.h"
#include "./ConfigReader/Parser/parser.h"
#include "./L-System/lSystem.h"

int main () {
   std::ifstream fl;
   fl.open ( "/home/jhazelden/GLS-Project/fl.txt" );
   Tokenizer t;
   t.tokenizeFile ( fl );

   Parser p { t.getTokenString () };
   p.mainParse ();

   std::vector<Symbol> axiom { p.getAxiom () };
   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> treeTable { p.getTreeTable () };
   std::vector<SymbolWithoutParams> constants { p.getConstants () }; 
   LSystem l { axiom, treeTable, constants };

   for ( int i = 0; i < 2; ++i ) {
      l.update (); 
      l.printString ();
   }
}
