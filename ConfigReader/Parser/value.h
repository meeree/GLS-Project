class Value {
private:
   enum value_type_t {
      INT, FLOAT, BOOL 
   } mValueType;

   union ValueContainer {
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

   Value ( double const &doubleVal );
   double * const &getFloat () const;
   bool isFloat () const; 
   void setFloat ( double const &newFloat );

   Value ( bool const &boolVal );
   bool * const &getBool () const;
   bool isBool () const; 
   void setBool ( bool const &newBool );

   ~Value ();
};
