class Memory {
   //HOLD TREE MEMORY
};

class Node {
protected:
   enum node_type_t {
      STATEMENT,
      VALUE
   };

   node_type_t mNodeType;
   Node ( node_type_t const &nodeType ) : mNodeType { nodeType } { }

public:
   bool isStatement ( ) const { return mNodeType == STATEMENT; } 
   bool isValue ( ) const { return mNodeType == VALUE; } 
};

// value node : node

class ValueNode : Node {
protected:
   union Storage {
      float * mFloat;
      int * mInt;
      Storage ( float * floatPtr ) : mFloat { floatPtr } { }
      Storage ( int * intPtr ) : mInt { intPtr } { }
   } mTypeStorage;
   
   enum value_type_t {
      FLOAT,
      INT
   };

   value_type_t mValueType;
   ValueNode ( value_type_t const &valueType, float * const &floatPtr ) : mValueType { valueType }, mTypeStorage ( floatPtr ), Node ( VALUE ) { } 
   ValueNode ( value_type_t const &valueType, int * const &intPtr ) : mValueType { valueType }, mTypeStorage ( intPtr ), Node ( VALUE ) { } 

public:
   bool isFloat ( ) const { return mValueType == FLOAT; }
   bool isInt ( ) const { return mValueType == INT; }
};

// instances
 
class IntNode : ValueNode {
private: 
   IntNode ( int * const &intPtr ) : ValueNode ( INT, intPtr ) { }
public:
   int * getValue ( ) const { return mTypeStorage.mInt; }
};

class FloatNode : ValueNode {
private: 
   FloatNode ( float * const &floatPtr ) : ValueNode ( FLOAT, floatPtr ) { }
public:
   float * getValue ( ) const { return mTypeStorage.mFloat; }
};

//

// statement node : node

class StatementNode : Node {
protected:
   enum return_type_t {
      VOID,

   };

   return_type_t mStatementType;
   StatementNode ( ) : Node ( STATEMENT ) { }
public:
         
};

// instances

class AssignmentNode : StatementNode {
};

class IfThenElseNode : StatementNode {
};

class ReturnNode : StatementNode {
};
 
// expression node : statement node

class ExpressionNode : StatementNode {
};

// instances
 
class ConditionNode : ExpressionNode {
};

class BinaryOperatorNode : ExpressionNode {
};

//

//
