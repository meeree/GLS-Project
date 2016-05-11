#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif
#ifndef SYMBOL_H
#define SYMBOL_H
#include "../Symbol/symbol.h"
#endif

Value::ValueContainer::ValueContainer ( int const &intVal ) : mInt { new int { intVal } } {
}
Value::ValueContainer::ValueContainer ( double const &floatVal ) : mFloat { new double { floatVal } } {
}
Value::ValueContainer::ValueContainer ( bool const &boolVal ) : mBool { new bool { boolVal } } {
}
Value::ValueContainer::ValueContainer ( std::string const &stringVal ) : mString { new std::string { stringVal } } {
}
Value::ValueContainer::ValueContainer ( Symbol const &symbolVal ) : mSymbol { new Symbol { symbolVal } } {
}
Value::ValueContainer::ValueContainer ( std::vector<Symbol> const &symbolString ) : mSymbolString { new std::vector<Symbol> { symbolString } } {
}

Value::Value ( value_type_t const &valueType ) : mValueType { valueType } {
   if ( isInt () ) {
      mContainer.mInt = std::make_shared<int> ( int {} );
   } else if ( isFloat () ) {
      mContainer.mFloat = std::make_shared<double> ( double {} );
   } else if ( isBool () ) {
      mContainer.mBool = std::make_shared<bool> ( bool {} );
   } else if ( isString () ) {
      mContainer.mString = std::make_shared<std::string> ( std::string {} );
   } else if ( isSymbol () ) {
      mContainer.mSymbol = std::make_shared<Symbol> ( Symbol {} );
   } else if ( isSymbolString () ) {
      mContainer.mSymbolString = std::make_shared<std::vector<Symbol> > ( std::vector<Symbol> {} );
   }
}

Value::Value ( int const &intVal ) : mContainer { intVal }, mValueType { INT } {
}
int const Value::getInt () const {
   if ( !isInt () && !isFloat () ) {
      std::cout<<"request for int from value failed: value does not contain int or float";
      exit ( EXIT_FAILURE );
   }
   if ( isFloat () ) { 
      return (int)*mContainer.mFloat;
   }
   return *mContainer.mInt;
}
bool Value::isInt () const {
   return mValueType == INT;
}
void Value::setInt ( int const &newInt ) {
   *mContainer.mInt = newInt;
}

Value::Value ( double const &floatVal ) : mContainer { floatVal }, mValueType { FLOAT } {
}
double const Value::getFloat () const {
   if ( !isFloat () && !isInt () ) {
      std::cout<<"request for float from value failed: value does not contain float or int";
      exit ( EXIT_FAILURE );
   }
   if ( isInt () ) { 
      return (double)*mContainer.mInt;
   }
   return *mContainer.mFloat;
}
bool Value::isFloat () const {
   return mValueType == FLOAT;
}
void Value::setFloat ( double const &newFloat ) {
   *mContainer.mFloat = newFloat;
}

Value::Value ( bool const &boolVal ) : mContainer { boolVal }, mValueType { BOOL } {
}
bool const Value::getBool () const {
   if ( !isBool () ) {
      std::cout<<"request for bool from value failed: value does not contain bool";
      exit ( EXIT_FAILURE );
   }
   return *mContainer.mBool;
}
bool Value::isBool () const {
   return mValueType == BOOL;
}
void Value::setBool ( bool const &newBool ) {
   *mContainer.mBool = newBool;
}

Value::Value ( std::string const &stringVal ) : mContainer { stringVal }, mValueType { STRING } {
}
std::string const Value::getString () const {
   if ( !isString () ) {
      std::cout<<"request for string from value failed: value does not contain string";
      exit ( EXIT_FAILURE );
   }
   return *mContainer.mString;
}
bool Value::isString () const {
   return mValueType == STRING;
}
void Value::setString ( std::string const &newString ) {
   *mContainer.mString = newString;
}

Value::Value ( Symbol const &symbolVal ) : mContainer { symbolVal }, mValueType { SYMBOL } {
}
Symbol const Value::getSymbol () const {
   if ( !isSymbol () ) {
      std::cout<<"request for symbol from value failed: value does not contain symbol";
      exit ( EXIT_FAILURE );
   }
   return *mContainer.mSymbol;
}
bool Value::isSymbol () const {
   return mValueType == SYMBOL;
}
void Value::setSymbol ( Symbol const &newSymbol ) {
   *mContainer.mSymbol = newSymbol;
}

Value::Value ( std::vector<Symbol> const &symbolString ) : mContainer { symbolString }, mValueType { SYMBOL_STRING } {
}
std::vector<Symbol> const Value::getSymbolString () const {
   if ( !isSymbolString () ) {
      std::cout<<"request for symbol string from value failed: value does not contain symbol string";
      exit ( EXIT_FAILURE );
   }
   return *mContainer.mSymbolString;
}
bool Value::isSymbolString () const {
   return mValueType == SYMBOL_STRING;
}
void Value::setSymbolString ( std::vector<Symbol> const &newSymbolString ) {
   *mContainer.mSymbolString = newSymbolString;
}
