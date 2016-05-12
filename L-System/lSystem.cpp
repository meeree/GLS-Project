#include "lSystem.h"
#include "../ConfigReader/Tree/tree.h"
#include "../ConfigReader/Value/value.h"
#include <iostream>

LSystem::LSystem ( std::vector<Symbol> const &axiom, std::map<SymbolWithoutParams, Tree*, TreeTableCompare> const &treeTable, std::vector<SymbolWithoutParams> const &constants ) : mString1 { axiom }, mTreeTable { treeTable }, mConstants { constants } {
}

bool LSystem::constFill ( Symbol const &sym, std::vector<Symbol> &str2 ) {
   for ( auto const &symW: mConstants ) {
      if ( sym.check ( symW ) ) {
         str2.push_back ( sym );
         return true;
      }
   }
   return false;
}

bool LSystem::variableFill ( Symbol const &sym, std::vector<Symbol> &str2 ) {
   for ( auto const &symTreePair: mTreeTable ) {
      SymbolWithoutParams const &symW = symTreePair.first;
      Tree * const &symTree = symTreePair.second;
      if ( sym.check ( symW ) ) {
         std::vector<Symbol> symStr { ( symTree->evalTree ( sym ) ).getSymbolString () };
         for ( auto const &symPush: symStr ) {
            str2.push_back ( symPush );
         }
         return true;
      }
   }
   return false;
}

void LSystem::updateSpecific ( std::vector<Symbol> const &str1, std::vector<Symbol> &str2 ) {
   for ( auto const &sym: str1 ) {
      if ( constFill ( sym, str2 ) ) {
         continue;
      } else if ( variableFill ( sym, str2 ) ) {
         continue;
      }
      std::cerr<<"undefined variable: "<<sym.getName ()<<" continuing anyways"<<std::endl;
   }
}

void LSystem::update () {
   if ( mString1.size () == 0 ) {
      updateSpecific ( mString2, mString1 );
      mString2.clear ();
      return;
   }

   updateSpecific ( mString1, mString2 );
   mString1.clear ();
}

void LSystem::printString () const {
   for ( auto const &sym: mString2 ) {
      sym.print ();
   }
   for ( auto const &sym: mString1 ) {
      sym.print ();
   }
   std::cout<<std::endl;
}

LSystem::~LSystem () {
//   for ( auto const &iPair: mTreeTable ) {
//      delete iPair.second;
//   }
}
