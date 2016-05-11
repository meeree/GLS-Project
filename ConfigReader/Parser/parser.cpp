#include <iostream>
#ifndef PARSER_H
#define PARSER_H
#include "parser.h"
#endif

#ifndef TREE_H 
#define TREE_H 
#include "../Tree/tree.h"
#endif 
#ifndef NODE_H
#define NODE_H
#include "../Node/node.h"
#endif
#ifndef TOKEN_H
#define TOKEN_H
#include "../Token/token.h"
#endif
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "../Tokenizer/tokenizer.h"
#endif
#ifndef VALUE_H
#define VALUE_H
#include "../Value/value.h"
#endif

bool TreeTableCompare::operator ()( SymbolWithoutParams const &sym1, SymbolWithoutParams const &sym2 ) const {
   std::string const &name1 { sym1.first };
   std::string const &name2 { sym2.first };
   std::vector<std::string> const &params1 { sym1.second };
   std::vector<std::string> const &params2 { sym2.second };

   if ( name1 == name2 && params1 == params2 ) {
      std::cout<<"function "+name1+" defined twice with same number of parameters "<<std::endl;
      exit ( EXIT_FAILURE );
   }

   return params1.size () < params2.size ();
}

Parser::Parser ( std::vector<Token> const &tokenString ) : mTokenString { tokenString }, mIter { mTokenString.begin () } {
}

Parser::~Parser () {
   for ( auto const &iPair: mTreeTable ) {
      delete iPair.second;
   }
}

