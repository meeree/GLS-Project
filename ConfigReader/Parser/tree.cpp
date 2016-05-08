#ifndef TREE_H
#define TREE_H
#include "tree.h"
#endif
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
Value WrapperTree::evalTree () const {
   std::vector<Value > retVec ( mChildren.size () );
   std::transform ( mChildren.begin (), mChildren.end (), retVec.begin (), 
         [] ( Tree * const &iChild ) { return iChild->evalTree (); } );
   return mRoot->evalNode ( retVec );
}

ITETree::ITETree ( Tree * const &leftTree, Tree * const &middleTree, Tree* const &rightTree ) : Tree { { leftTree, middleTree, rightTree }, nullptr } {
}
Value ITETree::evalTree () const {
   Value leftEval { mChildren[0]->evalTree () };
   if ( leftEval.getBool () ) {
      return mChildren[1]->evalTree ();
   } 
   return mChildren[2]->evalTree ();
}

AndTree::AndTree ( Tree * const &leftTree, Tree * const &rightTree ) : Tree { { leftTree, rightTree }, new SimpleNode {} } {
}
Value AndTree::evalTree () const {
   Value leftEval { mChildren[0]->evalTree () };
   if ( leftEval.getBool () ) {
      return mChildren[1]->evalTree ();
   } 
   return leftEval;
}
