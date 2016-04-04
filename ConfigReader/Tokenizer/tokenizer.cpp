#include "tokenizer.h"
#include <iostream>
#ifndef cassert
#include <cassert>
#endif 

GLSstring Tokenizer::readAxiom ( std::ifstream &configFile ) {
   std::string line;
   GLSstring axiom;
   while ( getline (configFile, line) ) {
      if ( line.find ("axiom") != std::string::npos ) {
         if ( getline (configFile, line) ) {
            std::string::iterator letter {line.begin()};

            if (*letter == ' ') { // whitespace
               while (*(++letter) == ' ') {} 
            }

            while (*letter != ';') {
               std::string identifier {*letter};
               while (*(letter++) != ')') { // Name and params
                  identifier.push_back(*letter);
               } 

               std::string * identPtr {new std::string(identifier)};
               IdentifierToken * identToken {new IdentifierToken (identPtr)};
               axiom.push_back( identToken );

               if (*letter == ' ') { // whitespace
                  while (*(++letter) == ' ') {} 
               }
            }
         }
         return axiom;
      }
   }
}

std::vector<GLSstring> Tokenizer::readProductions ( std::ifstream &configFile ) {
   return {};
}

Tokenizer::~Tokenizer () {
   for ( auto const &token: mAxiom ) {
      delete token;
   }
   for ( auto const &production: mProductions ) {
      for ( auto const &token: production) {
         delete token;
      }
   }
}

int main () {
   std::ifstream fl;
   fl.open("./config.GLS");
   Tokenizer tk (fl);
   GLSstring axiom {tk.getAxiom()};
   for (auto const &name: axiom) {
      std::cout<<*(static_cast<IdentifierToken*>(name)->getData())<<std::endl;
   }
}
