#include "token.h"
#include <iostream>

std::map<Token::type_t, std::string> Token::mTypeStrMap {
    {Token::type_t::DOUBLE, "double"},
    {Token::type_t::INT, "int"},
    {Token::type_t::WORD, "word"},
    {Token::type_t::SYMBOL, "symbol"}
};

Token::Storage::~Storage () {
}

Token::Storage::Storage ( int const& cpyInt ) : mIntPtr { new int { cpyInt } } {
}
Token::Storage::Storage ( double const& cpyDbl ) : mDblPtr { new double { cpyDbl } } {
}
Token::Storage::Storage ( std::string const& cpyStr ) : mStrPtr { new std::string { cpyStr } } {
}

Token::~Token () {
    switch ( mType ) {
        case type_t::INT: delete mStorage.mIntPtr; return;
        case type_t::DOUBLE: delete mStorage.mDblPtr; return;
        case type_t::WORD: delete mStorage.mStrPtr; return;
        case type_t::SYMBOL: delete mStorage.mStrPtr; return;
    }
}

void Token::error () const {
    std::cerr<<"Exiting in token of type "<<mTypeStrMap[mType]<<"."<<std::endl;
    exit ( EXIT_FAILURE );
}


Token::Token ( type_t const& type ) : mType { type } {
}

bool Token::isInt () const {
    return mType == type_t::INT;
}
bool Token::isDouble () const {
    return mType == type_t::DOUBLE;
}
bool Token::isWord () const {
    return mType == type_t::WORD ;
}
bool Token::isSymbol () const {
    return mType == type_t::SYMBOL ;
}

Token::Token ( int const& cpyInt ) : mStorage { cpyInt }, mType { type_t::INT } {
}
int const& Token::getInt () const {
    if ( isInt () ) {
        return *mStorage.mIntPtr;
    }
    std::cerr<<"Call to getInt in non-int token."<<std::endl;
    error ();
}

Token::Token ( double const& cpyDbl ) : mStorage { cpyDbl }, mType { type_t::DOUBLE } {
}
double const& Token::getDouble () const {
    if ( isDouble () ) {
        return *mStorage.mDblPtr;
    }
    std::cerr<<"Call to getDouble in non-double token."<<std::endl;
    error ();
}

Token::Token ( std::string const& cpyStr, type_t const& type ) : mStorage { cpyStr }, mType { type } {
    if ( mType != type_t::WORD && mType != type_t::SYMBOL ) {
        std::cerr<<"Attempt to initalize token with string but wrong type; tokens containing a string must be of type word or symbol."<<std::endl;
        error ();
    }
}
std::string const& Token::getSymbol () const {
    if ( isSymbol () ) {
        return *mStorage.mStrPtr;
    }
    std::cerr<<"Call to getSymbol in non-symbol token."<<std::endl;
    error ();
}
std::string const& Token::getWord () const {
    if ( isWord () ) {
        return *mStorage.mStrPtr;
    }
    std::cerr<<"Call to getWord in non-word token."<<std::endl;
    error ();
}
