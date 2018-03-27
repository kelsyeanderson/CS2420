//
//  List.cpp
//  Rotate Puzzle
//
//  Created by Kelsye Anderson on 1/23/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#include "List.hpp"


//creates a Node out of a board
node* List::createNode(Board data, std::string memory, int parent, int self)
{
    node* temp = new node(data, memory, parent, self);
    return temp;
}

//initializes the tail and head to nullptr
List::List()
{
    m_tail = nullptr;
    m_head = nullptr;
}


//puts the pointer node at the end of the linked list and switches the tail to the inputed node
void List::in(node* input)
{
    if (m_head == nullptr)
    {
        m_head = input;
        m_tail = m_head;
    }
    else
    {
        m_tail->m_next = input;
        m_tail = m_tail->m_next;
    }
}

//Takes the first node off of the linked list and makes the second node in the list = the head
node* List::out()
{
    node* temp = m_head;
    if(m_head != nullptr)
    {
        m_head = m_head->m_next;
    }
    else
    {
        m_head = nullptr;
    }
    return temp;
}





