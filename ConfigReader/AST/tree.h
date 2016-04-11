#include <iostream>
#include <string>

class Tree {
protected:
   enum return_type_t {
      FLOAT, INT, STRING, BOOL
   } mReturnType;

   Tree ( return_type_t const returnType ) : mReturnType { returnType } { }
public:
   virtual double outputFloat ( ) const { std::cout<<"Output Error: No float output"<<std::endl; exit( EXIT_FAILURE ); }    
   virtual int outputInt ( ) const { std::cout<<"Output Error: No int output"<<std::endl; exit( EXIT_FAILURE ); }    
   virtual std::string outputString ( ) const { std::cout<<"Output Error: No string output"<<std::endl; exit( EXIT_FAILURE ); }    
   virtual bool outputBool ( ) const { std::cout<<"Output Error: No bool output"<<std::endl; exit( EXIT_FAILURE ); }    

   bool returnsFloat ( ) const { return mReturnType == FLOAT; } 
   bool returnsInt ( ) const { return mReturnType == INT; } 
   bool returnsString ( ) const { return mReturnType == STRING; } 
   bool returnsBool ( ) const { return mReturnType == BOOL; } 
};

//Value Trees

class FloatTree : public Tree {
private:
   double mFloat;
public:
   FloatTree ( double const &floatValue ) : mFloat { floatValue }, Tree ( FLOAT ) { }
   double outputFloat ( ) const { return mFloat; }
};

class IntTree : public Tree {
private:
   int mInt;
public:
   IntTree ( int const &intValue ) : mInt { intValue }, Tree ( INT ) { }
   int outputInt ( ) const { return mInt; }
};

class StringTree : public Tree {
private:
   std::string mString;
public:
   StringTree ( std::string const &stringValue ) : mString { stringValue }, Tree ( STRING ) { }
   std::string outputString ( ) const { return mString; }
};

class BoolTree : public Tree {
private:
   bool mBool;
public:
   BoolTree ( bool const &boolValue ) : mBool { boolValue }, Tree ( BOOL ) { }
   bool outputBool ( ) const { return mBool; }
};

//

//BinaryTree

class BinaryTree : public Tree {
protected:
   Tree * mLeft;
   Tree * mRight;

   BinaryTree ( Tree * const &left, Tree * const &right, return_type_t const &returnType ) : mLeft { left }, mRight { right }, Tree ( returnType ) { }
};

class LogicTree : public BinaryTree {
protected:
   LogicTree ( Tree* const &left, Tree * const &right ) : BinaryTree ( left, right, BOOL ) { }
};

class Equal : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputBool( ) == mRight->outputBool( ) ) { return true; } return false; }
};

class NotEqual : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputBool( ) != mRight->outputBool( ) ) { return true; } return false; }
};

class And : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputBool( ) && mRight->outputBool( ) ) { return true; } return false; }
};

class Or : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputBool( ) || mRight->outputBool( ) ) { return true; } return false; }
};

class GreaterThan : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputFloat( ) > mRight->outputFloat( ) ) { return true; } return false; }
};

class LessThan : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputFloat( ) < mRight->outputFloat( ) ) { return true; } return false; }
};

class GreaterThanOrEqual : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputFloat( ) >= mRight->outputFloat( ) ) { return true; } return false; }
};

class LessThanOrEqual : public LogicTree {
public:
   bool outputBool ( ) const { if ( mLeft->outputFloat( ) <= mRight->outputFloat( ) ) { return true; } return false; }
};

////TernaryTree

class TernaryTree : public Tree {
protected:
   Tree * mLeft;
   Tree * mMiddle;
   Tree * mRight;

   TernaryTree ( Tree * const &left, Tree * const &middle, Tree * const &right, return_type_t const &returnType ) : mLeft { left }, mMiddle { middle }, mRight { right }, Tree ( returnType ) { }
};

class FloatITE : public TernaryTree {
public:
   FloatITE ( Tree * const &left, Tree * const &middle, Tree * const &right ) : TernaryTree ( left, middle, right, FLOAT ) { }
   double outputFloat ( ) const { if ( mLeft->outputBool( ) ) { return mMiddle->outputFloat( ); } return mRight->outputFloat( ); }
};

class IntITE : public TernaryTree {
public:
   IntITE ( Tree * const &left, Tree * const &middle, Tree * const &right ) : TernaryTree ( left, middle, right, INT ) { }
   int outputInt ( ) const { if ( mLeft->outputBool( ) ) { return mMiddle->outputInt( ); } return mRight->outputInt( ); }
};

class StringITE : public TernaryTree {
public:
   StringITE ( Tree * const &left, Tree * const &middle, Tree * const &right ) : TernaryTree ( left, middle, right, STRING ) { }
   std::string outputString ( ) const { if ( mLeft->outputBool( ) ) { return mMiddle->outputString( ); } return mRight->outputString( ); }
};

class BoolITE : public TernaryTree {
public:
   BoolITE ( Tree * const &left, Tree * const &middle, Tree * const &right ) : TernaryTree ( left, middle, right, BOOL ) { }
   bool outputBool ( ) const { if ( mLeft->outputBool( ) ) { return mMiddle->outputBool( ); } return mRight->outputBool( ); }
};

//
