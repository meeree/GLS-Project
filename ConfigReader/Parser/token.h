#ifndef string
#include <string>
#endif

class Token {
private:
   enum token_type_t {
      STRING, INT, FLOAT
   } mTokenType;

   union TokenContainer {
      TokenContainer ();
      TokenContainer ( std::string const &stringTok );
      TokenContainer ( int const &intTok );
      TokenContainer ( double const &floatTok );
      std::string * mString;
      int * mInt;
      double * mFloat;
   } mContainer;

public:
   Token ();

   Token ( std::string const &stringTok );
   std::string * const &getString () const;
   bool isString () const; 
   void setString ( std::string const &newString );

   Token ( int const &intTok );
   int * const &getInt () const;
   bool isInt () const; 
   void setInt ( int const &newInt );

   Token ( double const &floatTok );
   double * const &getFloat () const;
   bool isFloat () const; 
   void setFloat ( double const &newFloat );

   ~Token ();
};
