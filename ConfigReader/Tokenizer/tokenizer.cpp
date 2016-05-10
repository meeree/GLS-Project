#include <iostream>
#include <fstream>
//#ifndef TOKEN_H
//#define TOKEN_H
//#include "tokenizer.h"
//#endif
//

bool cndCheck ( std::string::iterator &iter );

void readAxiom ( std::istream &fl ) {
   std::string line;
   while ( std::getline ( fl, line ) ) {
      auto iter = line.begin ();
      while ( iter != line.end () ) {
         cndCheck ( iter );
         std::cout<<*iter<<std::endl;
      }
   }
}

bool progress ( char const &val1, char const &val2, std::string::iterator &iter ) {
   if ( *( iter++ ) == val2 ) {
      ++iter;
      return true;
   } 

   return false;
}


bool cndCheck ( std::string::iterator &iter ) {
   if ( progress ( *iter, '=' ) ) {

   switch ( *iter ) {
      case '>': {
         if ( *( ++iter ) == '=' ) {
            std::cout<<"GREAT EQUAL"<<std::endl;
         } else {
            std::cout<<"GREAT"<<std::endl;
         }
         return true;
      }
      case '<': { 
         if ( *( ++iter ) == '=' ) {
            std::cout<<"LESS EQUAL"<<std::endl;
         } else {
            std::cout<<"LESS"<<std::endl;
         }
         return true;
      }
      case '=': {
         if ( *( iter+1 ) == '=' ) {
            std::cout<<"EQUAL"<<std::endl;
            ++iter;
            return true;
         }
         return false;
      }
      case '!': {
         if ( *( iter+1 ) == '=' ) {
            std::cout<<"NOT EQUAL"<<std::endl;
            ++iter;
            return true;
         }
         return false;
      }
      default: 
         return false;
   }
}

int main () {
   std::ifstream fl;
   fl.open ( "./fl.txt" );
   readAxiom ( fl );
}
