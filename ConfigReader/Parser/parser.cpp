#ifndef vector 
#include <vector>
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
   std::string const &name1 { std::get<0>(key1) };
   std::string const &name2 { std::get<0>(key2) };
   unsigned const &paramSize1 { std::get<1>(key1) };
   unsigned const &paramSize2 { std::get<1>(key2) };

   if ( name1 == name2 && paramSize1 == paramSize2 ) {
      throw "function "+name1+" defined twice with same number of parameters ";
   }

   return paramSize1 < paramSize2;
}

Tree * Parser::parseProduction ( std::vector<Token*> const &tokenString ) const {

   Node * nullNode { new ValueNode { nullptr } };
   Tree * nullTree { new WrapperTree { {}, nullNode } };

   std::vector<Token*>::iterator iter { tokenString.begin () };

   //GET NAME
   ++iter;

   //ADD SIMPLENODE 
   Tree * &cndTree { andExpr ( iter ) };
   
   Node * ruleNode { new ValueNode { nullptr } };
   Tree * ruleTree { new parseRules ( iter ) };

   Tree * topTree { new ITETree { cndTree, ruleTree, nullTree } };

   return topTree;

}

Tree * Parser::andExpr ( std::vector<Token*>::iterator const &iter ) {
   if ( *iter->getOperator () == ')' ) {
      Node * trueNode { new ValueNode { true } };
      Tree * trueTree { new WrapperTree { {}, trueNode } };
      return trueTree;
   } 

   Tree * &leftTree { cndExpr ( ++iter ) };
   Tree * &rightTree { andExpr ( ++iter ) };
   Tree * topTree { new AndTree { leftTree, rightTree } };

   return topTree;
}

Tree * Parser::cndExpr ( std::vector<Token*>::iterator const &iter ) {
   Tree * &leftTree { addExpr ( iter ) };
   switch ( *(iter+1)->getCondition () ) {
      //ADD CONDITION TREES 
      case "<":
         std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
         Node * topNode { new LessNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      case ">":
         std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
         Node * topNode { new GreaterNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      case "<=":
         std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
         Node * topNode { new LessEqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      case ">=":
         std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
         Node * topNode { new GreaterEqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      case "=":
         std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
         Node * topNode { new EqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
      case "!=":
         std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
         Node * topNode { new NotEqualNode {} };
         Tree * topTree { new WrapperTree { children, topNode } };
         return topTree;
   }
}

Tree * Parser::addExpr ( std::vector<Token*>::iterator const &iter ) {
   Tree * &leftTree { mulExpr ( iter ) };
   if ( *(iter+1)->isOperator () ) {
      switch ( *(iter+1)->getOperator () ) {
         case '+': 
            std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
            Node * topNode { new PlusNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;

         case '-':
            std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
            Node * topNode { new MinusNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::mulExpr ( std::vector<Token*>::iterator const &iter ) {
   Tree * &leftTree { powExpr ( iter ) };
   if ( *(iter+1)->isOperator () ) {
      switch ( *(iter+1)->getOperator () ) {
         case '*': 
            std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
            Node * topNode { new MulNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;

         case '/':
            std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
            Node * topNode { new DivNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::powExpr ( std::vector<Token*>::iterator const &iter ) {
   Tree * &leftTree { brackExpr ( iter ) };
   if ( *(iter+1)->isOperator () ) {
      switch ( *(iter+1)->getOperator () ) {
         case '^': 
            std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
            Node * topNode { new PowNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;

         case '~':
            std::vector<Tree*> children { leftTree, addExpr ( ++(++iter) ) };
            Node * topNode { new PowRootNode {} };
            Tree * topTree { new WrapperTree { children, topNode } };
            return topTree;
      }
   }

   return leftTree;
}

Tree * Parser::brackExpr ( std::vector<Token*>::iterator const &iter ) {
   if ( *iter->getOperator () == '(' ) {
      Tree * &leftTree { addExpr ( ++iter ) };
      ++iter;
      return leftTree;
   }

   return staticNumExpr ( iter );
}

Tree * Parser::staticNumExpr ( std::vector<Token*>::iterator const &iter ) {
   if ( *iter->isInt () ) {
      Node * topNode { new IntNode { *iter } };
      Tree * topTree { new WrapperTree { {}, ValueNode } };
      return topTree;
   } else if ( *iter->isFloat () ) {
      Node * topNode { new FloatNode { *iter } };
      Tree * topTree { new WrapperTree { {}, ValueNode } };
      return topTree;
   }

   return dynamicNumExpr ( iter );
}

Tree * Parser::dynamicNumExpr ( std::vector<Token*>::iterator const &iter ) {
   // ADD CODE
}
