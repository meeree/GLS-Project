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
#ifndef VALUE_H
#define VALUE_H
#include "../Value/value.h"
#endif
#ifndef SYMBOL_H
#define SYMBOL_H
#include "../Symbol/symbol.h"
#endif

bool TreeTableCompare::operator ()( std::pair<std::string, unsigned> const &key1, std::pair<std::string, unsigned> const &key2 ) const {
   std::string const &name1 { key1.first };
   std::string const &name2 { key2.first };
   unsigned const &paramSize1 { key1.second };
   unsigned const &paramSize2 { key2.second };

   if ( name1 == name2 && paramSize1 == paramSize2 ) {
      throw "function "+name1+" defined twice with same number of parameters ";
   }

   return paramSize1 < paramSize2;
}

Parser::~Parser () {
   for ( auto const &iPair: mTreeTable ) {
      delete iPair.second;
   }
}

void Parser::parseSymbolTable ( std::vector<Token> &tokenString ) {
   auto iter = tokenString.begin(); 
   while ( ! ( ( *iter ).isString () && ( *iter ).getString () == ";" ) ) {
      std::string name { ( *iter ).getString () };
      std::vector<std::string> params;
      while ( ! ( ( *( ++iter ) ).isString () && ( *iter ).getString () == ")" ) ) {
         params.push_back ( ( *( ++iter ) ).getString () );
      }
      std::pair<std::string, std::vector<std::string> > sym { name, params };
      mSymbolTable.push_back ( sym );
   }
}

Tree * Parser::parseProduction ( std::vector<Token> &tokenString ) {

   Node * nullNode { new ValueNode { nullptr } };
   Tree * nullTree { new WrapperTree { {}, nullNode } };

   auto iter = tokenString.begin ();

   Tree * cndTree { andExpr ( ++iter ) };
   Tree * ruleTree { stringExpr ( ++iter ) };

   Tree * topTree { new ITETree { cndTree, ruleTree, nullTree } };

   return topTree;

}

Tree * Parser::andExpr ( std::vector<Token>::iterator &iter ) const {
   if ( ( *( ++iter ) ).isString () && ( *iter ).getString () == " )" ) {
      Value trueValue { true };
      Node * trueNode { new ValueNode { trueValue } };
      Tree * trueTree { new WrapperTree { {}, trueNode } };
      return trueTree;
   } 

   Tree * leftTree { cndExpr ( ++iter ) };
   Tree * rightTree { andExpr ( ++iter ) };
   Tree * topTree { new AndTree { leftTree, rightTree } };

   return topTree;
}

Tree * Parser::cndExpr ( std::vector<Token>::iterator &iter ) const {
   Tree * leftTree { addExpr ( iter ) };
   std::string const &cnd { ( *( iter+1 ) ).getString () };
   if ( cnd == "<" ) {
      std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
      Node * topNode { new LessNode {} };
      Tree * topTree { new WrapperTree { children, topNode } };
      return topTree;
   } else if ( cnd == ">" ) {
      std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
      Node * topNode { new GreaterNode {} };
      Tree * topTree { new WrapperTree { children, topNode } };
      return topTree;
   } else if ( cnd == "<=" ) {
      std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
      Node * topNode { new LessEqualNode {} };
      Tree * topTree { new WrapperTree { children, topNode } };
      return topTree;
   } else if ( cnd == ">=" ) {
      std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
      Node * topNode { new GreaterEqualNode {} };
      Tree * topTree { new WrapperTree { children, topNode } };
      return topTree;
   } else if ( cnd == "==" ) {
      std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
      Node * topNode { new EqualNode {} };
      Tree * topTree { new WrapperTree { children, topNode } };
      return topTree;
   } else if ( cnd == "!=" ) {
      std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
      Node * topNode { new NotEqualNode {} };
      Tree * topTree { new WrapperTree { children, topNode } };
      return topTree;
   }
}

