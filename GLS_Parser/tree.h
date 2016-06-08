#include <memory>
#include <vector>

class Node;
class Value;

class Tree {
protected:
    std::unique_ptr<Node> mRoot;
    std::vector<Tree> mChildren; 
public:
    virtual Value evalTree () const = 0;
};
