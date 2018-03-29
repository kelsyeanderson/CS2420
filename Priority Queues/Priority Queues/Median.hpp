//
//  Median.hpp
//  Priority Queues
//
//  Created by Kelsye Anderson on 3/28/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef Median_hpp
#define Median_hpp
#include "LeftistHeap.hpp"
#include "PQHeap.h"
#include "ItemType.h"

class Median
{
public:
    ItemType m_med;
    LeftistHeap minHeap;
    PQHeap maxHeap;
    void insert(ItemType input); //inserts ItemTypes into the Median class
    void toString(); //outputs the med [word and frequency]
private:
    void balance(); //makes sure the heaps are balanced

};

void Median::insert(ItemType input)
{
    if(input.priority > m_med.priority)
    {
        minHeap.insert(input);
    }
    else
    {
        maxHeap.insert(input);
    }
    balance();
}

void Median::balance()
{
    if((minHeap.size - 1) > maxHeap.size) //minHeap is greater than maxHeap
    {
        ItemType temp = minHeap.removeMin();
        maxHeap.insert(m_med);
        m_med = temp;
    }
    else if ((maxHeap.size - 1) > minHeap.size) //maxHeap is greater than minHeap
    {
        ItemType temp = maxHeap.deleteMax();
        minHeap.insert(m_med);
        m_med = temp;
    }
    else
    {
        return;
    }
}

void Median::toString()
{
    std::cout << "Median: [" << m_med.word << ", " << m_med.priority << "]" << std::endl;
}


#include <stdio.h>

#endif /* Median_hpp */
