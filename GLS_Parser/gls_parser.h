#ifndef __INCLUDED_GLS_PARSER_H__
#define __INCLUDED_GLS_PARSER_H__

#include <memory>
#include <fstream>

class Token;
class Tokenizer;
class Parser;

class GLSParser {
private:
    std::unique_ptr<Tokenizer> mTkr;
//    std::unique_ptr<Parser> mPsr;
public:
    GLSParser ( std::ifstream& fl );
};

#endif
