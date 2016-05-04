class Node {
private:
   Value * const &returnValue;
public:
   virtual Value * const &evaluateNode ( std::vector<Value*> const & ) = 0;
};

class PlusNode : public Node {
   
