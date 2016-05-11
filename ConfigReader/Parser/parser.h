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
   bool operator ()( std::pair<std::string, std::vector<std::string> > const &sym1, std::pair<std::string, std::vector<std::string> > const &sym2 ) const;
};

class Parser {
private:
   std::vector<Token> mTokenString;
   std::vector<Token>::iterator mIter;

   std::map<std::pair<std::string, std::vector<std::string> >, Tree*, TreeTableCompare> mTreeTable;
   std::vector<std::pair<std::string, std::vector<std::string> > > mConstants; 

   bool strCheck ( std::string const &str ) const;

   void parseAxiom ();
   void parseConstants ();
   void parseVariables ();
   void parseProductions ();

   Tree * andExpr () const;
   Tree * cndExpr () const;
   Tree * stringExpr () const;
   Tree * addExpr () const;
   Tree * mulExpr () const;
   Tree * powExpr () const;
   Tree * brackExpr () const;
   Tree * staticNumExpr () const;
   Tree * dynamicNumExpr () const;

public:
   Parser ( std::vector<Token> const &tokenString );
   ~Parser ();
   void mainParse ();
};
