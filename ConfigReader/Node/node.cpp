#include "node.h"
#include "../Symbol/symbol.h"
#include <cmath>
#include <algorithm>

//CONSTRUCTORS 

SaveNode::SaveNode ( Value const &val ) : mValue { val } {
}
SaveNode::SaveNode ( Value::value_type_t const &valueType ) : mValue { valueType } {
}

ValueNode::ValueNode ( Value const &val ) : SaveNode { val } {
}

LookupNode::LookupNode () : SaveNode { Value::value_type_t::FLOAT } {
}

ArithNode::ArithNode () : SaveNode { Value::value_type_t::FLOAT } {
}

LogicNode::LogicNode () : SaveNode { Value::value_type_t::BOOL } {
}

AccumulateNode::AccumulateNode () : SaveNode { Value::value_type_t::SYMBOL_STRING } {
}

SymbolNode::SymbolNode () : SaveNode { Value::value_type_t::SYMBOL } {
}

//EVAL FUNCTIONS 

Value ValueNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   return mValue;
}

Value SimpleNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   return inVec.at ( 0 ); 
}

Value LookupNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   std::string const &key { inVec.at ( 0 ).getString () };
   mValue.setFloat ( sym.getParam ( key ) );
   return mValue;
}

Value AccumulateNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   std::vector<Symbol> symbolString ( inVec.size () );
   std::transform ( inVec.begin (), inVec.end (), symbolString.begin (), 
         [] ( Value const &val ) { return val.getSymbol (); } );
   mValue.setSymbolString ( symbolString );
   return mValue;
}

Value SymbolNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   Symbol retSym;
   auto iter = inVec.begin ();
   retSym.setName ( ( *( iter++ ) ).getString () );

   while ( iter != inVec.end () ) {
      std::string const &paramName { ( *( iter++ ) ).getString () };
      double const &paramVal { ( *( iter++ ) ).getFloat () };
      retSym.addParam ( paramName, paramVal );
   }
   
   mValue.setSymbol ( retSym );
   return mValue;
}


Value PlusNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   double const &val { inVec.at ( 0 ).getFloat () + inVec.at ( 1 ).getFloat () };
   mValue.setFloat ( val );
   return mValue;
}

Value MinusNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   double const &val { inVec.at ( 0 ).getFloat () - inVec.at ( 1 ).getFloat () };
   mValue.setFloat ( val );
   return mValue;
}

Value MulNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   double const &val { inVec.at ( 0 ).getFloat () * inVec.at ( 1 ).getFloat () };
   mValue.setFloat ( val );
   return mValue;
}

Value DivNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   double const &val { inVec.at ( 0 ).getFloat () / inVec.at ( 1 ).getFloat () };
   mValue.setFloat ( val );
   return mValue;
}

Value PowNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   double const &val { pow ( inVec.at ( 0 ).getFloat (), inVec.at ( 1 ).getFloat () ) };
   mValue.setFloat ( val );
   return mValue;
}

Value PowRootNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   double const &val { pow ( inVec.at ( 0 ).getFloat (), 1.0 / ( inVec.at ( 1 ).getFloat () ) ) };
   mValue.setFloat ( val );
   return mValue;
}

Value LessNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   bool const &val { inVec.at ( 0 ).getFloat () < inVec.at ( 1 ).getFloat () };
   mValue.setBool ( val );
   return mValue;
}

Value GreaterNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   bool const &val { inVec.at ( 0 ).getFloat () > inVec.at ( 1 ).getFloat () };
   mValue.setBool ( val );
   return mValue;
}

Value LessEqualNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   bool const &val { inVec.at ( 0 ).getFloat () <= inVec.at ( 1 ).getFloat () };
   mValue.setBool ( val );
   return mValue;
}

Value GreaterEqualNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   bool const &val { inVec.at ( 0 ).getFloat () >= inVec.at ( 1 ).getFloat () };
   mValue.setBool ( val );
   return mValue;
}

Value EqualNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   bool const &val { inVec.at ( 0 ).getFloat () == inVec.at ( 1 ).getFloat () };
   mValue.setBool ( val );
   return mValue;
}

Value NotEqualNode::evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) {
   bool const &val { inVec.at ( 0 ).getFloat () != inVec.at ( 1 ).getFloat () };
   mValue.setBool ( val );
   return mValue;
}
