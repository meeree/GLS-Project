#ifndef map
#include <map>
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
public:
   ~Parser ();
   Tree * parseProduction ( std::vector<Token> &tokenString ) const;
   Tree * andExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * cndExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * stringExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * addExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * mulExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * powExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * brackExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * staticNumExpr ( std::vector<Token>::iterator &iter ) const;
   Tree * dynamicNumExpr ( std::vector<Token>::iterator &iter ) const;
};
