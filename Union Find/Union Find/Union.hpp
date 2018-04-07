//
//  Union.hpp
//  Union Find
//
//  Created by Kelsye Anderson on 4/7/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef Union_hpp
#define Union_hpp

#include <stdio.h>
#include <iostream>
#include "Node.hpp"

class Union
{
public:
    int m_days;
    int m_unions;
    int m_numFind;
    
    Union(int d = 0, int u = 0, int f = 0):
    m_days(d), m_unions(u), m_numFind(f) {}
    
    void unionByHeight(Node* root1, Node* root2);
    void toString(Node* ptr);
    
private:
    Node* find(Node* root1);
    
};

/*unionizes two ptrs by height*/
void Union::unionByHeight(Node* ptr1, Node* ptr2)
{
    m_days++;
    Node* root1 = find(ptr1);
    m_numFind++;
    Node* root2 = find(ptr2);
    m_numFind++;
    if(root1->m_value == root2->m_value)
    {
        return;
    }
    if (root2->m_height < root1->m_height)
    {
        root1->m_height = root2->m_value;
        root1->m_parent = root2;
        m_unions++;
    }
    else
    {
        if(root2->m_height == root1->m_height)
        {
            root1->m_height--; // weight  stored as a negative,  this increases height.
        }
        root2->m_height = root1->m_value;
        root2->m_parent = root1;
        m_unions++;
    }
}

/*finds root and then sets the Nodes's parent (from the first ptr up until the root) to root*/
Node* Union::find(Node* ptr)
{
    if (ptr->m_height < 0)
    {
        return ptr;
    }
    
    Node* root = find(ptr->m_parent);
    ptr->m_parent = root;
    
    return root;
}



#endif /* Union_hpp */
