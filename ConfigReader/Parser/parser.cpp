#include "parser.h"
#include "../Tree/tree.h"
#include "../Compare/compare.h"
#include "../Node/node.h"
#include "../Token/token.h"
#include "../Tokenizer/tokenizer.h"
#include "../Value/value.h"
#include <iostream>

std::map<std::string, unsigned> Parser::cndTable { 
   std::make_pair ( "<", 0 ), 
   std::make_pair ( ">", 1 ), 
   std::make_pair ( "<=", 2 ), 
   std::make_pair ( ">=", 3 ), 
   std::make_pair ( "==", 4 ), 
   std::make_pair ( "!=", 5 )
};

Parser::Parser ( std::vector<Token> const &tokenString ) : mTokenString { tokenString }, mIter { mTokenString.begin () } {
}

Parser::~Parser () {
   for ( auto const &iPair: mTreeTable ) {
      delete iPair.second;
   }
}

bool Parser::strCheck ( std::string const &str ) const {
   if ( mIter == mTokenString.end () ) {
      std::cerr<<"string check failed: hit end of tokenized file without finding string '" + str + "'"<<std::endl;
      exit ( EXIT_FAILURE );
   }

   return ( ( *mIter ).isString () && ( *mIter ).getString () == str );
}

void Parser::mainParse () { 
   while ( !strCheck ( "AXIOM" ) ) { ++mIter; }
   ++mIter; parseAxiom (); mIter = mTokenString.begin ();

   while ( !strCheck ( "CONSTANTS" ) ) { ++mIter; }
   ++mIter; parseConstants (); mIter = mTokenString.begin ();

   while ( !strCheck ( "PRODUCTIONS" ) ) { ++mIter; }
   ++mIter; parseProductions (); mIter = mTokenString.begin ();
//
//   while ( !strCheck ( "GRAPHICS" ) ) { ++mIter; }
//   ++mIter; parseGraphics ();
}

void Parser::parseAxiom () {
   while ( !strCheck (";") ) {
      Symbol sym { symExpr () };
      mAxiom.push_back ( sym );
      ++mIter;
   }
}

void Parser::parseConstants () {
   while ( !strCheck (";") ) {
      if ( strCheck (",") ) {
         ++mIter;
      }

      SymbolWithoutParams symW { symWoParamsExpr () };
      mConstants.push_back ( symW );
      ++mIter;
   }
}

Symbol Parser::symExpr () {
   std::string name { ( *( mIter++ ) ).getString () };
   std::map<std::string, double> params; ++mIter;

   while ( !strCheck ( ")" ) ) {
      std::string paramName { ( *mIter ).getString () };
      mIter += 2; 
      Tree * paramArithTree { addExpr () };
      Symbol arbSym; // Arbitrary symbol to satisfy evalTree
      double paramEval { paramArithTree->evalTree ( arbSym ).getFloat () };
      params[paramName] = paramEval; ++mIter;
      if ( strCheck ( "," ) ) {
         ++mIter;
      }
   }

   Symbol sym { name, params }; 
   return sym;
}

SymbolWithoutParams Parser::symWoParamsExpr () {
   std::string name { ( *( mIter++ ) ).getString () };
   std::vector<std::string> paramNames; ++mIter;

   while ( !strCheck ( ")" ) ) {
      std::string paramName { ( *mIter ).getString () };
      paramNames.push_back ( paramName ); ++mIter;

      if ( strCheck ( "," ) ) {
         ++mIter;
      }
   }

   SymbolWithoutParams symW { name, paramNames };
   return symW;
}

Tree * Parser::ruleSymExpr () {
   std::vector<Tree*> children;

   Value nameVal { ( *( mIter++ ) ).getString () };
   Node * nameNode { new ValueNode { nameVal } };
   Tree * nameTree { new WrapperTree { {}, nameNode } };
   children.push_back ( nameTree ); ++mIter;

   while ( !strCheck ( ")" ) ) {
      Value paramNameVal { ( *mIter ).getString () };
      Node * paramNameNode { new ValueNode { paramNameVal } };
      Tree * paramNameTree { new WrapperTree { {}, paramNameNode } };

      children.push_back ( paramNameTree );
      mIter += 2; 
      children.push_back ( addExpr () ); 
      ++mIter;

      if ( strCheck ( "," ) ) {
         ++mIter;
      }
   }

   Node * symNode { new SymbolNode {} };
   Tree * symTree { new WrapperTree { children, symNode } };
   Symbol sym;

   return symTree;
}

Tree * Parser::ruleExpr () {
   std::vector<Tree*> children {};
   
   mIter += 2;
   while ( !strCheck ( ";" ) ) {
      Tree * ruleSymTree { ruleSymExpr () }; 
      children.push_back ( ruleSymTree ); 
      ++mIter; 
   }


   Node * symStrNode { new AccumulateNode {} };
   Tree * symStrTree { new WrapperTree { children, symStrNode } };
   
   return symStrTree;
}

