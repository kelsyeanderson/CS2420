//
//  LeftistHeap.hpp
//  Priority Queues
//
//  Created by Kelsye Anderson on 3/27/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef LeftistHeap_hpp
#define LeftistHeap_hpp

#include <string>
#include <algorithm>
#include "ItemType.h"
#include "Node.h"

class LeftistHeap
{
public:
    int size = 0;
    Node* getMin() {return m_root;}; //returns the pointer to the min ItemType in heap
    void insert(ItemType input); //inserts an item into the tree
    ItemType removeMin(); //removes the root from the tree
    void merge(Node* heap2); //helper function for merging 2 Leftist heaps
    void toString()  {toString(m_root," ",0);}; //helper function for to String. Use at your own risk
    void toString(Node* ptr, std::string indent, int currdepth, int depth = std::numeric_limits<int>::max()); //outputs Leftist Heap
    
private:
    Node* m_root = nullptr;
    
    void setAllNullHeight(); //calls the overided setAllNullHeight with the root
    void setAllNullHeight(Node* & ptr); //recursive function to set all null heights
    Node* merge(Node* &heap1, Node* &heap2); // merges two heaps together
    bool notLeftist(Node* ptr); //returns true if not a leftist heap
};

/*helper function for other setAllNullHeight function. Checks if root is null*/
void LeftistHeap::setAllNullHeight()
{
    if(m_root != nullptr)
    {
        setAllNullHeight(m_root);
    }
};

/*recursively goes through the leftist heap and sets the nullHeight for every node*/
void LeftistHeap::setAllNullHeight(Node* & ptr)
{
    if(ptr == nullptr)
    {
        return;
    }
    if (ptr->left == nullptr || ptr->right == nullptr)
    {
        ptr->nullHeight = 0;
    }
    setAllNullHeight(ptr->left);
    setAllNullHeight(ptr->right);
    if (ptr->left != nullptr && ptr->right != nullptr)
    {
        ptr->nullHeight = std::min(ptr->left->nullHeight, ptr->right->nullHeight) + 1;
    }
}

/*inserts the ItemType into the Leftist Heap*/
void LeftistHeap::insert(ItemType input)
{
    size ++;
    Node* temp = new Node(input);
    m_root = merge(temp, m_root);
    setAllNullHeight();
}

///*helper function for merge. Merges current leftist heap with inputed leftist heap*/
//void LeftistHeap::merge(Node* heap2)
//{
//    this->m_root = merge(this->m_root, heap2);
//    setAllNullHeight();
//}

/*Combines two heaps based on which root is smaller*/
Node* LeftistHeap::merge(Node* & heap1, Node* & heap2)
{
    Node* small;
    if (heap1 == nullptr)
    {
        return heap2;
    }
    if (heap2 == nullptr)
    {
        return heap1;
    }
    if (heap1->element.priority < heap2->element.priority)
    {
        heap1->right = merge(heap1->right, heap2);
        small = heap1;
    }
    else
    {
        heap2->right = merge(heap2->right, heap1);
        small = heap2;
    }
    if (notLeftist(small))
    {
        std::swap(small->left,small->right);
    }
    return small;

}


/*returns false if a leftist heap and true if not*/
bool LeftistHeap::notLeftist(Node* ptr)
{
    if (ptr == nullptr)
    {
        return false;
    }
    else if(ptr->left == nullptr && ptr->right == nullptr)
    {
        return false;
    }
    else if (ptr->left != nullptr && ptr->right == nullptr)
    {
        return false;
    }
    else if (ptr->left == nullptr && ptr->right != nullptr)
    {
        return true;
    }
    else if(ptr->left->nullHeight < ptr->right->nullHeight)
    {
        return true;
    }
    
    return notLeftist(ptr->right) && notLeftist(ptr->left);
}

/*merges the left and right child of the root to remove the min*/
ItemType LeftistHeap::removeMin()
{
    size--;
    ItemType temp = m_root->element;
    m_root = merge(m_root->right, m_root->left);
    return temp;
    
}

/*outputs the heap into a string*/
void LeftistHeap::toString(Node* ptr, std::string indent, int currdepth, int depth)
{
    if (ptr != nullptr)// || currdepth > depth
    {
        toString(ptr->right, indent + "  ", currdepth + 1, depth);
        std::cout << indent << ptr->toString() << std::endl;;
        toString(ptr->left, indent + "  ", currdepth + 1, depth);
    }
}





#endif /* LeftistHeap_hpp */
