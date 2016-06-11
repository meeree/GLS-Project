#include "tokenizer.h"
#include "token.h"
#include <cctype>

#include <iostream>
#include <vector>

/* non-accepting states
   state 0 represents the searching state
   state 1 represents the DFA finding a symbol but needing more for a full symbol
   accepting states
   state 2 represents the DFA finding a symbol and not needing more but still searching
   state 3 represents the done state */
std::map<std::pair<unsigned, char>, unsigned> Tokenizer::mSymStateTbl {
    {{1,'='},3}, {{2,'='},3}, {{0,'>'},2}, {{0,'<'},2}, {{0,'!'},1},  {{0,'='},1}, {{0,':'},1},
    {{0,';'},3}, {{0,','},3}, {{0,'%'},3}, {{0,'&'},3}, {{0,'|'},3}, 
    {{0,'+'},3}, {{0,'-'},3}, {{0,'*'},3}, {{0,'/'},3}, {{0,'^'},3}, {{0,'~'},3}, 
    {{0,'['},3}, {{0,']'},3}, {{0,'('},3}, {{0,')'},3}
};

Tokenizer::Tokenizer ( std::ifstream& right ) : mRight { right }, mLnCtr {1}, mVrtCtr {1} {
    shift ();
}

Tokenizer::~Tokenizer () {
    while ( mLeft.size () > 0 ) {
        mLeft.pop ();
    }
}

void Tokenizer::error () const {
    std::cerr<<"Exiting at line "<<mLnCtr<<" vertical position "<<mVrtCtr<<std::endl;
    exit ( EXIT_FAILURE );
}

void Tokenizer::shift () {
    if ( mHead == '\n' ) {
        ++mLnCtr;
        mVrtCtr = 0;
    } else {
        ++mVrtCtr;
    }
    mBuff += mHead ;
    if ( !mRight.get ( mHead ) ) {
        mHead = EOF;
    }
}

void Tokenizer::acceptToken ( std::unique_ptr<Token>& tk ) {
    mLeft.push ( std::move ( tk ) );
    mBuff.clear ();
}

void Tokenizer::tokenize () {
    if ( std::isalpha ( mHead ) ) {
        tokenizeWord ();
    } else if ( std::isdigit ( mHead ) || mHead == '.') {
        tokenizeDouble ();
    } else if ( mHead == '\n' || mHead == ' ' ) {
        shift ();
    } else if ( mSymStateTbl.find ( {0,mHead} ) != mSymStateTbl.end () ) {
        mSymState = 0;
        tokenizeSymbol ();
    } else {
        std::cerr<<"Tokenizer could not find matching grammar rule for character "<<mHead<<"."<<std::endl;
        error ();
    }
}

void Tokenizer::tokenizeSymbol () {
    while ( true ) {
        if ( mSymStateTbl.find ( {mSymState,mHead} ) == mSymStateTbl.end () ) {
            switch ( mSymState ) {
                case 0: case 1: 
                    std::cerr<<"Tokenizer could find matching grammar rule for symbol "<<mBuff<<mHead<<"."<<std::endl;
                    error ();
                case 2: case 3:
                    std::unique_ptr<Token> tk { new Token { mBuff, Token::type_t::SYMBOL } };
                    acceptToken ( tk );
                    return;
            }
        } else {
            switch ( mSymState ) {
                case 0: case 1: case 2: 
                    mSymState = mSymStateTbl [ {mSymState,mHead } ];
                    shift ();
                    break;
                case 3: 
                    return;
            }
        }
    }
}

void Tokenizer::tokenizeWord () {
    shift ();
    while ( std::isalnum ( mHead ) || mHead == '_' ) {
        shift ();
    }
    std::unique_ptr<Token> tk { new Token { mBuff, Token::type_t::WORD } };
    acceptToken ( tk );
}

void Tokenizer::tokenizeDouble () {
    /* first double form: int "." [unsignedInt]
       second double form: [int] "." [unsignedInt] */
    bool firstForm { false };
    std::string buff;
    if ( std::isdigit ( mHead ) ) {
        firstForm = true;
        /* if the double or int starts w/ zero we cannot have a digit after it. */
        if ( mHead == '0' ) {
            shift ();
            if ( std::isdigit ( mHead ) ) {
                std::cerr<<"0"<<mHead<<"... is not a valid int."<<std::endl;
                error ();
            }
        }
    }
    while ( std::isdigit ( mHead ) ) {
        std::cout<<mHead<<std::endl;
        shift (); 
        buff += mHead;
    }
    std::cout<<mBuff<<std::endl;
    if ( mHead != '.' ) {
        std::unique_ptr<Token> tk { new Token { std::stoi ( buff ) } };
        acceptToken ( tk );
        return;
    }
    shift ();
    while ( std::isdigit ( mHead ) ) {
        shift (); 
    }
    std::unique_ptr<Token> tk { new Token { std::stod ( mBuff ) } };
    acceptToken ( tk );
}

void Tokenizer::tokenizeLoop () {
    while ( mHead != EOF ) {
        tokenize (); 
    }
}

int main () {
    std::ifstream fl;
    fl.open ( "fl" );
    Tokenizer tkr { fl };
    tkr.tokenizeLoop ();
}