#include "compare.h"
#include <iostream>

bool TreeTableCompare::operator ()( SymbolWithoutParams const &sym1, SymbolWithoutParams const &sym2 ) const {
   std::string const &name1 { sym1.first };
   std::string const &name2 { sym2.first };
   std::vector<std::string> const &params1 { sym1.second };
   std::vector<std::string> const &params2 { sym2.second };

   if ( name1 == name2 && params1 == params2 ) {
      std::cerr<<"function "+name1+" defined twice with same number of parameters "<<std::endl;
      exit ( EXIT_FAILURE );
   }
   if ( params1.size() == params2.size() ) {
      return true;
   }
   return params1.size () < params2.size ();
}
