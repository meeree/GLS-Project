#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

#include "../Value/value.h"
#include <vector>

class Symbol;

class Node { 
protected:
   Node () = default;
public:
   virtual Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym ) = 0;
};

class SaveNode : public Node {
protected:
   Value mValue;
   SaveNode () = default;
   SaveNode ( Value const &val );
   SaveNode ( Value::value_type_t const &valueType );
};

class ValueNode : public SaveNode {
public:
   ValueNode () = delete;
   ValueNode ( Value const &val );
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};

class SimpleNode : public Node {
public:
   SimpleNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};

class LookupNode : public SaveNode {
public:
   LookupNode ();
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};

class AccumulateNode : public SaveNode {
public:
   AccumulateNode ();
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};

class SymbolNode : public SaveNode {
public:
   SymbolNode ();
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};

class ArithNode : public SaveNode {
protected:
   ArithNode ();
};

class PlusNode : public ArithNode {
public:
   PlusNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class MinusNode : public ArithNode {
public:
   MinusNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class MulNode : public ArithNode {
public:
   MulNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class DivNode : public ArithNode {
public:
   DivNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class PowNode : public ArithNode {
public:
   PowNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class PowRootNode : public ArithNode {
public:
   PowRootNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};

class LogicNode : public SaveNode {
protected:
   LogicNode ();
};

class LessNode : public LogicNode {
public:
   LessNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class GreaterNode : public LogicNode {
public:
   GreaterNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class LessEqualNode : public LogicNode {
public:
   LessEqualNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class GreaterEqualNode : public LogicNode {
public:
   GreaterEqualNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class EqualNode : public LogicNode {
public:
   EqualNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};
class NotEqualNode : public LogicNode {
public:
   NotEqualNode () = default;
   Value evalNode ( std::vector<Value > const &inVec, Symbol const &sym );
};

#endif
