#ifndef TOKEN_H
#define TOKEN_H
#include "token.h"
#endif

#ifndef iostream
#include <iostream>
#endif

Token::TokenContainer::TokenContainer ( std::string const &stringTok ) : mString { new std::string { stringTok } } {
}
Token::TokenContainer::TokenContainer ( int const &intTok ) : mInt { new int { intTok } } {
}
Token::TokenContainer::TokenContainer ( double const &floatTok ) : mFloat { new double { floatTok } } {
}

Token::Token ( std::string const &stringTok ) : mContainer { stringTok }, mTokenType { STRING } {
}
std::string const &Token::getString () const {
   if ( !isString () ) {
      std::cerr<<"request for string from token failed: token does not contain string"<<std::endl;
      exit ( EXIT_FAILURE );
   }
   return *mContainer.mString;
}
bool Token::isString () const {
   return mTokenType == STRING;
}
void Token::setString ( std::string const &newString ) {
   *mContainer.mString = newString;
}

Token::Token ( int const &intTok ) : mContainer { intTok }, mTokenType { INT } {
}
int const &Token::getInt () const {
   if ( !isInt () ) {
      std::cerr<<"request for int from token failed: token does not contain int"<<std::endl;
      exit ( EXIT_FAILURE );
   }
   return *mContainer.mInt;
}
bool Token::isInt () const {
   return mTokenType == INT;
}
void Token::setInt ( int const &newInt ) {
   *mContainer.mInt = newInt;
}

Token::Token ( double const &floatTok ) : mContainer { floatTok }, mTokenType { FLOAT } {
}
double const &Token::getFloat () const {
   if ( !isFloat () ) {
      std::cerr<<"request for float from token failed: token does not contain float"<<std::endl;
      exit ( EXIT_FAILURE );
   }
   return *mContainer.mFloat;
}
bool Token::isFloat () const {
   return mTokenType == FLOAT;
}
void Token::setFloat ( double const &newFloat ) {
   *mContainer.mFloat = newFloat;
}
