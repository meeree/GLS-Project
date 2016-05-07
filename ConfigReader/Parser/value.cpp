Value::Value () {
}
Value::~Value () {
}
int &Value::getInt () const { 
   throw "no int or float value";
   exit ( EXIT_FAILURE ); 
} 
double &Value::getFloat () const { 
   throw "no int or float value";
   exit ( EXIT_FAILURE ); 
}
double &Value::getBool () const { 
   throw "no bool value";
   exit ( EXIT_FAILURE ); 
}

bool Value::isInt () const {
   return false;
}
bool Value::isFloat () const {
   return false;
}
bool Value::isBool () const {
   return false;
}

IntValue::IntValue ( int const &value ) : mValue { value } {
}
IntValue::~IntValue () {
   delete mValue;
}
int &IntValue::getInt () const { 
   return mValue;
}
double &IntValue::getFloat () const { 
   return (double)mValue;
}
bool IntValue::isInt () const {
   return true;
}

FloatValue::FloatValue ( int const &value ) : mValue { value } {
}
FloatValue::~FloatValue () {
   delete mValue;
}
double &FloatValue::getFloat () const { 
   return mValue;
}
int &FloatValue::getInt () const { 
   return (int)mValue;
}
bool FloatValue::isFloat () const {
   return true;
}

BoolValue::BoolValue ( int const &value ) : mValue { value } {
}
BoolValue::~BoolValue () {
   delete mValue;
}
bool &BoolValue::getBool () const { 
   return mValue;
}
bool BoolValue::isBool () const {
   return true;
}
