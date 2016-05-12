#ifndef iostream 
#include <iostream>
#endif
#ifndef LSYSTEM_H
#define LSYSTEM_H
#include "lSystem.h"
#endif
#ifndef TREE_H
#define TREE_H
#include "../ConfigReader/Tree/tree.h"
#endif
#ifndef VALUE_H
#define VALUE_H
#include "../ConfigReader/Value/value.h"
#endif

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
      std::cout<<symW.first<<std::endl;
      Tree * const &symTree = symTreePair.second;
      if ( sym.check ( symW ) ) {
         for ( auto const &symPush: ( symTree->evalTree ( sym ) ).getSymbolString () ) {
            std::cout<<symPush.getName ()<<std::endl;
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
      }
      if ( variableFill ( sym, str2 ) ) {
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
   if ( mString1.size() == 0 ) {
      for ( auto const &sym: mString2 ) {
         std::cout<<sym.getName();
      }
      return;
   } 

   for ( auto const &sym: mString1 ) {
      std::cout<<sym.getName();
   }
}
