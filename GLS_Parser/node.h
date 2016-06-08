
class Value;

class Node {
public:
    Node () = default;
    virtual Value evalNode () const = 0;
};

class ValueNode : public Node {
private:
    Value mValue;
public:
    ValueNode ( Value const& value );
    Value evalNode () const override;
};
