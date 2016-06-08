#include "tokenizer.h"
#include "token.h"
#include <iostream>

//some information about the different states:
// double1 represents a double of the form: int, ".", [ int ] ; 
// double2 represents a double of the form: [ int ], ".", int ;
// cndOp1 represents a condition of the form ">" | "<" | ">=" | "<="
// cndOp2 represents a condition of the form "==" | "!="
// cndOp_2 represents the second part of a condtion: "="

void Tokenizer::shift () {
    ++mHoriPos;
    if ( mHead == '\n' ) {
        ++mVertPos;
        mHoriPos = 0;
    }

    mBuffer += mHead;
    if ( !( mRight.get ( mHead ) ) ) {
        mHead = EOF;
    }
}

void Tokenizer::setState () {
    if ( std::isdigit ( mHead ) ) {
        mState = state_t::Int; 
        return;
    }
    if ( std::isalpha ( mHead ) && mHead != 'P' && mHead != 'E' ) {
        switch ( mHead ) {
            case 'P': mState = state_t::PrdsLbl; return;
            case 'E': mState = state_t::PrdsLbl; return;
            default: mState = state_t::Word; return;
        }
    }
    switch ( mHead ) {
        case '.': mState = state_t::Double2; return;
        case '\n': case ' ': shift (); return setState (); 
        case EOF: mState = state_t::End; return;
        case '>': case '<': mState = state_t::CndOp1_1; return;
        case '=': case '!': mState = state_t::CndOp2_1; return;
        case ':': mState = state_t::PrdEquLbl; return;
        case ';': mState = state_t::SemiColon; return;
        case ',': mState = state_t::Comma; return;
        case '[': mState = state_t::OpnSqrBrk; return;
        case ']': mState = state_t::ClsSqrBrk; return;
        case '(': mState = state_t::OpnRndBrk; return;
        case ')': mState = state_t::ClsRndBrk; return;
        case '&': mState = state_t::And; return;
        case '|': mState = state_t::Or; return;
        case '%': mState = state_t::Percent; return;
        case '+': mState = state_t::Plus; return;
        case '-': mState = state_t::Min; return;
        case '*': mState = state_t::Mul; return;
        case '/': mState = state_t::Div; return;
        case '^': mState = state_t::Pow; return;
        case '~': mState = state_t::PowRt; return;
        default:
            std::cerr<<"SetState failed: no double or int."<<std::endl;
            mState = state_t::Err;
            return;
    }
}

Tokenizer::Tokenizer ( std::ifstream& right ) : mRight { right }, mState { state_t::Start }, mHoriPos {1}, mVertPos {1} {
    shift ();
}

void Tokenizer::errState () {
    std::cerr<<"Vertical position: "<<mVertPos<<"."<<std::endl;
    std::cerr<<"Horizontal position: "<<mHoriPos<<"."<<std::endl;
    exit (0);
}

void Tokenizer::intState () {
    if ( mHead == '0' ) {
        shift ();
        if ( std::isdigit ( mHead ) ) {
            std::cerr<<"Error while tokenizing int: 0"<<mHead<<"... is not a valid int."<<std::endl;
            mState = state_t::Err;
            return;
        }
    }
    while ( std::isdigit ( mHead ) ) {
        shift ();
    }
    switch ( mHead ) {
        case '.': 
            mState = state_t::Double1; 
            return;
        default: 
            std::unique_ptr<Token> tk { new Token { std::stoi ( mBuffer ) } };
            mLeft.push ( std::move ( tk ) );
            mState = state_t::Start;
            return;        
    }
}

void Tokenizer::fractionState () {
    while ( std::isdigit ( mHead ) ) {
        shift ();
    }
    std::unique_ptr<Token> tk { new Token { std::stod ( mBuffer ) } };
    mLeft.push ( std::move ( tk ) );
    mState = state_t::Start; 
}


void Tokenizer::double1State () {
    shift ();
    if ( std::isdigit ( mHead ) ) {
        mState = state_t::Fraction; 
    } else {
        std::unique_ptr<Token> tk { new Token { std::stod ( mBuffer ) } };
        mLeft.push ( std::move ( tk ) );
        mState = state_t::Start; 
    }
}

void Tokenizer::double2State () {
    shift ();
    if ( std::isdigit ( mHead ) ) {
        mState = state_t::Fraction; 
    } else {
        std::cerr<<"Error while tokenizing double: no digit after '.' symbol."<<std::endl;
        mState = state_t::Err;
    }
}

void Tokenizer::wordState () {
    while ( std::isalpha ( mHead ) ) {
        shift ();
    }
    std::unique_ptr<Token> tk { new Token { mBuffer, tk_t::Word } };
    mLeft.push ( std::move ( tk ) );
    mState = state_t::Start;
}

