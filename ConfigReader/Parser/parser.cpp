#ifndef vector 
#include <vector>
#endif
#ifndef PARSER_H
#define PARSER_H
#include "parser.h"
#endif
#ifndef TREE_H 
#define TREE_H 
#include "tree.h"
#endif 
#ifndef NODE_H
#define NODE_H
#include "node.h"
#endif
#ifndef TOKEN_H
#define TOKEN_H
#include "token.h"
#endif
#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif

bool TreeTableCompare::operator ()( std::pair<std::string, unsigned> const &key1, std::pair<std::string, unsigned> const &key2 ) const {
   std::string const &name1 { std::get<0>( key1 ) };
   std::string const &name2 { std::get<0>( key2 ) };
   unsigned const &paramSize1 { std::get<1>( key1 ) };
   unsigned const &paramSize2 { std::get<1>( key2 ) };

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

Tree * Parser::parseProduction ( std::vector<Token> &tokenString ) const {

   Node * nullNode { new ValueNode { nullptr } };
   Tree * nullTree { new WrapperTree { {}, nullNode } };

   std::vector<Token>::iterator iter = tokenString.begin ();

   std::string::iterator stringIt = ( *iter ).getString().begin();
   ++stringIt;
   

   Tree * &cndTree { andExpr ( ++iter ) };
   Tree * &ruleTree { stringExpr ( ++iter ) };

   Tree * topTree { new ITETree { cndTree, ruleTree, nullTree } };

   return topTree;

}

Tree * Parser::andExpr ( std::vector<Token>::iterator &iter ) const {
   if ( ( *( ++iter ) ).isString () && *( ( *iter ).getString () ) == " )" ) {
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
   std::string const &cnd { *( ( *( iter+1 ) ).getString () ) };
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
   std::string name { ( *iter )->getString () };
   Value nameValue { name };
   Node * nameNode { new ValueNode { nameValue } };
   Tree * nameTree { new WrapperTree { {}, nameNode } };

   std::vector<Tree *> children { nameTree };

   int paramSize {0};
   while ( ! ( *( ( ++iter ) )->isString () && *( iter )->getString () != ")" ) ) {
      children.push_back ( addExpr ( ++iter ) );
      ++paramSize;
   }

   for ( auto const &iSymPair: mSymbolMap ) {
      if ( iSymPair.first == name && iSymPair.second.size() == paramSize ) {
         for ( auto const paramName: &iSymPair.second ) {
            
         }
      }
   }
   
} 

Tree * Parser::addExpr ( std::vector<Token>::iterator &iter ) const {
   Tree * leftTree { mulExpr ( iter ) };
   if ( ( ( *( iter+1 ) ) ).isString () ) {
      std::string const &expr { *( ( *( iter+1 ) ).getString () ) };
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
      std::string const &expr { *( ( *( iter+1 ) ).getString () ) };
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
      std::string const &expr { *( ( *( iter+1 ) ).getString () ) };
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
   std::string const &expr { *( ( *iter ).getString () ) };
   if ( ( *iter ).isString () && expr == "(" ) {
      Tree * leftTree { addExpr ( ++iter ) };
      ++iter;
      return leftTree;
   }

   return staticNumExpr ( iter );
}

Tree * Parser::staticNumExpr ( std::vector<Token>::iterator &iter ) const {
   if ( ( *iter ).isInt () ) {
      Value topValue { *( ( *iter ).getInt () ) };
      Node * topNode { new ValueNode { topValue } };
      Tree * topTree { new WrapperTree { {}, topNode } };
      return topTree;
   } else if ( ( *iter ).isFloat () ) {
      Value topValue { *( ( *iter ).getFloat () ) };
      Node * topNode { new ValueNode { topValue } };
      Tree * topTree { new WrapperTree { {}, topNode } };
      return topTree;
   }

   return dynamicNumExpr ( iter );
}

Tree * Parser::dynamicNumExpr ( std::vector<Token>::iterator &iter ) const {
   Value paramValue { ( *iter )->getString () };
   Node * bottomNode { new ValueNode { paramValue } }; 
   Tree * bottomTree { new WrapperTree { {}, bottomNode } };

   std::vector<Tree*> children { bottomTree };
   Node * topNode { new ParamLookupNode {} };
   Tree * topTree { new WrapperTree { children, topNode } };

   return topTree;
}
