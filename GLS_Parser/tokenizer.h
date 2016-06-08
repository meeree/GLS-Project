#include <stack>
#include <fstream>
#include <memory>

enum class state_t {
    Start, End, Err,
    Int, Fraction, Zero, 
    Double1, Double2,
    Word, 
    PrdsLbl, EndLbl, 
    CndOp1_1, CndOp2_1, CndOp_2,
    PrdEquLbl,
    SemiColon, Comma,
    OpnSqrBrk, ClsSqrBrk, OpnRndBrk, ClsRndBrk,
    And, Or, Percent,
    Plus, Min, Mul, Div, Pow, PowRt
};

class Token;

class Tokenizer {
private:
    std::ifstream& mRight;  
    state_t mState;
    char mHead;
    std::stack<std::unique_ptr<Token>> mLeft; 
    std::string mBuffer;

    unsigned mHoriPos;
    unsigned mVertPos;

    void shift ();
    void setState ();

    void errState ();
    void intState ();
    void fractionState ();
    void zeroState ();
    void double1State ();
    void double2State ();
    void wordState ();
    void prdsLblState ();
    void endLblState ();
    void cndOp1_1State ();
    void cndOp2_1State ();
    void cndOp_2State ();
    void prdEquLblState ();
    void semiColonState ();
    void commaState ();
    void opnSqrBrkState ();
    void clsSqrBrkState ();
    void opnRndBrkState ();
    void clsRndBrkState ();
    void andState ();
    void orState ();
    void percentState ();
    void plusState ();
    void minState ();
    void mulState ();
    void divState ();
    void powState ();
    void powRtState ();
    void periodState ();

public:
    Tokenizer ( std::ifstream& right );
    void tokenize ();
};