void Parser::parseProductions () {
   while ( !strCheck ( "END" ) ) {
      std::vector<Symbol> noRet {};
      Node * nullNode { new ValueNode { noRet } };
      Tree * nullTree { new WrapperTree { {}, nullNode } };

      SymbolWithoutParams symW { symWoParamsExpr () };

      ++mIter; Tree * cndTree { logicExpr () };
      Tree * ruleTree { ruleExpr () };
      Tree * prdTree { new ITETree { cndTree, ruleTree, nullTree } };
      mTreeTable[symW] = prdTree; ++mIter;
   }
}

//void Parser::parseGraphics () {
//   while ( !strCheck ( "END" ) ) {
//      std::string name { ( *( mIter++ ) ).getString () };
//      
//   }
//}


Tree * Parser::logicExpr () {
   ++mIter; Tree * leftTree { cndExpr () }; ++mIter;

   if ( strCheck ( "&" ) ) {
      Tree * rightTree { logicExpr () };
      Tree * topTree { new AndTree { leftTree, rightTree } };
      return topTree;
   } else if ( strCheck ( "|" ) ) {
      Tree * rightTree { logicExpr () };
      Tree * topTree { new OrTree { leftTree, rightTree } };
      return topTree;
   } else if ( strCheck ( ")" ) ) {
      return leftTree;
   } else {
      std::cerr<<"logic parse failed: undefined logical connective between conditions:, try using & or |"<<std::endl;
      exit ( EXIT_FAILURE );
   }
}

Tree * Parser::cndExpr () {
   Tree * leftTree { addExpr () };
   std::string cnd { ( *( ++mIter ) ).getString () };

   ++mIter; std::vector<Tree*> children { leftTree, addExpr () };

   switch ( cndTable.at ( cnd ) ) {
      case 0: {
         Node * topNode { new LessNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
      case 1: {
         Node * topNode { new GreaterNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
      case 2: {
         Node * topNode { new LessEqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
      case 3: {
         Node * topNode { new GreaterEqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
      case 4: {
         Node * topNode { new EqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }  
      case 5: {
         Node * topNode { new NotEqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
      default: {
         std::cerr<<"conditon parse failed: boolean connective undefined, try using < or > or <= or >= or == or !="<<std::endl; 
         exit ( EXIT_FAILURE );
      }
   }
}

Tree * Parser::addExpr () {
   Tree * leftTree { mulExpr () };
   if ( ( *( mIter+1 ) ).isString () ) {
      std::string const &expr { ( *( mIter+1 ) ).getString () };
      if ( expr == "+" ) {
         mIter += 2; std::vector<Tree*> children { leftTree, addExpr () };
         Node * topNode { new PlusNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      } else if ( expr == "-" ) {
         mIter += 2; std::vector<Tree*> children { leftTree, addExpr () };
         Node * topNode { new MinusNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::mulExpr () {
   Tree * leftTree { powExpr () };
   if ( ( *( mIter+1 ) ).isString () ) {
      std::string const &expr { ( *( mIter+1 ) ).getString () };
      if ( expr == "*" ) {
         mIter += 2; std::vector<Tree*> children { leftTree, addExpr () };
         Node * topNode { new MulNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      } else if ( expr == "/" ) {
         mIter += 2; std::vector<Tree*> children { leftTree, addExpr () };
         Node * topNode { new DivNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::powExpr () {
   Tree * leftTree { brackExpr () };
   if ( ( *( mIter+1 ) ).isString () ) {
      std::string const &expr { ( *( mIter+1 ) ).getString () };
      if ( expr == "^" ) {
         mIter += 2; std::vector<Tree*> children { leftTree, addExpr () };
         Node * topNode { new PowNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      } else if ( expr == "~" ) {
         mIter += 2; std::vector<Tree*> children { leftTree, addExpr () };
         Node * topNode { new PowRootNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::brackExpr () {
   if ( strCheck ( "(" ) ) {
      ++mIter; Tree * leftTree { addExpr () }; ++mIter;
      return leftTree;
   }

   return staticNumExpr ();
}

Tree * Parser::staticNumExpr () {
   if ( ( *mIter ).isInt () ) {
      Value topValue { ( *mIter ).getInt () };
      Node * topNode { new ValueNode { topValue } };
      Tree * topTree { new WrapperTree { {}, topNode } };
      return topTree;
   } else if ( ( *mIter ).isFloat () ) {
      Value topValue { ( *mIter ).getFloat () };
      Node * topNode { new ValueNode { topValue } };
      Tree * topTree { new WrapperTree { {}, topNode } };
      return topTree;
   }

   return dynamicNumExpr ();
}

Tree * Parser::dynamicNumExpr () {
   Value paramValue { ( *mIter ).getString () };
   Node * bottomNode { new ValueNode { paramValue } }; 
   Tree * bottomTree { new WrapperTree { {}, bottomNode } };

   std::vector<Tree*> children { bottomTree };
   Node * topNode { new LookupNode {} };
   Tree * topTree { new WrapperTree { children, topNode } };

   return topTree;
}

std::vector<Symbol> Parser::getAxiom () const {
   return mAxiom;
}
std::map<SymbolWithoutParams, Tree*, TreeTableCompare> Parser::getTreeTable () const {
   return mTreeTable;
}
std::vector<SymbolWithoutParams> Parser::getConstants () const {
   return mConstants;
}
