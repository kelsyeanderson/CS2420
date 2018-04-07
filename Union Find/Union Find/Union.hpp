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
#include "Node.hpp"

class Union
{
public:
    int m_days;
    
    void unionByHeight(Node* root1, Node* root2);
    
private:
    Node* isRoot(Node* root);
    
};

void Union::unionByHeight(Node* ptr1, Node* ptr2)
{
    Node* root1 = isRoot(ptr1);
    Node* root2 = isRoot(ptr2);
    if (root2->m_height < root1->m_height)
    {
        root1->m_height = root2->m_value;
    }
    else
    {
        if(root2->m_height == root1->m_height)
        {
            root1->m_height--; // weight  stored as a negative,  this increases height.
        }
        
        root2->m_height = root1->m_value;
    }
}

Node* Union::isRoot(Node* ptr)
{
    if (ptr->m_height < 0)
    {
        return ptr;
    }
    
    return isRoot(ptr->m_parent);
}



#endif /* Union_hpp */
