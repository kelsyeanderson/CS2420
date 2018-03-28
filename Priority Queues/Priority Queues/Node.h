
#ifndef NODE_H
#define NODE_H
class Node
{
public:
    ItemType element;
    Node* left;
    Node* right;
    int nullHeight;
    
    Node( ItemType e, Node *l = NULL, Node *r = NULL, int h = 0 ) :
    element( e ), left( l ), right( r ), nullHeight( h ) {}
    virtual std::string toString() {
        std::stringstream out;
        out << element.toString();
        if (left!=NULL) out << "[l:" << left->element.priority<< "]";
        if (right!=NULL) out << "[r:" << right->element.priority<< "]";
        return out.str();
    }
    virtual std::string toStringShort() { return element.word;}
};
#endif
