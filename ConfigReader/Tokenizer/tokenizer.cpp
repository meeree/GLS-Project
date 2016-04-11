#ifndef TOKEN_H
#define TOKEN_H
#include "tokenizer.h"
#endif

GLSstring Tokenizer::readAxiom ( std::ifstream &configFile ) {
   configFile.clear();
   configFile.seekg(0, configFile.beg);

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

std::vector<GLSstring> Tokenizer::readProductions ( std::ifstream &configFile ) {
   configFile.clear();
   configFile.seekg(0, configFile.beg);
   
   std::string line;
   std::vector<GLSstring> productions;

   while ( getline ( configFile, line ) ) {
      if ( line.find ( "productions" ) != std::string::npos ) {
         while ( getline ( configFile, line ) ) {
            productions.push_back({});

            std::string::iterator letter { line.begin( ) };
            if ( *letter == ' ') { // whitespace
               while ( *( ++letter ) == ' ') { } 
            }

            if ( *(letter++) != ':') { // begin production
               break;
            } 

            if ( *letter == ' ') { // whitespace
               while ( *( ++letter ) == ' ') { } 
            }

            std::string identifier { *letter };
            while ( *( letter++ ) != ')') { // name and params
               identifier.push_back( *letter );
            } 

            std::string * identPtr { new std::string( identifier ) };
            IdentifierToken * identToken { new IdentifierToken ( identPtr ) };
            productions.back().push_back ( identToken );         

            if ( *letter == ' ') { // whitespace
               while ( *( ++letter ) == ' ') { } 
            }

            if ( *(letter++) != '(' ) {
               throw "Syntax error: no '(' operator";
            }

            while ( *letter != ')' ) {

               if ( *letter == ' ') { // whitespace
                  while ( *( ++letter ) == ' ') { } 
               }

               std::string condition { *letter };
               while ( *(++letter) != ',') { // param name condition op and number
                  condition.push_back( *letter );
               } letter++;

               std::string * cndPtr { new std::string( condition ) };
               ConditionToken * cndToken { new ConditionToken ( cndPtr ) };
               productions.back().push_back ( cndToken );         

               if ( *letter == ' ') { // whitespace
                  while ( *( ++letter ) == ' ') { } 
               }

            }

            if ( *(++letter) == ' ') { // whitespace
               while ( *( ++letter ) == ' ') { } 
            }
            
            if ( *letter != ':' || *(++letter) != '=' ) {
               throw "Syntax error: no ':=' operator";
            } ++letter;

            std::string * strPtr { new std::string ( ":=" ) };
            OperatorToken * opToken { new OperatorToken ( strPtr ) };
            productions.back().push_back ( opToken );

            if ( *letter == ' ') { // whitespace
               while ( *( ++letter ) == ' ') { } 
            }
            
            while ( *letter != ';' ) {
               std::string identifier { *letter };
               while ( *( letter++ ) != ')' ) { // Name and params
                  identifier.push_back( *letter );
               }

               std::string * identPtr { new std::string( identifier ) };
               IdentifierToken * identToken { new IdentifierToken ( identPtr ) };
               productions.back().push_back( identToken );

               if ( *letter == ' ') { // whitespace
                  while ( *( ++letter ) == ' ') { } 
               }
            }
         }

         return productions;
      }
   }
}

Tokenizer::~Tokenizer () {
   for (auto &token: mAxiom) {
      delete token;
   }

   for (auto const &production: mProductions) {
      for (auto &token: production) {
         delete token;
      }
   }
}
