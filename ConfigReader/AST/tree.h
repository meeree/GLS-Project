#ifndef vector
#include <vector>
#endif

class Symbol;
class Value;
class Node;

class Tree {
protected:
   std::vector<Tree*> mChildren;
   Node * mRoot;
   void sendContext ( Symbol * const &symbolContext, std::vector<Symbol*> &stringContext );

public:
   Tree ( std::vector<Tree*> const &children, Node * const &root );
   virtual ~Tree ();
   //GetContext is defined to be overloaded
   virtual void getContext ( Symbol * const &symbolContext, std::vector<Symbol*> &stringContext );
   virtual Value * const &evaluateTree () = 0;
};

class ContextTree : public Tree {
protected:
   Symbol * const &mSymbolContext;
   std::vector<Symbol*> &mStringContext;

   void getContext ( Symbol * const &symbolContext, std::vector<Symbol*> &stringContext );
   ContextTree ();
};

class GLSTreeWrapper {
private:
   Tree * mTop;
   Symbol * const symbolContext;
   std::vector<Symbol*> const stringContext;
   void firstPass ();

public:
   Value * const &evaluateTree ();
};

class SimpleTree : public Tree {
   Value * const &evaluateTree ();
};

class ITETree : public Tree {
   Value * const &evaluateTree ();
};

class ParamLookupTree : public ContextTree {
   Value * const &evaluateTree ();
};

class FillStringTree : public ContextTree {
   Value * const &evaluateTree ();
};
