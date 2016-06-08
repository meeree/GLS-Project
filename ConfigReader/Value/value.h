#ifndef _VALUE__H_INCLUDED__
#define _VALUE__H_INCLUDED__

#include <vector>
#include <memory>

class Symbol;

class Value {
private:
   struct ValueContainer {
      ValueContainer () = default;

      ValueContainer ( int const &intVal );
      ValueContainer ( double const &floatVal );
      ValueContainer ( bool const &boolVal );
      ValueContainer ( std::string const &stringVal );
      ValueContainer ( Symbol const &symbolVal );
      ValueContainer ( std::vector<Symbol> const &symbolString );

      std::shared_ptr<int>  mInt;
      std::shared_ptr<double>  mFloat;
      std::shared_ptr<bool>  mBool;
      std::shared_ptr<std::string>  mString;
      std::shared_ptr<Symbol>  mSymbol;
      std::shared_ptr<std::vector<Symbol> >  mSymbolString;
   } mContainer;

public:
   enum value_type_t {
      INT, FLOAT, BOOL, STRING, SYMBOL, SYMBOL_STRING 
   } mValueType;

   Value () = default;

   Value ( value_type_t const &valueType );

   Value ( int const &intVal );
   int const getInt () const;
   bool isInt () const; 
   void setInt ( int const &newInt );

   Value ( double const &floatVal );
   double const getFloat () const;
   bool isFloat () const; 
   void setFloat ( double const &newFloat );

   Value ( bool const &boolVal );
   bool const getBool () const;
   bool isBool () const; 
   void setBool ( bool const &newBool );

   Value ( std::string const &stringVal );
   std::string const getString () const;
   bool isString () const; 
   void setString ( std::string const &newString );

   Value ( Symbol const &symbolVal );
   Symbol const getSymbol () const;
   bool isSymbol () const; 
   void setSymbol ( Symbol const &newSymbol );

   Value ( std::vector<Symbol> const &symbolString );
   std::vector<Symbol> const getSymbolString () const;
   bool isSymbolString () const; 
   void setSymbolString ( std::vector<Symbol> const &newSymbolString );

};

#endif
