#include <string>
#include <vector>

class Symbol {
protected:
   std::string mName;
   std::vector<double> mParams;
public:
   Symbol (std::string const &name, std::vector<double> const &params) : 
      mName {name},
      mParams {params}
   {}

   std::vector<double> getParams () const {return mParams};
   std::string getName () const {return mName};
   void setParams (std::vector<double> const &newParams);

};

class Token {
protected:
   enum token_type_t {
      CHARACTER,
      NUMBER,
      SYMBOL
   }

   token_type_t mType;



};

class Tokenizer {
private:
   std::vector<Symbol> symbolTable,
                       axiom;
   std::vector<Token> 

};
