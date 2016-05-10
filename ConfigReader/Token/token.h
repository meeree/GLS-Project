#ifndef string
#include <string>
#endif
#ifndef memory
#include <memory>
#endif

class Token {
private:
   enum token_type_t {
      STRING, INT, FLOAT
   } mTokenType;

   struct TokenContainer {
      TokenContainer () = default;

      TokenContainer ( std::string const &stringTok );
      TokenContainer ( int const &intTok );
      TokenContainer ( double const &floatTok );
      TokenContainer ( Token::TokenContainer const &tokCot, Token::token_type_t const &tokType );
      std::shared_ptr<std::string>  mString;
      std::shared_ptr<int>  mInt;
      std::shared_ptr<double>  mFloat;
   } mContainer;

public:
   Token () = default;

   Token ( std::string const &stringTok );
   std::string const &getString () const;
   bool isString () const; 
   void setString ( std::string const &newString );

   Token ( int const &intTok );
   int const &getInt () const;
   bool isInt () const; 
   void setInt ( int const &newInt );

   Token ( double const &floatTok );
   double const &getFloat () const;
   bool isFloat () const; 
   void setFloat ( double const &newFloat );
//
//   ~Token ();
};
