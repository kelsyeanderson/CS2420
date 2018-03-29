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

/*initializes the median if heap is empty. Inserts the value into max or min heap depending on if the priority of the newValue is larger or smaller than the current median priority*/
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

/*checks if one tree is more than 1 size bigger than the other. If true, it rebalances by inserting the current median into the smaller heap and pulling whatever is at the top out of the bigger heap*/
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

/*reassigns the median to whichever ItemType is at the top of the heap in max or min. Chooses which heap to take from based on which is bigger. returns previous median */
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

/*prints the word and priority of median*/
void Median::toString()
{
    std::cout << "[" << m_med.word << ", " << m_med.priority << "]" << std::endl;
}


#include <stdio.h>

#endif /* Median_hpp */
