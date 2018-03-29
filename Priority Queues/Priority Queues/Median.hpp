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
    Median();
    void insert(ItemType input); //inserts ItemTypes into the Median class
    void toString(); //outputs the med [word and frequency]
    ItemType removeMed(); //removes the median from whichever has a greater size
private:
    void balance(); //makes sure the heaps are balanced

};

Median::Median():
    m_med("", -1), minHeap(), maxHeap("MaxHeap",6000) {}

void Median::insert(ItemType newValue)
{
    if (m_med.priority == -1)
    {
        m_med = newValue;
    }
    else if(newValue.priority > m_med.priority)
    {
        minHeap.insert(newValue);
    }
    else if(newValue.priority <= m_med.priority)
    {
        maxHeap.insert(newValue);
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

ItemType Median::removeMed()
{
    ItemType toReturn = m_med;
    if(maxHeap.size > minHeap.size)
    {
        m_med = maxHeap.deleteMax();
    }
    else if(minHeap.size > maxHeap.size)
    {
        m_med = minHeap.removeMin();
    }
    else
    {
        m_med = minHeap.removeMin();
    }
    return toReturn;
}

void Median::toString()
{
    std::cout << "[" << m_med.word << ", " << m_med.priority << "]" << std::endl;
}


#include <stdio.h>

#endif /* Median_hpp */
