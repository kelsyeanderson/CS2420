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
    void unionizeForNumSize(int size, bool print);
    
private:
    Node* find(Node* root1);
    
};

/*unionizes two ptrs by height*/
void Union::unionByHeight(Node* ptr1, Node* ptr2)
{
    m_days++;
    Node* root1 = find(ptr1);
    Node* root2 = find(ptr2);
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
    m_numFind++;
    if (ptr->m_height < 0)
    {
        return ptr;
    }
    
    Node* root = find(ptr->m_parent);
    ptr->m_parent = root;
    
    return root;
}

/*This function fills an array of length size with Node* whose values are numbers 0 - size. It then randomly unionizes the Nodes in the array with each other until they are all friends. If print is true it will print the number of unions, finds and days after they have all been unionized*/
void Union::unionizeForNumSize(int size, bool print)
{
    Node* myArray[size];
    srand(int(time(NULL)));
    
    for(int i = 0; i < size; i++)
    {
        Node* temp = new Node(i);
        myArray[i] = temp;
    }
    
    while(m_unions < size - 1)
    {
        int rand1 = rand() % size;
        int rand2 = rand() % size;
        unionByHeight(myArray[rand1], myArray[rand2]);
        
        /*uncomment to help debug*/
        
//        std::cout << "-----------Rand-1--------------" << std::endl;
//        std::cout << "First input [v:h]: [" << myArray[rand1]->m_value << ":" << myArray[rand1]->m_height << "]\n";
//        std::cout << "-------------------------" << std::endl;
//        std::cout << "-----------Rand-2--------------" << std::endl;
//        std::cout << "Second input [v: h]: [" << myArray[rand2]->m_value << ":" << myArray[rand2]->m_height << "]\n";
//        std::cout << "-------------------------\n\n";
    }
    
    if(print == true)
    {
        std::cout << "Number of Unions: " << m_unions << std::endl;
        std::cout << "Number of Finds: " << m_numFind << std::endl;
        std::cout << "Number of Days: " << m_days << std::endl;
    }
}



#endif /* Union_hpp */
