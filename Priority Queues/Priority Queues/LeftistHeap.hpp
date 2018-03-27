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
#include "ItemType.h"


class LeftistHeap
{
public:
    ItemType getMin() {return m_root;}; //returns the pointer to the min ItemType in heap
    void insert(ItemType input); //inserts an item into the tree
    Node* merge(Node* heap1, Node* heap2 = nullptr); // merges two heaps together
    void removeMin(); //removes the root from the tree
    LeftistHeap(); 
    
private:
    struct Node
    {
        ItemType element;
        Node* left;
        Node* right;
        int nullHeight;
        
        Node( ItemType e, Node *l = NULL, Node *r = NULL, int h = -1 ) :
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
    Node* m_root;
    void setAllNullHeight() {setNullHeight(m_root);}; //calls the overided setAllNullHeight with the root
    void setAllNullHeight(Node* & ptr); //recursive function to set all null heights
    void setNullHeight(Node* & ptr); //sets individual null heights
    void swapKids(Node* & ptr); //switches the left and right children
    bool notLeftist(Node* ptr);
};


/*recursively goes through the leftist heap and sets the nullHeight for every node*/
void LeftistHeap::setAllNullHeight(Node* & ptr)
{
    if (ptr == nullptr)
    {
        ptr->nullHeight = -1;
    }
    setNullHeight(ptr->left);
    setNullHeight(ptr->right);
    
    setNullHeight(ptr);
}

/*sets the nullHeight for a specific Node*/
void LeftistHeap::setNullHeight(Node* & ptr)
{
    ptr->nullHeight = std::min(ptr->left->nullHeight, ptr->right->nullHeight) + 1;
}

/*inserts the ItemType into the Leftist Heap*/
void LeftistHeap::insert(ItemType input)
{
    Node* temp;
    temp->element = input;
    merge(m_root, temp);
}

/*Combines two heaps based on which root is smaller*/
Node* LeftistHeap::merge(Node* heap1, Node* heap2 = nullptr)
{
    Node* small;
    if (heap1 == nullptr)
    {
        return heap2;
    }
    if (heap2 == nullptr)
    {
        return heap2;
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
        swapkids(small);
    }
    setAllNullHeight();
    return small;

}

/*swaps the left and right children of inputted pointer with each other*/
void LeftistHeap::swapkids(Node* & ptr)
{
    if(ptr != nullptr)
    {
        if(ptr->left->nullHeight < ptr->right->nullHeight)
        {
            Node* temp = ptr->right;
            ptr->right = ptr->left;
            ptr->left = temp;
        }
    }
    swapkids(ptr->left);
    swapkids(ptr->right);
}

bool LeftistHeap::notLeftist(Node* ptr)
{
    if(ptr == nullptr)
    {
        return FALSE;
    }
    if(ptr->left->nullHeight < ptr->right->nullHeight)
    {
        return true;
    }
    return notLeftist(ptr->right) && notLeftist(ptr->left);
}

/*merges the left and right child of the root to remove the min*/
void LeftistHeap::removeMin()
{
    m_root = merge(m_root->right, m_root->left);
}







#endif /* LeftistHeap_hpp */
