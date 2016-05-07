std::string const &Token::getOperator () const {
   throw "not an operator token";
   exit ( EXIT_FAILURE );
}
std::string const &Token::getCondition () const {
   throw "not a condition token";
   exit ( EXIT_FAILURE );
}
int const &Token::getInt () const {
   throw "not an int token";
   exit ( EXIT_FAILURE );
}
double const &Token::getFloat () const {
   throw "not a float token";
   exit ( EXIT_FAILURE );
}


bool Token::isOperator () const {
   return false;
}
bool Token::isCondition () const;
   return false;
}
bool Token::isInt () const;
   return false;
}
bool Token::isFloat () const;
   return false;
}

OperatorToken::OperatorToken ( std::string const &token ) : mToken { token } {
}
std::string const &OperatorToken::getOperator () const {
   return mToken; 
}
bool OperatorToken::isOperator () const {
   return true;
}

ConditionToken::ConditionToken ( std::string const &token ) : mToken { token } {
}
std::string const &ConditionToken::getCondition () const {
   return mToken; 
}
bool ConditionToken::isCondition () const {
   return true;
}

IntToken::IntToken ( int const &token ) : mToken { token } {
}
int const &IntToken::getInt () const {
   return mToken; 
}
double &IntToken::getFloat () const { 
   return (double)mToken;
}
bool IntToken::isInt () const {
   return true;
}

FloatToken::FloatToken ( double const &token ) : mToken { token } {
}
double const &FloatToken::getFloat () const {
   return mToken; 
}
int &FloatToken::getInt () const { 
   return (int)mToken;
}
bool FloatToken::isFloat () const {
   return true;
}
