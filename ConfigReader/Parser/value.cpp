#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif

Value::ValueContainer::ValueContainer ( int const &intVal ) : mInt { new int { intVal } } {
}
Value::ValueContainer::ValueContainer ( double const &floatVal ) : mFloat { new double { floatVal } } {
}
Value::ValueContainer::ValueContainer ( bool const &boolVal ) : mBool { new bool { boolVal } } {
}

Value::Value () {
}
Value::Value ( int const &intVal ) : mContainer { intVal }, mValueType { INT } {
}
int * const &Value::getInt () const {
   return mContainer.mInt;
}
bool Value::isInt () const {
   return mValueType == INT;
}
void Value::setInt ( int const &newInt ) {
   delete mContainer.mInt;
   mContainer.mInt = new int { newInt };
}

Value::Value ( double const &floatVal ) : mContainer { floatVal } {
}
double * const &Value::getFloat () const {
   return mContainer.mFloat;
}
bool Value::isFloat () const {
   return mValueType == FLOAT;
}
void Value::setFloat ( double const &newFloat ) {
   delete mContainer.mFloat;
   mContainer.mFloat = new double { newFloat };
}

Value::Value ( bool const &boolVal ) : mContainer { boolVal } {
}
bool * const &Value::getBool () const {
   return mContainer.mBool;
}
bool Value::isBool () const {
   return mValueType == BOOL;
}
void Value::setBool ( bool const &newBool ) {
   delete mContainer.mBool;
   mContainer.mBool = new bool { newBool }; 
}

Value::~Value () {
   if ( isInt () ) {
      delete mContainer.mInt;
   } else if ( isFloat () ) {
      delete mContainer.mFloat;
   } else if ( isBool () ) {
      delete mContainer.mBool;
   }
}
