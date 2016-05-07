#ifndef string
#include <string>
#endif

class Token {
public:
   virtual std::string const &getOperator () const;
   virtual std::string const &getCondition () const;
   virtual int const &getInt () const;
   virtual double const &getFloat () const;
   
   virtual bool isOperator () const;
   virtual bool isCondition () const;
   virtual bool isInt () const;
   virtual bool isFloat () const;
};

class OperatorToken : public Token {
private:
   std::string mToken;
public:
   OperatorToken ( std::string const &token );
   std::string const &getOperator () const;
   bool isOperator () const;
};

class ConditionToken : public Token {
private:
   std::string mToken;
public:
   ConditionToken ( std::string const &token );
   std::string const &getCondition () const;
   bool isCondition () const;
};

class IntToken : public Token {
private:
   int mToken;
public:
   IntToken ( int const &token );
   int const &getInt () const;
   double const &getFloat () const;
   bool isInt () const;
};

class FloatToken : public Token {
private:
   double mToken;
public:
   FloatToken ( double const &token );
   double const &getFloat () const;
   int const &getInt () const;
   bool isFloat () const;
};
