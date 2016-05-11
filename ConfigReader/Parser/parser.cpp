#include <iostream>
#ifndef PARSER_H
#define PARSER_H
#include "parser.h"
#endif
#ifndef vector 
#include <vector>
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
#ifndef SYMBOL_H
#define SYMBOL_H
#include "../Symbol/symbol.h"
#endif

bool TreeTableCompare::operator ()( std::pair<std::string, std::vector<std::string> > const &sym1, std::pair<std::string, std::vector<std::string> > const &sym2 ) const {
   std::string const &name1 { sym1.first };
   std::string const &name2 { sym2.first };
   std::vector<std::string> const &params1 { sym1.second };
   std::vector<std::string> const &params2 { sym2.second };

   if ( name1 == name2 && params1 == params2 ) {
      throw "function "+name1+" defined twice with same number of parameters ";
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
   std::cout<<(*mIter).getString ()<<std::endl;
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
//      std::pair<std::string, std::vector<std::string> > sym { name, params };
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
//Tree * Parser::andExpr () const {
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
//Tree * Parser::cndExpr () const {
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
//Tree * Parser::stringExpr () const {
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
//
//Tree * Parser::addExpr () const {
//   Tree * leftTree { mulExpr ( mIter ) };
//   if ( ( ( *( mIter+1 ) ) ).isString () ) {
//      std::string const &expr { ( *( mIter+1 ) ).getString () };
//      if ( expr == "+" ) {
//            std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//            Node * topNode { new PlusNode {} };
//            Tree * topTree { new WrapperTree { children, topNode } };
//            return topTree;
//      } else if ( expr == "-" ) {
//            std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//            Node * topNode { new MinusNode {} };
//            Tree * topTree { new WrapperTree { children, topNode } };
//            return topTree;
//      }
//   }
//
//   return leftTree;
//}
//
//Tree * Parser::mulExpr () const {
//   Tree * leftTree { powExpr ( mIter ) };
//   if ( ( ( *( mIter+1 ) ) ).isString () ) {
//      std::string const &expr { ( *( mIter+1 ) ).getString () };
//      if ( expr == "*" ) {
//         std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//         Node * topNode { new MulNode {} };
//         Tree * topTree { new WrapperTree { children, topNode } };
//         return topTree;
//      } else if ( expr == "/" ) {
//         std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//         Node * topNode { new DivNode {} };
//         Tree * topTree { new WrapperTree { children, topNode } };
//         return topTree;
//      }
//   }
//
//   return leftTree;
//}
//
//Tree * Parser::powExpr () const {
//   Tree * leftTree { brackExpr ( mIter ) };
//   if ( ( ( *( mIter+1 ) ) ).isString () ) {
//      std::string const &expr { ( *( mIter+1 ) ).getString () };
//      if ( expr == "^" ) {
//            std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//            Node * topNode { new PowNode {} };
//            Tree * topTree { new WrapperTree { children, topNode } };
//            return topTree;
//      } else if ( expr == "~" ) {
//            std::vector<Tree*> children { leftTree, addExpr ( ++( ++mIter ) ) };
//            Node * topNode { new PowRootNode {} };
//            Tree * topTree { new WrapperTree { children, topNode } };
//            return topTree;
//      }
//   }
//
//   return leftTree;
//}
//
//Tree * Parser::brackExpr () const {
//   std::string const &expr {  };
//   if ( ( *mIter ).isString () && ( *mIter ).getString () == "(" ) {
//      Tree * leftTree { addExpr ( ++mIter ) };
//      ++mIter;
//      return leftTree;
//   }
//
//   return staticNumExpr ( mIter );
//}
//
//Tree * Parser::staticNumExpr () const {
//   if ( ( *mIter ).isInt () ) {
//      Value topValue { ( *mIter ).getInt () };
//      Node * topNode { new ValueNode { topValue } };
//      Tree * topTree { new WrapperTree { {}, topNode } };
//      return topTree;
//   } else if ( ( *mIter ).isFloat () ) {
//      Value topValue { ( *mIter ).getFloat () };
//      Node * topNode { new ValueNode { topValue } };
//      Tree * topTree { new WrapperTree { {}, topNode } };
//      return topTree;
//   }
//
//   return dynamicNumExpr ( mIter );
//}
//
//Tree * Parser::dynamicNumExpr () const {
//   Value paramValue { ( *mIter ).getString () };
//   Node * bottomNode { new ValueNode { paramValue } }; 
//   Tree * bottomTree { new WrapperTree { {}, bottomNode } };
//
//   std::vector<Tree*> children { bottomTree };
//   Node * topNode { new LookupNode {} };
//   Tree * topTree { new WrapperTree { children, topNode } };
//
//   return topTree;
//}
//

int main () {
   Tokenizer t;
   std::ifstream fl;
   fl.open ( "../Tokenizer/fl.txt" );
   Tokenizer t;
   t.tokenizeFile ( fl );
}
