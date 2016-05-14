#include "turtle.h"
#include <iostream>
#include <cmath>

Turtle::Turtle ( std::vector<double> const &position, std::vector<double> const &orientation, double const &girth ) : mPositionStack {}, mOrientationStack {}, mGirth { girth } {
   if ( position.size () != 3 || orientation.size () != 3 ) {
      std::cerr<<"error in turtle construction: position or orientatin not of size 3"<<std::endl;
      exit ( EXIT_FAILURE );
   }
   mPositionStack.push ( position );
   mOrientationStack.push ( orientation );
}

void Turtle::move ( double const &distance ) {
   std::vector<double> const &posTop { mPositionStack.top () };
   std::vector<double> const &oriTop { mOrientationStack.top () };
   std::vector<double> newPosTop  { posTop.at ( 0 ) * oriTop.at ( 0 ),
                                    posTop.at ( 1 ) * oriTop.at ( 1 ),
                                    posTop.at ( 2 ) * oriTop.at ( 2 ) };
   std::cout<<newPosTop[0]<<','<<newPosTop[1]<<','<<newPosTop[2]<<std::endl;
   mPositionStack.push ( newPosTop );
}

void Turtle::rotateX ( double const &theta ) {
   std::vector<double> const &oriTop { mOrientationStack.top () };
   std::vector<double> const &newOriTop { oriTop.at ( 0 ),
                                          oriTop.at ( 1 ) * cos ( theta ) + oriTop.at ( 2 ) * sin ( theta ),
                                          oriTop.at ( 1 ) * ( -sin ( theta ) ) + oriTop.at ( 2 ) * cos ( theta ) };
   mOrientationStack.push ( newOriTop );
}

void Turtle::rotateY ( double const &theta ) {
   std::vector<double> const &oriTop { mOrientationStack.top () };
   std::vector<double> const &newOriTop { oriTop.at ( 0 ) * cos ( theta ) + oriTop.at ( 2 ) * ( -sin (theta ) ),
                                          oriTop.at ( 1 ),
                                          oriTop.at ( 0 ) * sin ( theta ) + oriTop.at ( 2 ) * cos (theta ) };
   mOrientationStack.push ( newOriTop );
}

void Turtle::rotateZ ( double const &theta ) {
   std::vector<double> const &oriTop { mOrientationStack.top () };
   std::vector<double> const &newOriTop { oriTop.at ( 0 ) * cos ( theta ) + oriTop.at ( 1 ) * sin (theta ),
                                          oriTop.at ( 0 ) * ( -sin ( theta ) ) + oriTop.at ( 1 ) * cos (theta ),
                                          oriTop.at ( 2 ) };
   mOrientationStack.push ( newOriTop );
}

void Turtle::width ( double const &girth ) {
   mGirth = girth;
}

void Turtle::push () {
   mPopStack.push ( mPositionStack.size () );
   mPopStack.push ( mOrientationStack.size () );
}

void Turtle::pop () {
   unsigned const &prevOriIndex { mPopStack.top () };
   for ( int i = 0; i < prevOriIndex - mOrientationStack.size (); ++i ) {
      mOrientationStack.pop ();
   }
   mPopStack.pop ();

   unsigned const &prevPosIndex { mPopStack.top () };
   for ( int i = 0; i < prevPosIndex - mPositionStack.size (); ++i ) {
      mPositionStack.pop ();
   }
   mPopStack.pop ();
}
