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
   Tree * &parseProduction ( std::vector<Token*> const &tokenString ) const;
   Tree * &addExpr ( std::vector<Token*>::iterator const &iter ) const;
   Tree * &mulExpr ( std::vector<Token*>::iterator const &iter ) const;
   Tree * &powExpr ( std::vector<Token*>::iterator const &iter ) const;
   Tree * &brackExpr ( std::vector<Token*>::iterator const &iter ) const;
   Tree * &staticNumExpr ( std::vector<Token*>::iterator const &iter ) const;
   Tree * &dynamicNumExpr ( std::vector<Token*>::iterator const &iter ) const;

};
