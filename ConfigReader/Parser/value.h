#ifndef string
#include <string>
#endif

class Value {
private:
   enum value_type_t {
      INT, FLOAT, BOOL, STRING 
   } mValueType;

   union ValueContainer {
      ValueContainer ();
      ValueContainer ( int const &intVal );
      ValueContainer ( double const &floatVal );
      ValueContainer ( bool const &boolVal );
      int * mInt;
      double * mFloat;
      bool * mBool;
   } mContainer;

public:
   Value ();

   Value ( int const &intVal );
   int * const &getInt () const;
   bool isInt () const; 
   void setInt ( int const &newInt );

   Value ( double const &floatVal );
   double * const &getFloat () const;
   bool isFloat () const; 
   void setFloat ( double const &newFloat );

   Value ( bool const &boolVal );
   bool * const &getBool () const;
   bool isBool () const; 
   void setBool ( bool const &newBool );

   Value ( std::string const &stringVal );
   std::string * const &getString () const;
   std::string isString () const; 
   void setString ( std::string const &newString );

   ~Value ();
};
