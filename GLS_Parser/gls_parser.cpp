#include "gls_interface.h"
#include "tokenizer.h"

GLSParserInterface::GLSParserInterface ( std::ifstream &fl ) : mTkr { new Tokenizer { fl } } {
}

int main () {
    std::ifstream fl;
    fl.open ( "fl.txt" );
    GLSParserInterface gls { fl };
}
