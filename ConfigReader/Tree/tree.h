#ifndef vector 
#include <vector>
#endif

class Node;
class Value;
class Symbol;

class Tree {
protected:
   std::vector<Tree * > mChildren;
   Node * mRoot;
   Tree ( std::vector<Tree * > const &children, Node * const &root );
public:
   virtual Value evalTree ( Symbol const &sym ) const = 0;
   virtual ~Tree ();
};

class WrapperTree : public Tree {
public:
   WrapperTree ( std::vector<Tree * > const &children, Node * const &root );
   Value evalTree ( Symbol const &sym ) const;
};

class ITETree : public Tree {
public:
   ITETree ( Tree * const &leftTree, Tree * const &middleTree, Tree* const &rightTree );
   Value evalTree ( Symbol const &sym ) const;
};

class AndTree : public Tree {
public:
   AndTree ( Tree * const &leftTree, Tree * const &rightTree );
   Value evalTree ( Symbol const &sym ) const;
};