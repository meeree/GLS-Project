#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

//>>>>>>>>>> value type

class Value { 
private:
   enum value_t {
      INT,
      FLOAT
   };

   union {
      double mFloatData;
      int mIntData;
   } mData;

   value_t mType;

public:

   bool isFloat ( ) const { return mType == FLOAT; }
   void setFloat ( ) { mType = FLOAT; }
   void setFloatData ( double const &value) { assert( mType == FLOAT); mData.mFloatData = value; }
   double getFloatData ( ) const { assert( mType == FLOAT); return mData.mFloatData; }

   bool isInt ( ) const { return mType == INT; }
   void setInt ( ) { mType = INT; }
   void setIntData ( int const &value) { assert( mType == INT); mData.mIntData = value; }
   double getIntData ( ) const { assert( mType == INT); return mData.mIntData; }

};

//>>>>>>>>>> main node class 

class Node {
protected:
   enum node_type_t {
      FUNC_NODE,
      VALUE_NODE
   };

   node_type_t mNodeType;

   Node ( node_type_t nodeType) :
      mNodeType { nodeType}
   { }

public:
   bool isFuncNode ( ) { return mNodeType == FUNC_NODE; }
   bool isValueNode ( ) { return mNodeType == VALUE_NODE; }

};

//>>>>>>>>>> value node implementation

class ValueNode : public Node {
private:
   Value mData;

public:
   ValueNode ( Value const &data) :
      mData { data},
      Node ( VALUE_NODE)
   { }

   Value getData ( ) {
      return mData;
   }

};

//>>>>>>>>>> function node implementation

class FuncNode : public Node {
public:
   FuncNode ( ) :
      Node ( FUNC_NODE)
   { }

   virtual Value apply ( std::vector<Value> const &belowData) = 0;

};

//>>>>>>>>>> Tree implementation

class Tree {
private:
   Node* mRoot;
   std::vector<Tree*> mChildren;
public:
   Tree ( Node * const &root) :
      mRoot { root}
   { }

   Tree ( Node * const &root, std::vector<Tree*> const &children) :
      mRoot { root},
      mChildren { children}
   { }

   Value evaluate ( ) {
      if ( mRoot->isValueNode( )) { 
         return static_cast<ValueNode*>( mRoot)->getData( );
      }

      if ( mRoot->isFuncNode( )) {
         std::vector<Value> belowData ( mChildren.size( ));
         std::transform( mChildren.begin( ), mChildren.end( ), belowData.begin( ), 
               [] ( Tree* const &iTree) { return iTree->evaluate( ); });

         return static_cast<FuncNode*>( mRoot)->apply( belowData);
       }
   }

};
