#include <string>
#include <vector>
#include <fstream>
#include <iostream>

//class Symbol {
//private:
//   std::string mName;
//   std::vector<double> mParams;
//
//public:
//   Symbol (std::string const &name, std::vector<double> const &params) : 
//      mName {name},
//      mParams {params}
//   {}
//
//   std::vector<double> getParams () const { return mParams; };
//   std::string getName () const { return mName; };
//   void setParams (std::vector<double> const &newParams);
//
//};

class Token {
protected:
   union typeStorage {
      typeStorage () {}
      void setVal (int * const &intPtr) {mInt = intPtr; }
      void setVal (double * const &floatPtr) {mFloat = floatPtr; }
      void setVal (std::unique_ptr<std::string> const &stringPtr) {mString = stringPtr; }
      int * mInt;
      double * mFloat;
      std::unique_ptr<std::string> mString;
   } mTypeStorage;
   //ADD DESTRUCTOR
   
   enum token_type_t {
      INT,
      FLOAT,
      IDENTIFIER,
      OPERATOR,
      CONDITION
   };

   token_type_t mType;

public:
   Token (token_type_t const &type, int * const &intPtr) : mType { type } { mTypeStorage.setVal (intPtr); }
   Token (token_type_t const &type, double * const &floatPtr) : mType { type } { mTypeStorage.setVal (floatPtr); }
   Token (token_type_t const &type, std::unique_ptr<std::string> const &stringPtr) : mType { type } { mTypeStorage.setVal (stringPtr); }
};

class IntToken : public Token {
public:
   IntToken (int * const &intPtr) : Token (INT, intPtr) {}
   int * getData () const { return mTypeStorage.mInt; }
};

class FloatToken : public Token {
public:
   FloatToken (double * const &floatPtr) : Token (FLOAT, floatPtr) {}
   double * getData () const { return mTypeStorage.mFloat; }
};

class IdentifierToken : public Token {
public:
   IdentifierToken (std::unique_ptr<std::string> const &stringPtr) : Token (IDENTIFIER, stringPtr) {}
   std::unique_ptr<std::string> getData () const { return mTypeStorage.mString; }
   ~IdentifierToken () { std::cout<<"deleting more pointers :)"<<std::endl; delete mTypeStorage.mString; }
};

class OperatorToken : public Token {
public:
   OperatorToken (std::unique_ptr<std::string> const &stringPtr) : Token (OPERATOR, stringPtr) {}
   std::unique_ptr<std::string> getData () const { return mTypeStorage.mString; }
};

class ConditionToken : public Token {
public:
   ConditionToken (std::unique_ptr<std::string> const &stringPtr) : Token (CONDITION, stringPtr) {}
   std::unique_ptr<std::string> getData () const { return mTypeStorage.mString; }
};

typedef std::vector<Token*> GLSstring;

class Tokenizer {
private:
   GLSstring mAxiom; 
   std::vector<GLSstring> mProductions;

   GLSstring readAxiom ( std::ifstream &configFile );
   std::vector<GLSstring> readProductions ( std::ifstream &configFile );

public:
   Tokenizer ( std::ifstream &configFile ) : mAxiom {readAxiom (configFile)}, mProductions {readProductions (configFile)} {}
   std::vector<GLSstring> getProductions () const { return mProductions; }
   GLSstring getAxiom () const { return mAxiom; }
   ~Tokenizer ();
};
