#include "tokenizer.h"
#include <iostream>
#ifndef cassert
#include <cassert>
#endif 

GLSstring Tokenizer::readAxiom ( std::ifstream &configFile ) {
   std::string line;
   GLSstring axiom;
   while ( getline ( configFile, line ) ) {
      if ( line.find ( "axiom" ) != std::string::npos ) {
         if ( getline ( configFile, line ) ) {
            std::string::iterator letter { line.begin( ) };

            if ( *letter == ' ' ) { // whitespace
               while ( *( ++letter ) == ' ' ) { } 
            }

            while ( *letter != ';' ) {
               std::string identifier { *letter };
               while ( *( letter++ ) != ')' ) { // Name and params
                  identifier.push_back( *letter );
               } 

               std::string * identPtr { new std::string( identifier ) };
               IdentifierToken * identToken { new IdentifierToken ( identPtr ) };
               axiom.push_back( identToken );

               if ( *letter == ' ') { // whitespace
                  while ( *( ++letter ) == ' ') { } 
               }
            }
         }
         return axiom;
      }
   }
}

//std::vector<GLSstring> Tokenizer::readProductions ( std::ifstream &configFile ) {
//   std::string line;
//   std::vector<GLSstring> productions;
//   while ( getline ( configFile, line ) ) {
//      if ( line.find ( "productions" ) != std::string::npos ) {
//         while ( getline ( configFile, line ) ) {
//            productions.push_back({});
//
//            std::string::iterator letter { line.begin( ) };
//            if ( *letter == ' ') { // whitespace
//               while ( *( ++letter ) == ' ') { } 
//            }
//
//            if ( *( ++letter ) != ':') { // begin production
//               break;
//            } 
//            
//            if ( *letter == ' ') { // whitespace
//               while ( *( ++letter ) == ' ') { } 
//            }
//
//            std::string identifier { *letter };
//            while ( *( letter++ ) != ')') { // name and params
//               identifier.push_back( *letter );
//            } 
//            std::string * identPtr { new std::string( identifier ) };
//            IdentifierToken * identToken { new IdentifierToken ( identPtr ) };
//            productions.back().push_back ( identToken );         
//
//            if ( *letter == ' ') { // whitespace
//               while ( *( ++letter ) == ' ') { } 
//            }
//            
//            if ( *(++letter) != ':' && *(++letter) != '=' ) {
//               throw "no production operator ':='";
//            }
//
//            std::string ident {":="}; 
//            std::string * strPtr { new std::string ( ident ) };
//            std::cout<<&strPtr<<std::endl;
//            OperatorToken * opToken { new OperatorToken ( strPtr ) };
//            std::cout<<&opToken<<std::endl;
//            productions.back().push_back ( opToken );
//            
//            while ( *letter != ';' ) {
//               std::string identifier { *letter };
//               while ( *( letter++ ) != ')' ) { // Name and params
//                  identifier.push_back( *letter );
//               } 
//
//               std::string * identPtr { new std::string( identifier ) };
//               IdentifierToken * identToken { new IdentifierToken ( identPtr ) };
//               productions.back().push_back( identToken );
//
//               if ( *letter == ' ') { // whitespace
//                  while ( *( ++letter ) == ' ') { } 
//               }
//            }
//         }
//      }
//   }
//}
int main ( ) {
   std::ifstream fl;
   fl.open( "./config.GLS" );
   Tokenizer tk ( fl );
   GLSstring axiom { tk.getAxiom( ) };
   for ( auto const &name: axiom ) {
      std::cout<<*( static_cast<IdentifierToken*>( name )->getData( ) )<<std::endl;
   }
}
