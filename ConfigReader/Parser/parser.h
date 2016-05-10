#ifndef map
#include <map>
#endif
#ifndef vector
#include <vector>
#endif
#ifndef utility
#include <utility>
#endif
#ifndef string
#include <string>
#endif

class Tree;
class Token;

struct TreeTableCompare {
   bool operator ()( std::pair<std::string, unsigned> const &key1, std::pair<std::string, unsigned> const &key2 ) const;
};

class Parser {
private:
   std::map<std::pair<std::string, unsigned>, Tree*, TreeTableCompare> mTreeTable;
   std::vector<std::pair<std::string, std::vector<std::string> > > mSymbolTable; 

public:
   Tree * andExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * cndExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * stringExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * addExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * mulExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * powExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * brackExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * staticNumExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * dynamicNumExpr ( std::vector<Token>::iterator &iter ) const;
   Parser () = default;
   void parseSymbolTable ( std::vector<Token> &tokenString );
   Tree * parseProduction ( std::vector<Token> &tokenString );
   ~Parser ();
};
