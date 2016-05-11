#include <iostream>
#include <cctype>
#include <cmath>
#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "tokenizer.h"
#endif

std::vector<Token> const &Tokenizer::getTokenString () const {
   return mTokenString;
}

void Tokenizer::tokenizeFile ( std::istream &fl ) {
   std::string line;
   while ( std::getline ( fl, line ) ) {
      auto iter = line.begin ();
      tokenizeString ( iter );
   }
}

void Tokenizer::tokenizeString ( std::string::iterator &iter ) {
   std::string val { "" };

   if ( ! std::isalpha ( *iter ) ) {
      return tokenizeNum ( iter );
   }

   while ( std::isalpha ( * ( iter ) ) ) {
      val += *( iter++ );
   }

   Token tok { val };
   mTokenString.push_back ( tok );

   return tokenizeNum ( iter );
}

void Tokenizer::tokenizeNum ( std::string::iterator &iter ) {
   std::string val { "" };

   if ( ! std::isdigit ( *iter ) ) {
      return tokenizeBool ( iter );
   }

   while ( std::isdigit ( * ( iter ) ) ) {
      val += *( iter++ );
   }

   if ( !( *iter == '.' ) ) {
      Token tok { std::stoi ( val ) };
      mTokenString.push_back ( tok );
      
      return tokenizeString ( iter );
   }

   val += *( iter++ );
   while ( std::isdigit ( * ( iter ) ) ) {
      val += *( iter++ );
   }

   std::cout<<std::stod( val )<<","<<val<<std::endl;
   Token tok { std::stod ( val ) };
   mTokenString.push_back ( tok );

   return tokenizeString ( iter );
}

void Tokenizer::tokenizeBool ( std::string::iterator &iter ) {
   // + - * / ^ ~ ( ) 
   // , ; 

   switch ( *iter ) {
      case '>': case '<': {
         std::string val { "" };
         if ( *( iter+1 ) == '=' ) {
            val += *( iter++ );
            val += *( iter++ );
         } else {
            val += *( iter++ );
         }

         Token tok { val };
         mTokenString.push_back ( tok );

         return tokenizeString ( iter );
      }

      case '=': case '!': case ':': {
         if ( *( iter+1 ) == '=' ) {
            std::string val { "" };
            val += *( iter++ );
            val += *( iter++ );
            Token tok { val };
            mTokenString.push_back ( tok );
         }

         return tokenizeString ( iter );
      }

      case '+': case '-': case '*': case '/': case '^': case '~': case '(': case ')': case ',': case ';': {
         std::string val { *( iter++ ) };
         Token tok { val };
         mTokenString.push_back ( tok );
         
         return tokenizeString ( iter );
      }
   }
         
   return tokenizeMisc ( iter );
}

void Tokenizer::tokenizeMisc ( std::string::iterator &iter ) {
   if ( *iter == '\0' ) {
      return;
   }
   return tokenizeString ( ++iter );
}

int main () {
   std::ifstream fl;
   fl.open ( "./fl.txt" );
   Tokenizer t;
   t.tokenizeFile ( fl );
   for (auto const &iter: t.getTokenString () ) {
      if ( iter.isString () ) {
         std::cout<<iter.getString()<<",";
      } else if ( iter.isInt () ) {
         std::cout<<iter.getInt()<<",";
      } else if ( iter.isFloat () ) {
         std::cout<<iter.getFloat ()<<",";
      }
   }
}
