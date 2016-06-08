#ifndef __TOKENIZER_H_INCLUDED__
#define __TOKENIZER_H_INCLUDED__

#include "../Token/token.h"
#include <fstream>
#include <vector>

class Tokenizer {
private:
   std::vector<Token> mTokenString;

   void tokenizeString ( std::string::iterator &iter );
   void tokenizeNum ( std::string::iterator &iter );
   void tokenizeBool ( std::string::iterator &iter );
   void tokenizeMisc ( std::string::iterator &iter );

public:
   Tokenizer () = default;
   void tokenizeFile ( std::ifstream &fl );
   std::vector<Token> const &getTokenString () const;
};

#endif
