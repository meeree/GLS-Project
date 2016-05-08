#ifndef vector
#include <vector>
#endif
#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif

class Node { 
public:
   Node ();
   virtual ~Node ();
   virtual Value evalNode ( std::vector<Value > const &inVec ) const = 0;
};

class ValueNode : public Node {
private:
   Value mValue;
public:
   ValueNode ( Value const &valuePtr );
   Value evalNode ( std::vector<Value > const &inVec ) const;
};

class SimpleNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};

class ArithNode : public Node {
protected:
   bool intCheck ( std::vector<Value> const &inVec ) const;
};
class PlusNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class MinusNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class MulNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class DivNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class PowNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class PowRootNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};

class LessNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class GreaterNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class LessEqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class GreaterEqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class EqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
class NotEqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec ) const;
};
