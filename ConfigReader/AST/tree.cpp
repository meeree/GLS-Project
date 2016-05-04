#ifndef TREE_H
#define TREE_H
#include "tree.h"
#endif
#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif
#ifndef SYMBOL_H
#define SYMBOL_H
#include "symbol.h"
#endif
#ifndef NODE_H
#define NODE_H
#include "node.h"
#ifndef algorithm
#include <algorithm>
#endif

//Main Tree Class 
Tree::Tree ( std::vector<Tree*> const &children, Node * const &root ) : mChildren { children }, mRoot { root } {
}

Tree::~Tree () { 
   std::for_each ( mChildren.begin(), mChildren.end(),
         [] ( Tree* const &iChild ) { delete iChild; } );
   delete mRoot;
}

void Tree::sendContext ( Symbol * const &symbolContext, std::vector<Symbol*> &stringContext ) {
   std::for_each ( mChildren.begin(), mChildren.end(),
         [] ( Tree* const &iChild ) { iChild->getContext ( symbolContext, stringContext ); } );
}

void Tree::getContext ( Symbol * const &symbolContext, std::vector<Symbol*> &stringContext ) {
   sendContext ( symbolContext, stringContext );
}


//Context Tree
void ContextTree::getContext ( Symbol * const &symbolContext, std::vector<Symbol*> &stringContext ) {
   mSymbolContext = symbolContext;
   mStringContext = stringContext;
}

ContextTree::ContextTree ( Node * const &root ) : Tree { {}, root } {
}


//Tree Wrapper 
void GLSTreeWrapper::firstPass () {
   mTop->getContext ( symbolContext, stringContext );
}

Value * const &GLSTreeWrapper::evaluateTree () {
   firstPass ();
   return mTop->evaluateTree();
}


//Simple Tree 
Value * const &SimpleTree::evaluateTree () {
   std::vector<Value* const &> evalChildren ( mChildren.size() );
   std::transform ( mChildren.begin(), mChildren.end(), evalChildren.begin(),
         [] ( Tree * const &iChild ) { return iChild->evaluateTree (); } );

   return mRoot->evaluateNode ( evalChildren );
}

//If Then Else Tree 
Value * const &ITETree::evaluateTree () {
   Value * const &evalLeft { mChildren[0]->evaluateTree () };
   switch ( static_cast<BoolValue*>(evalLeft) ) {
      case true: return mRoot->evaluateNode ( mChildren[1]->evaluateTree () );
      case false: return mRoot->evaluateNode ( mChildren[2]->evaluateTree () );
   }
}

//Param Lookup Tree
Value * const &ParamLookupTree::evaluateTree () {
   Value * const &evalBelow { mChildren[0]->evaluateTree () };
   
   return mRoot->evaluateNode ( static_cast<

Value * const &SimpleTree::evaluateTree () {
   return mRoot->evaluateNode (
Value * const &ITETree::evaluateTree ();
Value * const &ParamLookupTree::evaluateTree ();
Value * const &FillStringTreevaluateTree ();
