Node::Node () {
}
Node::~Node () {
}

ValueNode::ValueNode ( Value * const &valuePtr ) : mValue { valuePtr } {
}
ValueNode::~ValueNode () {
   delete mValue;
}
Value * ValueNode::evalNode ( std::vector<Value * > const &inVec ) const {
   return mValue;
}

bool ArithNode::intCheck ( std::vector<Value*> const &inVec ) const {
   //IS INT METHOD VALUE
   for ( auto const &iVal: inVec ) {
      if ( !iVal->isInt () ) {
         return false;
      }
   }
   return true;
}
Value * PlusNode::evalNode ( std::vector<Value * > const &inVec ) const { 
   if ( intCheck ( inVec ) ) {
      return inVec[0]->getInt () + inVec[1]->getInt ();
   }
   // AUTOMATIC CONVERSION IN VALUE FROM INT TO FLOAT AND BACKWARDS
   return inVec[0]->getFloat /* */t () + inVec[1]->getFloat ();
}
Value * MinusNode::evalNode ( std::vector<Value * > const &inVec ) const { 
   if ( intCheck ( inVec ) ) {
      return inVec[0]->getInt () - inVec[1]->getInt ();
   }
   return inVec[0]->getFloat () - inVec[1]->getFloat ();
}
Value * MulNode::evalNode ( std::vector<Value * > const &inVec ) const { 
   if ( intCheck ( inVec ) ) {
      return inVec[0]->getInt () * inVec[1]->getInt ();
   }
   return inVec[0]->getFloat () * inVec[1]->getFloat ();
}
Value * DivNode::evalNode ( std::vector<Value * > const &inVec ) const { 
   if ( intCheck ( inVec ) ) {
      return inVec[0]->getInt () / inVec[1]->getInt ();
   }
   return inVec[0]->getFloat () / inVec[1]->getFloat ();
}
Value * PowNode::evalNode ( std::vector<Value * > const &inVec ) const { 
   if ( intCheck ( inVec ) ) {
      return pow ( inVec[0]->getInt (), inVec[1]->getInt () );
   }
   return pow ( inVec[0]->getFloat (), inVec[1]->getFloat () );
}
Value * PowRootNode::evalNode ( std::vector<Value * > const &inVec ) const { 
   if ( intCheck ( inVec ) ) {
      return pow ( inVec[0]->getInt (), 1.0/inVec[1]->getInt () );
   }
   return pow ( inVec[0]->getFloat (), 1.0/inVec[1]->getFloat () );
}

Value * LessNode::evalNode ( std::vector<Value * > const &inVec ) const {
   return inVec[0]->getFloat () < inVec[1]->getFloat ();
}
Value * GreaterNode::evalNode ( std::vector<Value * > const &inVec ) const {
   return inVec[0]->getFloat () > inVec[1]->getFloat ();
}
Value * LessEqualNode::evalNode ( std::vector<Value * > const &inVec ) const {
   return inVec[0]->getFloat () <= inVec[1]->getFloat ();
}
Value * GreaterEqualNode::evalNode ( std::vector<Value * > const &inVec ) const {
   return inVec[0]->getFloat () >= inVec[1]->getFloat ();
}
class EqualNode : public Node {
public:
   Value * evalNode ( std::vector<Value * > const &inVec ) const;
};
class NotEqualNode : public Node {
public:
   Value * evalNode ( std::vector<Value * > const &inVec ) const;
};
