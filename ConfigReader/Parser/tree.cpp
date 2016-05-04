#ifndef algorithm
#include <algorithm>
#endif
#ifndef NODE_H
#define NODE_H
#include "node.h"
#endif

Tree::Tree ( std::vector<Tree * > const &children, Node * const &root ) : mChildren { children }, mRoot { root } {
}
Tree::~Tree () { 
   delete mRoot;
   for ( auto const &iChild: mChildren ) {
      delete iChild;
   } 
}

WrapperTree::WrapperTree ( std::vector<Tree * > const &children, Node * const &root ) : Tree { children, root } {
}
Value * const WrapperTree::evalTree () const {
   std::vector<Value * > retVec { mChildren.size() };
   std::transform( mChildren.begin(), mChildren.end(), retVec.begin(), 
         [] ( Tree * const &iChild ) { return iChild->evalTree (); } );
   return mRoot->evalNode ( retVec );
}

ITETree::ITETree ( Tree * const &leftTree, Tree * const &middleTree, Tree* const &rightTree ) : Tree { {leftTree, middleTree, rightTree}, nullptr } {
}
Value * const ITETree::evalTree () const {
   Value * const leftEval { mChildren[0]->evalNode() };
   if ( leftEval->getBool() ) {
      return mChildren[1]->evalNode();
   } 
   return mChildren[2]->evalNode();
}

AndTree::AndTree ( Tree * const &leftTree, Tree * const &rightTree ) : Tree { {leftTree, rightTree}, new SimpleNode {} } {
}
Value * const AndTree::evalTree () const {
   Value * const leftEval { mChildren[0]->evalNode() };
   if ( leftEval->getBool() ) {
      return mChildren[1]->evalNode();
   } 
   return leftEval;
}
