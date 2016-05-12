#include "tree.h"
#include "../Node/node.h"
#include <algorithm>

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
Value WrapperTree::evalTree ( Symbol const &sym ) const {
   std::vector<Value > retVec ( mChildren.size () );
   std::transform ( mChildren.begin (), mChildren.end (), retVec.begin (), 
         [&] ( Tree * const &iChild ) { return iChild->evalTree ( sym ); } );
   return mRoot->evalNode ( retVec, sym );
}

ITETree::ITETree ( Tree * const &leftTree, Tree * const &middleTree, Tree* const &rightTree ) : Tree { { leftTree, middleTree, rightTree }, nullptr } {
}
Value ITETree::evalTree ( Symbol const &sym ) const {
   Value leftEval { mChildren[0]->evalTree ( sym ) };
   if ( leftEval.getBool () ) {
      return mChildren[1]->evalTree ( sym );
   } 
   return mChildren[2]->evalTree ( sym );
}

AndTree::AndTree ( Tree * const &leftTree, Tree * const &rightTree ) : Tree { { leftTree, rightTree }, new SimpleNode {} } {
}
Value AndTree::evalTree ( Symbol const &sym ) const {
   Value leftEval { mChildren[0]->evalTree ( sym ) };
   if ( leftEval.getBool () ) {
      return mChildren[1]->evalTree ( sym );
   } 
   return leftEval;
}

OrTree::OrTree ( Tree * const &leftTree, Tree * const &rightTree ) : Tree { { leftTree, rightTree }, new SimpleNode {} } {
}
Value OrTree::OrTree::evalTree ( Symbol const &sym ) const {
   Value leftEval { mChildren[0]->evalTree ( sym ) };
   if ( leftEval.getBool () ) {
      return leftEval;
   } 
   return mChildren[1]->evalTree ( sym );
}
