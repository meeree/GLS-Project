#ifndef _TURTLE__H_INCLUDED__
#define _TURTLE__H_INCLUDED__

#include <vector>
#include <stack>

class Turtle {
private:
   std::stack<std::vector<double> > mPositionStack;
   std::stack<std::vector<double> > mOrientationStack;
   std::stack<unsigned> mPopStack;
   double mGirth;
public:
   Turtle ( std::vector<double> const &position, std::vector<double> const &orientation, double const &girth=1.0 );
   void move ( double const &distance );
   void rotateX ( double const &theta );
   void rotateY ( double const &theta );
   void rotateZ ( double const &theta );
   void width ( double const &girth );
   void push ();
   void pop ();
};

#endif