bool Parser::strCheck ( std::string const &str ) const {
   if ( mIter == mTokenString.end () ) {
      std::cout<<"string check failed: hit end of tokenized file without finding string '" + str + "'"<<std::endl;
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
   ++mIter; auto iter2 = mIter; parseVariables ();
   mIter = iter2; parseProductions ();
}

void Parser::parseAxiom () {
   while ( !strCheck (";") ) {
      std::string name { ( *mIter ).getString () };
      std::map<std::string, double> params;

      do { 
         std::string paramName { ( *( ++mIter ) ).getString () };
         mIter += 2; Tree * paramArithVal { addExpr () };
         Symbol arbSym; // Arbitrary symbol to satisfy evalTree
         double paramVal { paramArithVal->evalTree ( arbSym ).getFloat () };
         params[paramName] = paramVal;
      } while ( strCheck ( ")" ) );

      Symbol sym { name, params };
      mAxiom.push_back ( sym );
   }
       
}

void Parser::parseConstants () {
}

void Parser::parseVariables () {
}

void Parser::parseProductions () {
}

//
//void Parser::parseSymbolTable ( std::vector<Token> &tokenString ) {
//   auto mIter = tokenString.begin (); 
//   while ( ! ( ( *mIter ).isString () && ( *mIter ).getString () == ";" ) ) {
//      std::string name { ( *mIter ).getString () };
//      std::vector<std::string> params;
//      while ( ! ( ( *( ++mIter ) ).isString () && ( *mIter ).getString () == " )" ) ) {
//         params.push_back ( ( *( ++mIter ) ).getString () );
//      }
//      SymbolWithoutParams sym { name, params };
//      mSymbolTable.push_back ( sym );
//   }
//}
//
//Tree * Parser::parseProduction ( std::vector<Token> &tokenString ) {
//
//   Node * nullNode { new ValueNode { nullptr } };
//   Tree * nullTree { new WrapperTree { {}, nullNode } };
//
//   auto mIter = tokenString.begin ();
//
//   Tree * cndTree { andExpr ( ++mIter ) };
//   Tree * ruleTree { stringExpr ( ++mIter ) };
//
//   Tree * topTree { new ITETree { cndTree, ruleTree, nullTree } };
//
//   return topTree;
//
//}
//
//Tree * Parser::andExpr () {
//   if ( ( *( ++mIter ) ).isString () && ( *mIter ).getString () == " )" ) {
//      Value trueValue { true };
//      Node * trueNode { new ValueNode { trueValue } };
//      Tree * trueTree { new WrapperTree { {}, trueNode } };
//      return trueTree;
//   } 
//
//   Tree * leftTree { cndExpr ( ++mIter ) };
//   Tree * rightTree { andExpr ( ++mIter ) };
//   Tree * topTree { new AndTree { leftTree, rightTree } };
//
//   return topTree;
//}
//
//Tree * Parser::cndExpr () {
//   Tree * leftTree { addExpr ( mIter ) };
//   std::string const &cnd { ( *( mIter+1 ) ).getString () };
//   if ( cnd == "<" ) {
//      std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//      Node * topNode { new LessNode {} };
//      Tree * topTree { new WrapperTree { children, topNode } };
//      return topTree;
//   } else if ( cnd == ">" ) {
//      std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//      Node * topNode { new GreaterNode {} };
//      Tree * topTree { new WrapperTree { children, topNode } };
//      return topTree;
//   } else if ( cnd == "<=" ) {
//      std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//      Node * topNode { new LessEqualNode {} };
//      Tree * topTree { new WrapperTree { children, topNode } };
//      return topTree;
//   } else if ( cnd == ">=" ) {
//      std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//      Node * topNode { new GreaterEqualNode {} };
//      Tree * topTree { new WrapperTree { children, topNode } };
//      return topTree;
//   } else if ( cnd == "==" ) {
//      std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//      Node * topNode { new EqualNode {} };
//      Tree * topTree { new WrapperTree { children, topNode } };
//      return topTree;
//   } else if ( cnd == "!=" ) {
//      std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//      Node * topNode { new NotEqualNode {} };
//      Tree * topTree { new WrapperTree { children, topNode } };
//      return topTree;
//   }
//}
//
//Tree * Parser::stringExpr () {
//   std::vector<Tree*> children;
//
//   while ( ! ( ( *mIter ).isString () && ( *mIter ).getString () == ";" ) ) {
//      std::string name { ( *mIter ).getString () };
//      Value const &nameValue { name };
//      Node * nameNode { new ValueNode { nameValue } };
//      Tree * nameTree { new WrapperTree { {}, nameNode } };
//      std::vector<Tree*> symChildren { nameTree };
//
//      int paramCount { 0 };
//      auto mIter2 = mIter;
//      while ( true ) {
//         ++paramCount;
//         while ( ! ( ( *( ++mIter2 ) ).isString () && ( *mIter2 ).getString () == "," ) ) {
//            if ( ( *( ++mIter2 ) ).isString () && ( *mIter2 ).getString () == " )" ) { 
//               break;
//            }
//            ++mIter2;
//         }
//      }
//
//      std::vector<std::string> params;
//      for ( auto const &sym: mSymbolTable ) {
//         if ( sym.first == name && sym.second.size () == paramCount ) {
//            params = sym.second;
//         }
//      }
//
//      if ( params.size () == 0 ) {
//         throw "Error in stringExpr function while parsing params";
//      }
//
//      auto paramIt = params.begin ();
//      while ( ! ( ( *( ++mIter ) ).isString () && ( *mIter ).getString () == " )" ) ) {
//         Value const &paramValue { * ( paramIt++ ) };
//         Node * paramNode { new ValueNode { paramValue } };
//         Tree * paramTree { new WrapperTree { {}, paramNode } };
//         symChildren.push_back ( paramTree );
//         symChildren.push_back ( addExpr ( ++mIter ) );
//      }
//
//      Node * symNode { new SymbolNode {} };
//      Tree * symTree { new WrapperTree { symChildren, symNode } };
//      children.push_back ( symTree );
//   }
//
//   Node * symStringNode { new AccumulateNode {} };
//   Tree * symStringTree { new WrapperTree { children, symStringNode } };
//   return symStringTree;
//}

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
   std::string const &expr {  };
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


int main () {
   std::ifstream fl;
   fl.open ( "/home/jhazelden/GLS-Project/ConfigReader/fl.txt" );
   Tokenizer t;
   t.tokenizeFile ( fl );
   Parser p { t.getTokenString () };
   p.mainParse ();
}
