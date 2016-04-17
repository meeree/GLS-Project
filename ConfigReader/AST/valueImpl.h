#ifndef string
#include <string>
#endif

enum class value_type_t;
class Symbol;

class FloatValue : public Value {
private:
   double * mValue;
public:
   FloatValue ( double const &inValue );
   void setValue ( double const &newValue );
   double const &getValue () const;
   value_type_t getType () const;
};

class IntValue : public Value {
private:
   int * mValue;
public:
   IntValue ( int const &inValue );
   void setValue ( int const &newValue );
   int const &getValue () const;
   value_type_t getType () const;
};

class StringValue : public Value {
private:
   std::string * mValue;
public:
   StringValue ( std::string const &inValue );
   void setValue ( std::string const &newValue );
   std::string const &getValue () const;
   value_type_t getType () const;
};

class BoolValue : public Value {
private:
   bool * mValue;
public:
   BoolValue ( bool const &inValue );
   void setValue ( bool const &newValue );
   bool const &getValue () const;
   value_type_t getType () const;
};