Tree * Parser::stringExpr ( std::vector<Token>::iterator &iter ) const {
   std::vector<Tree*> children;

   while ( ! ( ( *iter ).isString () && ( *iter ).getString () == ";" ) ) {
      std::string name { ( *iter ).getString () };
      Value const &nameValue { name };
      Node * nameNode { new ValueNode { nameValue } };
      Tree * nameTree { new WrapperTree { {}, nameNode } };
      std::vector<Tree*> symChildren { nameTree };

      int paramCount { 0 };
      auto iter2 = iter;
      while ( true ) {
         ++paramCount;
         while ( ! ( ( *( ++iter2 ) ).isString () && ( *iter2 ).getString () == "," ) ) {
            if ( ( *( ++iter2 ) ).isString () && ( *iter2 ).getString () == ")" ) { 
               break;
            }
            ++iter2;
         }
      }

      std::vector<std::string> params;
      for ( auto const &sym: mSymbolTable ) {
         if ( sym.first == name && sym.second.size() == paramCount ) {
            params = sym.second;
         }
      }

      if ( params.size() == 0 ) {
         throw "Error in stringExpr function while parsing params";
      }

      auto paramIt = params.begin();
      while ( ! ( ( *( ++iter ) ).isString () && ( *iter ).getString () == ")" ) ) {
         Value const &paramValue { * ( paramIt++ ) };
         Node * paramNode { new ValueNode { paramValue } };
         Tree * paramTree { new WrapperTree { {}, paramNode } };
         symChildren.push_back ( paramTree );
         symChildren.push_back ( addExpr ( ++iter ) );
      }

      Node * symNode { new SymbolNode {} };
      Tree * symTree { new WrapperTree { symChildren, symNode } };
      children.push_back ( symTree );
   }

   Node * symStringNode { new AccumulateNode {} };
   Tree * symStringTree { new WrapperTree { children, symStringNode } };
   return symStringTree;
}

Tree * Parser::addExpr ( std::vector<Token>::iterator &iter ) const {
   Tree * leftTree { mulExpr ( iter ) };
   if ( ( ( *( iter+1 ) ) ).isString () ) {
      std::string const &expr { ( *( iter+1 ) ).getString () };
      if ( expr == "+" ) {
            std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
            Node * topNode { new PlusNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;
      } else if ( expr == "-" ) {
            std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
            Node * topNode { new MinusNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::mulExpr ( std::vector<Token>::iterator &iter ) const {
   Tree * leftTree { powExpr ( iter ) };
   if ( ( ( *( iter+1 ) ) ).isString () ) {
      std::string const &expr { ( *( iter+1 ) ).getString () };
      if ( expr == "*" ) {
         std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
         Node * topNode { new MulNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      } else if ( expr == "/" ) {
         std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
         Node * topNode { new DivNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::powExpr ( std::vector<Token>::iterator &iter ) const {
   Tree * leftTree { brackExpr ( iter ) };
   if ( ( ( *( iter+1 ) ) ).isString () ) {
      std::string const &expr { ( *( iter+1 ) ).getString () };
      if ( expr == "^" ) {
            std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
            Node * topNode { new PowNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;
      } else if ( expr == "~" ) {
            std::vector<Tree*> children { leftTree, addExpr ( ++( ++iter ) ) };
            Node * topNode { new PowRootNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::brackExpr ( std::vector<Token>::iterator &iter ) const {
   std::string const &expr {  };
   if ( ( *iter ).isString () && ( *iter ).getString () == "(" ) {
      Tree * leftTree { addExpr ( ++iter ) };
      ++iter;
      return leftTree;
   }

   return staticNumExpr ( iter );
}

Tree * Parser::staticNumExpr ( std::vector<Token>::iterator &iter ) const {
   if ( ( *iter ).isInt () ) {
      Value topValue { ( *iter ).getInt () };
      Node * topNode { new ValueNode { topValue } };
      Tree * topTree { new WrapperTree { {}, topNode } };
      return topTree;
   } else if ( ( *iter ).isFloat () ) {
      Value topValue { ( *iter ).getFloat () };
      Node * topNode { new ValueNode { topValue } };
      Tree * topTree { new WrapperTree { {}, topNode } };
      return topTree;
   }

   return dynamicNumExpr ( iter );
}

Tree * Parser::dynamicNumExpr ( std::vector<Token>::iterator &iter ) const {
   Value paramValue { ( *iter ).getString () };
   Node * bottomNode { new ValueNode { paramValue } }; 
   Tree * bottomTree { new WrapperTree { {}, bottomNode } };

   std::vector<Tree*> children { bottomTree };
   Node * topNode { new LookupNode {} };
   Tree * topTree { new WrapperTree { children, topNode } };

   return topTree;
}

int main () {
   Token a { "(" };
   Token b { 5. };
   Token c { "~" };
   Token d { 6. };
   Token e { ")" };
   Token f { "^" };
   Token g { 3. };
   Symbol sym;
   std::vector<Token> tokenString {a, b, c, d, e, f, g};
   auto iter = tokenString.begin();
   Parser p;
   Tree * tr { p.addExpr ( iter ) };
}
