#include "token.h"

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
        case tk_t::Int: delete mStorage.mIntPtr; return;
        case tk_t::Double: delete mStorage.mDblPtr; return;
        case tk_t::Word: delete mStorage.mStrPtr; return;
        case tk_t::CndOp: delete mStorage.mStrPtr; return;
        default: return;
    }
}

Token::Token ( tk_t const& type ) : mType { type } {
}
tk_t const& Token::getType () const {
    return mType;
}

Token::Token ( int const& cpyInt ) : mStorage { cpyInt }, mType { tk_t::Int } {
}
int const& Token::getInt () const {
    return *mStorage.mIntPtr;
}

Token::Token ( double const& cpyDbl ) : mStorage { cpyDbl }, mType { tk_t::Double } {
}
double const& Token::getDouble () const {
    return *mStorage.mDblPtr;
}

Token::Token ( std::string const& cpyStr, tk_t const& type ) : mStorage { cpyStr }, mType { type } {
}
std::string const& Token::getString () const {
    return *mStorage.mStrPtr;
}
