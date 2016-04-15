#ifndef string
#include <string> 
#endif
#ifndef SYMBOL_H
#define SYMBOL_H
#include "symbol.h"
#endif

class Value {
protected:
   enum value_type_t {
      FLOAT, INT, STRING, BOOL, SYMBOL
   } mValueType;
   Value ( value_type_t const &valueType ) : mValueType { valueType } {} 
public:
   bool isFloat () const { return mValueType == FLOAT; }
   bool isInt () const { return mValueType == INT; }
   bool isString () const { return mValueType == STRING; }
   bool isBool () const { return mValueType == BOOL; }
   bool isSymbol () const { return mValueType == SYMBOL; }
};

class FloatValue : public Value {
private:
   double mValue;
public:
   FloatValue ( double const &inValue ) : mValue { inValue }, Value { FLOAT } {} 
   void setValue ( double const &newValue ) { mValue = newValue; } 
   double getValue () const { return mValue; } 
};

class IntValue : public Value {
private:
   int mValue;
public:
   IntValue ( int const &inValue ) : mValue { inValue }, Value { INT } {} 
   void setValue ( int const &newValue ) { mValue = newValue; } 
   int getValue () const { return mValue; } 
};

class StringValue : public Value {
private:
   std::string mValue;
public:
   StringValue ( std::string const &inValue ) : mValue { inValue }, Value { STRING } {} 
   void setValue ( std::string const &newValue ) { mValue = newValue; } 
   std::string getValue () const { return mValue; } 
};

class BoolValue : public Value {
private:
   bool mValue;
public:
   BoolValue ( bool const &inValue ) : mValue { inValue }, Value { BOOL } {} 
   void setValue ( bool const &newValue ) { mValue = newValue; } 
   bool getValue () const { return mValue; } 
};

class SymbolValue : public Value {
private:
   Symbol mValue;
public:
   SymbolValue ( Symbol const &inValue ) : mValue { inValue }, Value { SYMBOL } {} 
   void setValue ( Symbol const &newValue ) { mValue = newValue; } 
   Symbol getValue () const { return mValue; } 
};
