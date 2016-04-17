#ifndef FUNC_NODE_H
#define FUNC_NODE_H
#include "implementation.h"
#endif
#ifndef cassert
#include <cassert>
#endif
#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif
#ifndef SYMBOL_H
#define SYMBOL_H
#include "symbol.h"
#endif

virtual Tree::~Tree () { 
   delete mTreeEval;
   for ( auto const &child: mChildren ) { delete child; } 
}

// Func Tree Children Evaluate Implementation: 

Value * const &ITETree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   assert ( leftEval->isBool() );
   switch ( static_cast<BoolValue*>(leftEval)->getValue() ) {
      case true: return mMiddleTree->evaluateTree(symbolContext, stringContext );
      case false: return mRightTree->evaluateTree(symbolContext, stringContext );
   }
}

Value * const &AndTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   assert ( leftEval->isBool() );
   if ( !static_cast<BoolValue*>(leftEval)->getValue() ) {
      return leftEval;
   }

   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };
   assert ( rightEval->isBool() );
   return rightEval;
}

Value * const &OrTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   assert ( leftEval->isBool() );
   if ( static_cast<BoolValue*>(leftEval)->getValue() ) {
      return leftEval;
   }

   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };
   assert ( rightEval->isBool() );
   return rightEval;
}

// Storage Func Tree Children Evaluate Implementation: 

//Value * const &SymbolTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
//   Value * const &nameEval {mNameTree->evaluateTree(symbolContext, stringContext ) };
//   assert ( nameEval->isString() );
//
//}

Value * const &LookupTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &keyEval {mKeyTree->evaluateTree(symbolContext, stringContext ) };
   assert ( keyEval->isString() );
   double const &param {symbolContext.getParam( static_cast<StringValue*>(keyEval)->getValue() )};
   mReturnValue = new FloatValue { param };
   return mReturnValue;
}

Value * const &FillStringTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) { 
   for ( auto const &child: mChildren ) {
      Value * const &childEval { child->evaluateTree( symbolContext, stringContext ) };
      assert ( childEval->isSymbol() );
      stringContext.push_back( static_cast<SymbolValue*>(childEval)->getValue() );
   }

   return mReturnValue;
}


Value * const &GreaterThanTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };

   if ( leftEval->isFloat() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() > static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() > static_cast<IntValue* const>( rightEval )->getValue() };
   else if ( leftEval->isInt() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() > static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() > static_cast<IntValue* const>( rightEval )->getValue() };
   else 
      mReturnValue = new BoolValue { false };

   return mReturnValue;
}

Value * const &GreaterThanEqualTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };

   if ( leftEval->isFloat() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() >= static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() >= static_cast<IntValue* const>( rightEval )->getValue() };
   else if ( leftEval->isInt() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() >= static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() >= static_cast<IntValue* const>( rightEval )->getValue() };
   else 
      mReturnValue = new BoolValue { false };

   return mReturnValue;
}

Value * const &LessThanTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };

   if ( leftEval->isFloat() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() < static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() < static_cast<IntValue* const>( rightEval )->getValue() };
   else if ( leftEval->isInt() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() < static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() < static_cast<IntValue* const>( rightEval )->getValue() };
   else 
      mReturnValue = new BoolValue { false };

   return mReturnValue;
}

Value * const &LessThanEqualTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };

   if ( leftEval->isFloat() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() <= static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() <= static_cast<IntValue* const>( rightEval )->getValue() };
   else if ( leftEval->isInt() ) 
      if ( rightEval->isFloat() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() <= static_cast<FloatValue* const>( rightEval )->getValue() };
      else if ( rightEval->isInt() ) 
         mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() <= static_cast<IntValue* const>( rightEval )->getValue() };
   else 
      mReturnValue = new BoolValue { false };

   return mReturnValue;
}

Value * const &EqualTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };

   if ( leftEval->isFloat() && rightEval->isFloat() ) 
      mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() == static_cast<FloatValue* const>( rightEval )->getValue() };
   else if ( leftEval->isInt() && rightEval->isInt() ) 
      mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() == static_cast<IntValue* const>( rightEval )->getValue() };
   else 
      mReturnValue = new BoolValue { false };
   return mReturnValue;
}

Value * const &NotEqualTree::evaluateTree ( Symbol const &symbolContext, std::vector<Symbol> &stringContext ) {
   Value * const &leftEval { mLeftTree->evaluateTree(symbolContext, stringContext) };
   Value * const &rightEval { mRightTree->evaluateTree(symbolContext, stringContext) };

   if ( leftEval->isFloat() && rightEval->isFloat() ) 
      mReturnValue = new BoolValue { static_cast<FloatValue* const>( leftEval )->getValue() != static_cast<FloatValue* const>( rightEval )->getValue() };
   else if ( leftEval->isInt() && rightEval->isInt() ) 
      mReturnValue = new BoolValue { static_cast<IntValue* const>( leftEval )->getValue() != static_cast<IntValue* const>( rightEval )->getValue() };
   else 
      mReturnValue = new BoolValue { false };
   return mReturnValue;
}
