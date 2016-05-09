#ifndef vector
#include <vector>
#endif
#ifndef VALUE_H
#define VALUE_H
#include "value.h"
#endif

class MemoryUnit;

class Node { 
public:
   Node ();
   virtual ~Node ();
   virtual Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const = 0;
};

class ValueNode : public Node {
private:
   Value mValue;
public:
   ValueNode ( Value const &valuePtr );
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};

class SimpleNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};

class LookupNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};

class ArithNode : public Node {
protected:
   bool intCheck ( std::vector<Value> const &inVec ) const;
};

class PlusNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class MinusNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class MulNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class DivNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class PowNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class PowRootNode : public ArithNode {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};

class LessNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class GreaterNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class LessEqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class GreaterEqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class EqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
class NotEqualNode : public Node {
public:
   Value evalNode ( std::vector<Value > const &inVec, MemoryUnit const &mem ) const;
};
