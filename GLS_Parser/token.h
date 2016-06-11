#include <string> 
#include <map>

class Token {
public:
    Token () = default;
    ~Token ();

    void error () const;

    enum class type_t {
        DOUBLE, INT, WORD, SYMBOL
    };

    /* no copy assignment or construction because that would
       copy the pointers in storage. */
    Token ( Token const& ) = delete;
    Token& operator = ( Token const& ) = delete;

    Token ( type_t const& type );
    bool isInt () const;
    bool isDouble () const;
    bool isWord () const;
    bool isSymbol () const;

    Token ( int const& cpyInt );
    int const& getInt () const;

    Token ( double const& cpyDbl );
    double const& getDouble () const;

    /* we need to take type in string constructor because that is how 
       we will store both words and symbols */
    Token ( std::string const& cpyStr, type_t const& type );
    std::string const& getSymbol () const;
    std::string const& getWord () const;

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

    type_t mType;

    static std::map<type_t, std::string> mTypeStrMap;
};
