#ifndef TREE_H
#define TREE_H
#include "tree.h"
#endif 

// Func Tree Children:

class ITETree : public Tree {
private:
   Tree * const &mLeftTree;
   Tree * const &mMiddleTree;
   Tree * const &mRightTree;
public:
   ITETree ( Tree * const &leftTree, Tree * const &middleTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mMiddleTree { middleTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class AndTree : public Tree  {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   AndTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class OrTree : public Tree  {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   OrTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class SymbolTree : public Tree {
private:
   Tree * const &mNameTree;
   std::vector<Tree*> mParamChildren;
public:
   FillStringTree ( Tree * const &nameTree, std::vector<Tree*> const &paramChildren ) : mNameTree { nameTree }, mChildren { children } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

// Storage Func Tree Children:

class LookupTree : public StorageFuncTree {
private:
   Tree * const &mKeyTree;
public:
   LookupTree ( Tree * const &keyTree ) : mKeyTree { keyTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class FillStringTree : public StorageFuncTree {
private:
   std::vector<Tree*> mChildren;
public:
   FillStringTree ( std::vector<Tree*> const &children ) : mChildren { children }, StorageFuncTree { nullptr } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class GreaterThanTree : public StorageFuncTree {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   GreaterThanTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class GreaterThanEqualTree : public StorageFuncTree {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   GreaterThanEqualTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class LessThanTree : public StorageFuncTree {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   LessThanTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class LessThanEqualTree : public StorageFuncTree {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   LessThanEqualTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class EqualTree : public StorageFuncTree {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   EqualTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};

class NotEqualTree : public StorageFuncTree {
private:
   Tree * const &mLeftTree;
   Tree * const &mRightTree;
public:
   NotEqualTree ( Tree * const &leftTree, Tree * const &rightTree ) : mLeftTree { leftTree }, mRightTree { rightTree } {}
   Value * const &evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext );
};
