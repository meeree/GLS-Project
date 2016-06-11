#include <stack>
#include <fstream>
#include <string>
#include <map>
#include <memory>

class Token;

class Tokenizer {
private:
    static std::map<std::pair<unsigned, char>, unsigned> mSymStateTbl;
    unsigned mSymState;

    std::ifstream& mRight;
    std::stack<std::unique_ptr<Token>> mLeft;
    std::string mBuff;
    char mHead;

    unsigned mLnCtr;
    unsigned mVrtCtr;
    
    void error () const;
    void shift ();
    void acceptToken ( std::unique_ptr<Token>& tk );

    void tokenizeWord ();
    void tokenizeDouble ();
    void tokenizeSymbol ();
    void tokenize ();

public:
    Tokenizer ( std::ifstream& right );
    ~Tokenizer ();
    void tokenizeLoop ();
};
