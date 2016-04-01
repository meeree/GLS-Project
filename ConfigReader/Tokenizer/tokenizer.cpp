#ifndef cassert
#include <cassert>
#endif 

void Symbol::setParams (std::vector<double> const &newParams) {
   assert(mParams.size() == newParams.size());
   for (int i = 0; i < mParams.size(); i++) {
      mParams[i] = newParams[i];
   }
} 
