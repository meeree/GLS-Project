#ifndef string 
#include <string>
#endif

//this is a bad seperation of concerns but because my code is
//quite specific I decided to keep it like this, for now,
//because it is easy for debugging.
class Value {
public:
   Value ();
   virtual double const &getFloat const;
   virtual int const &getInt const;
   virtual std::string const &getString const;
   virtual bool const &getBool const;

};

class FloatValue : public Value {
private: 
   double mValue;
public:
   FloatValue ( double const &value ) : mValue { value } {}
   double const &getFloat const;
};

class IntValue : public Value {
private: 
   int mValue;
public:
   IntValue ( int const &value ) : mValue { value } {}
   int const &getInt const;
};

class StringValue : public Value {
private: 
   std::string mValue;
public:
   StringValue ( std::string const &value ) : mValue { value } {}
   std::string const &getString const;
};

class BoolValue : public Value {
private: 
   bool mValue;
public:
   BoolValue ( bool const &value ) : mValue { value } {}
   bool const &getBool const;
};
