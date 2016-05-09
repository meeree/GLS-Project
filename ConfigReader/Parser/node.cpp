#ifndef NODE_H
#define NODE_H
#include "node.h"
#endif
#ifndef cmath
#include <cmath>
#endif

Node::Node () {
}
Node::~Node () {
}

ValueNode::ValueNode ( Value const &valuePtr ) : mValue { valuePtr } {
}
Value ValueNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const {
   return mValue;
}

Value SimpleNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   return inVec[0];
}

Value LookupNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   std::string const &paramName { inVec[0]->getString () };
   return mem.lookupParam ( paramName );
} 

bool ArithNode::intCheck ( std::vector<Value> const &inVec ) const {
   for ( auto const &iVal: inVec ) {
      if ( !iVal.isInt () ) {
         return false;
      }
   }
   return true;
}
Value PlusNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   if ( intCheck ( inVec ) ) {
      return *( inVec[0].getInt () ) + *( inVec[1].getInt () );
   }
   return *( inVec[0].getFloat () ) + *( inVec[1].getFloat () );
}
Value MinusNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   if ( intCheck ( inVec ) ) {
      return *( inVec[0].getInt () ) - *( inVec[1].getInt () );
   }
   return *( inVec[0].getFloat () ) - *( inVec[1].getFloat () );
}
Value MulNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   if ( intCheck ( inVec ) ) {
      return *( inVec[0].getInt () ) * *( inVec[1].getInt () );
   }
   return *( inVec[0].getFloat () ) * *( inVec[1].getFloat () );
}
Value DivNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   if ( intCheck ( inVec ) ) {
      return *( inVec[0].getInt () ) / *( inVec[1].getInt () );
   }
   return *( inVec[0].getFloat () ) / *( inVec[1].getFloat () );
}
Value PowNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   if ( intCheck ( inVec ) ) {
      return pow ( *( inVec[0].getInt () ), *( inVec[1].getInt () ) );
   }
   return pow ( *( inVec[0].getFloat () ), *( inVec[1].getFloat () ) );
}
Value PowRootNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const { 
   if ( intCheck ( inVec ) ) {
      return pow ( *( inVec[0].getInt () ), 1.0/ *( inVec[1].getInt () ) );
   }
   return pow ( *( inVec[0].getFloat () ), 1.0/ *( inVec[1].getFloat () ) );
}

Value LessNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const {
   Value newValue { *( inVec[0].getFloat () ) < *( inVec[1].getFloat () ) }; 
   return newValue;
}
Value GreaterNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const {
   Value newValue { *( inVec[0].getFloat () ) > *( inVec[1].getFloat () ) }; 
   return newValue;
}
Value LessEqualNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const {
   Value newValue { *( inVec[0].getFloat () ) <= *( inVec[1].getFloat () ) }; 
   return newValue;
}
Value GreaterEqualNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const {
   Value newValue { *( inVec[0].getFloat () ) >= *( inVec[1].getFloat () ) }; 
   return newValue;
}
Value EqualNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const {
   Value newValue { *( inVec[0].getFloat () ) == *( inVec[1].getFloat () ) }; 
   return newValue;
}
Value NotEqualNode::evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const {
   Value newValue { *( inVec[0].getFloat () ) != *( inVec[1].getFloat () ) }; 
   return newValue;
}
