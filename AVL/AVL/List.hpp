//
//  List.hpp
//  Rotate Puzzle
//
//  Created by Kelsye Anderson on 1/23/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include <string>
#include "Board.h"

class node
{
public:
    Board m_board;
    std::string m_memory;
    int m_parent;
    int m_self;
    node* m_next;
    
    //sets m_next to nullpointer by default
    node(){m_next = nullptr;}
    //sets the node based on input information
    node(Board data, std::string memory, int parent, int self)
    {
        m_board = data;
        m_memory = memory;
        m_parent = parent;
        m_self = self;
        m_next = nullptr;
    }
    //cleans up memory
    ~node()
    {
        if (m_next != nullptr)
        {
            delete m_next;
            m_next = nullptr;
        }
    }
};

class List
{
private:
    node* m_head = nullptr;
    node* m_tail = nullptr;
public:
    node* createNode(Board data, std::string memory, int parent, int self);//creates a node based on input information
    List();
    void in(node* input);//adds pointer node to the end of list
    node* out(); //takes pointer node off the front of the list
};


#endif /* List_hpp */
