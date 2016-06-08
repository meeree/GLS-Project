#include <memory>

class Token;
class Tokenizer;
class Tree;

class Parser {
private:
    std::unique_ptr<Tree> mTree;
    
    void parseProductions (); 
    void parseProduction (); 
    void parseRule (); 
    void parseProbability ();  
    void parseCnd (); 
    void parseCndSingular (); 
    void parseSymbol ();  
    void parseSymbolWithExpr (); 
    void parseAddExpr ();  
    void parseMulExpr (); 
    void parsePowExpr (); 
    void parseValue (); 
};
