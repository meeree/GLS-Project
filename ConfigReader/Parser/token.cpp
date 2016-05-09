#ifndef TOKEN_H
#define TOKEN_H
#include "token.h"
#endif

Token::TokenContainer::TokenContainer () {
}
Token::TokenContainer::TokenContainer ( std::string const &stringTok ) : mString { new std::string { stringTok } } {
}
Token::TokenContainer::TokenContainer ( int const &intTok ) : mInt { new int { intTok } } {
}
Token::TokenContainer::TokenContainer ( double const &floatTok ) : mFloat { new double { floatTok } } {
}

Token::Token () {
}

Token::Token ( std::string const &stringTok ) : mContainer { stringTok }, mTokenType { STRING } {
}
std::string * const &Token::getString () const {
   return mContainer.mString;
}
bool Token::isString () const {
   return mTokenType == STRING;
}
void Token::setString ( std::string const &newString ) {
   delete mContainer.mString;
   mContainer.mString = new std::string { newString};
}

Token::Token ( int const &intTok ) : mContainer { intTok }, mTokenType { INT } {
}
int * const &Token::getInt () const {
   return mContainer.mInt;
}
bool Token::isInt () const {
   return mTokenType == INT;
}
void Token::setInt ( int const &newInt ) {
   delete mContainer.mInt;
   mContainer.mInt = new int { newInt };
}

Token::Token ( double const &floatTok ) : mContainer { floatTok }, mTokenType { FLOAT } {
}
double * const &Token::getFloat () const {
   return mContainer.mFloat;
}
bool Token::isFloat () const {
   return mTokenType == FLOAT;
}
void Token::setFloat ( double const &newFloat ) {
   delete mContainer.mFloat;
   mContainer.mFloat = new double { newFloat };
}

Token::~Token () {
   if ( isString () ) {
      delete mContainer.mString;
   } else if ( isInt () ) {
      delete mContainer.mInt;
   } else if ( isFloat () ) {
      delete mContainer.mFloat;
   }
}