void Tokenizer::prdsLblState () {
    shift ();
    if ( mHead != 'R' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'O' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'D' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'U' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'C' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'T' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'I' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'O' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'N' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'S' ) {
        mState = state_t::Word;
        shift ();
    } else {
        mState = state_t::Word;
    }
}
void Tokenizer::endLblState () {
    shift ();
    if ( mHead != 'N' ) {
        mState = state_t::Word;
        shift ();
    } else if ( mHead != 'D' ) {
        mState = state_t::Word;
        shift ();
    } else {
        mState = state_t::Word;
    }
}

void Tokenizer::cndOp1_1State () {
    shift ();
    if ( mHead == '=' ) {
        mState = state_t::CndOp_2;
    } else {
        mState = state_t::Start;
        std::unique_ptr<Token> tk { new Token { mBuffer, tk_t::CndOp } };
        mLeft.push ( std::move ( tk ) );
    }
}

void Tokenizer::cndOp2_1State () {
    shift ();
    if ( mHead == '=' ) {
        mState = state_t::CndOp_2;
    } else {
        mState = state_t::Err;
    }
}

void Tokenizer::cndOp_2State () {
    std::unique_ptr<Token> tk { new Token { mBuffer, tk_t::CndOp } };
    mLeft.push ( std::move ( tk ) );
    mState = state_t::Start;
    shift ();
}

void Tokenizer::prdEquLblState () {
    shift ();
    if ( mHead == '=' ) {
        std::unique_ptr<Token> tk { new Token { tk_t::PrdEquLbl } };
        mLeft.push ( std::move ( tk ) );
        mState = state_t::Start;
        shift ();
    } else {
        std::cerr<<"Error while tokenizing ':=': character ':' must be before '='."<<std::endl;
        mState = state_t::Err; 
    }
}

void Tokenizer::semiColonState () {
    std::unique_ptr<Token> tk { new Token { tk_t::SemiColon } };
    mLeft.push ( std::move ( tk ) );
    mState = state_t::Start;
    shift ();
}

void Tokenizer::commaState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Comma } };
    mLeft.push ( std::move ( tk ) );
    mState = state_t::Start;
    shift ();
}

void Tokenizer::opnSqrBrkState () {
    std::unique_ptr<Token> tk { new Token { tk_t::OpnSqrBrk } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::clsSqrBrkState () {
    std::unique_ptr<Token> tk { new Token { tk_t::ClsSqrBrk } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::opnRndBrkState () {
    std::unique_ptr<Token> tk { new Token { tk_t::OpnRndBrk } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::clsRndBrkState () {
    std::unique_ptr<Token> tk { new Token { tk_t::ClsRndBrk } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::andState () {
    std::unique_ptr<Token> tk { new Token { tk_t::And } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::orState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Or } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::percentState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Percent } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::plusState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Plus } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::minState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Min } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::mulState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Mul } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::divState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Div } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::powState () {
    std::unique_ptr<Token> tk { new Token { tk_t::Pow } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::powRtState () {
    std::unique_ptr<Token> tk { new Token { tk_t::PowRt } };
    mLeft.push ( std::move ( tk ) );
	mState = state_t::Start;
	shift ();
}

void Tokenizer::tokenize () {
    do { 
        switch ( mState ) {
            case state_t::Start: setState (); break;
            case state_t::Int: intState (); break;
            case state_t::Double1: double1State (); break;
            case state_t::Double2: double2State (); break;
            case state_t::Fraction: fractionState (); break;
            case state_t::Word: wordState (); break;
            case state_t::CndOp1_1: cndOp1_1State (); break;
            case state_t::CndOp2_1: cndOp2_1State (); break;
            case state_t::CndOp_2: cndOp_2State (); break;
            case state_t::PrdEquLbl: prdEquLblState (); break;
            case state_t::SemiColon: semiColonState (); break;
            case state_t::OpnSqrBrk: opnSqrBrkState (); break;
            case state_t::ClsSqrBrk: clsSqrBrkState (); break;
            case state_t::OpnRndBrk: opnRndBrkState (); break;
            case state_t::ClsRndBrk: clsRndBrkState (); break;
            case state_t::And: andState (); break;
            case state_t::Or: orState (); break;
            case state_t::Percent: percentState (); break;
            case state_t::Plus: plusState (); break;
            case state_t::Min: minState (); break;
            case state_t::Mul: mulState (); break;
            case state_t::Div: divState (); break;
            case state_t::Pow: powState (); break;
            case state_t::PowRt: powRtState (); break;
            case state_t::Err: errState ();
            default: break;
        }
        if ( mState == state_t::Start ) {
            mBuffer.clear ();
        }
    } while ( mState != state_t::End );
}
