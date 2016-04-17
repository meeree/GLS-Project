#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif
#ifndef VALUEIMPL_H
#define VALUEIMPL_H
#include "valueImpl.h"
#endif

enum class value_type_t {
   FLOAT,
   INT,
   STRING,
   BOOL
};

FloatValue::FloatValue ( double const &inValue ) : mValue { new double { inValue } } {}
void FloatValue::setValue ( double const &newValue ) { *mValue = newValue; }
double const &FloatValue::getValue () const { return *mValue; }
value_type_t FloatValue::getType () const { return value_type_t::FLOAT; } 

IntValue::IntValue ( int const &inValue ) : mValue { new int { inValue } } {}
void IntValue::setValue ( int const &newValue ) { *mValue = newValue; }
int const &IntValue::getValue () const { return *mValue; }
value_type_t IntValue::getType () const { return value_type_t::INT; } 

StringValue::StringValue ( std::string const &inValue ) : mValue { new std::string { inValue } } {}
void StringValue::setValue ( std::string const &newValue ) { *mValue = newValue; }
std::string const &StringValue::getValue () const { return *mValue; }
value_type_t StringValue::getType () const { return value_type_t::STRING; } 

BoolValue::BoolValue ( bool const &inValue ) : mValue { new bool { inValue } } {}
void BoolValue::setValue ( bool const &newValue ) { *mValue = newValue; }
bool const &BoolValue::getValue () const { return *mValue; }
value_type_t BoolValue::getType () const { return value_type_t::BOOL; } 
