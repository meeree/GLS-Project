#ifndef vector
#include <vector>
#endif
#ifndef string
#include <string>
#endif

class Symbol;
class Value;

class MemoryUnit {
private:
   std::vector<Symbol> mString;
   Symbol mSymbol;
public:
   MemoryUnit ();
   void setString ( std::vector<Symbol> const &newString );
   void pushString ( Symbol const &pushSymbol );
   void setSymbol ( Symbol const &newSymbol );
   Value lookupParam ( std::string const &paramName ) const;
   std::vector<Symbol> const &getString () const;
   Symbol const &getSymbol () const;
};
