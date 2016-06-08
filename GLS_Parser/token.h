#include <string> 

enum class tk_t {
    Double, Int, Word, CndOp, 
    PrdEquLbl, SemiColon, Comma,
    OpnSqrBrk, ClsSqrBrk, OpnRndBrk, ClsRndBrk,
    And, Or, Percent,
    Plus, Min, Mul, Div, Pow, PowRt
};

class Token {
private:
    union Storage {
        Storage () = default;
        ~Storage ();
        
        int* mIntPtr;
        double* mDblPtr;
        std::string* mStrPtr;

        Storage ( int const& cpyInt );
        Storage ( double const& cpyDbl );
        Storage ( std::string const& cpyStr );
    } mStorage;

public:
    tk_t mType;
    
    Token () = default;
    ~Token ();
    // no copy assignment or construction because that would
    // copy the pointers in storage. 
    Token ( Token const& ) = delete;
    Token& operator = ( Token const& ) = delete;

    Token ( tk_t const& type );
    tk_t const& getType () const;

    Token ( int const& cpyInt );
    int const& getInt () const;

    Token ( double const& cpyDbl );
    double const& getDouble () const;

    //we need to take type in string constructor because that is how 
    //we will store both words and conditions 
    Token ( std::string const& cpyStr, tk_t const& type );
    std::string const& getString () const;
};
