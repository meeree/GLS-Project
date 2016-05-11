#ifndef fstream
#include <fstream>
#endif
#ifndef vector
#include <vector>
#endif
#ifndef TOKEN_H
#define TOKEN_H
#include "../Token/token.h"
#endif


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
