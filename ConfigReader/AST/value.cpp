Value::Value () {
}
double const &Value::getFloat () const {
	throw "Value Err: no float output"; 
}
int const &Value::getInt () const {
	throw "Value Err: no int output"; 
}
std::string const &Value::getString () const {
	throw "Value Err: no string output"; 
}
bool const &Value::getBool () const {
	throw "Value Err: no bool output"; 
}

FloatValue::FloatValue ( double const &value ) :
   mValue { value }
{}
double const &FloatValue::getFloat const {
	return mValue;
}

IntValue::IntValue ( int const &value ) :
   mValue { value }
{}
int const &IntValue::getInt const {
	return mValue;
}

StringValue::StringValue ( std::string const &value ) :
   mValue { value }
{}
std::string const &StringValue::getString const {
	return mValue;
}

BoolValue::BoolValue ( bool const &value ) :
   mValue { value }
{}
bool const &BoolValue::getBool const {
	return mValue;
}
