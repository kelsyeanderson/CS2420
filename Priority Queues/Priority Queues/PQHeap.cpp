#include "PQHeap.h"

//Create a heap with maximum size "physicalSize" 
PQHeap::PQHeap(std::string name,int physicalSize ) 
{  
	this->name = name;
	size=0;
	heap = new ItemType[physicalSize];
	this->physicalSize = physicalSize;
}


// insert element and re-heapify
void PQHeap::insert(ItemType &newVal)
{  
	int curr = size;
	assert(size < physicalSize);
	int parent = (curr-1) / KIDS; // round down
	while(curr > 0 && newVal.priority > heap[parent].priority)
    {
		heap[curr] = heap[parent];
		curr = parent;
		parent = (curr-1) / KIDS;
	}
	heap[curr] = newVal;
	size++;
}

/*delete max for 4 kids instead of 2*/
ItemType PQHeap::deleteMax( )
{
    if (size==0)
    {
        return ItemType("error", -1);
    }
    ItemType toReturn = heap[0];
    size--;
    ItemType currVal = heap[size];
    int curr = 0;
    int firstChild = 1;
    int secondChild = firstChild + 1;
    int thirdChild = secondChild + 1;
    int fourthChild = thirdChild + 1;
    while( (firstChild < size && currVal.priority < heap[firstChild].priority) ||
          (secondChild < size && currVal.priority < heap[secondChild].priority) ||
          (thirdChild < size && currVal.priority < heap[thirdChild].priority) ||
          (fourthChild < size && currVal.priority < heap[fourthChild].priority))
    {
        int bestChild = firstChild;
        int priority1 = heap[firstChild].priority;
        int priority2 = heap[secondChild].priority;
        int priority3 = heap[thirdChild].priority;
        int priority4 = heap[fourthChild].priority;
        
        if( secondChild < size && priority2 > std::max(priority1, std::max(priority3, priority4)))
        {
            bestChild = secondChild;
        }
        else if (thirdChild < size && priority3 > std::max(priority1, std::max(priority2, priority4)))
        {
            bestChild = thirdChild;
        }
        else if (fourthChild < size && priority4 > std::max(priority1, std::max(priority2, priority3)))
        {
            bestChild = fourthChild;
        }
        
        heap[curr] = heap[bestChild];
        curr = bestChild;
        firstChild = KIDS * bestChild + 1;
        secondChild = firstChild + 1;
        thirdChild = secondChild + 1;
        fourthChild = thirdChild + 1;
    } // endwhile
    
    
    heap[curr] = currVal;
    return toReturn;
}


// Delete maximum value, re-heapify, and return max element
ItemType PQHeap::oldDeleteMax( )
{  	
	if (size==0)
    {
		return ItemType("error", -1);
    }
	ItemType toReturn = heap[0];
	size--;
	ItemType currVal = heap[size];
	int curr = 0;
	int left = 1;
	int right = left+1;
	while( (left < size && currVal.priority < heap[left].priority) ||
		(right < size && currVal.priority < heap[right].priority) )
    {
			int bestChild = left;
			if( right < size && heap[right].priority > heap[left].priority )
				bestChild = right;
			heap[curr] = heap[bestChild];
			curr = bestChild;
			left = OLDKIDS*bestChild+1;
			right = left+1;
	} // endwhile


	heap[curr] = currVal;
	return toReturn;

}


// merge second into current  heap
void PQHeap::merge(PQ * second)
{  
	for (int i=0; i < second->getSize(); i++)
    {
		insert(dynamic_cast<PQHeap*>(second)->heap[i]);
    }
	second->makeEmpty();
}

// Convert first "size: elements of PQ to a string.
std::string PQHeap::toString(int maxSize) const
{
    const int PERLINE = 5;
	std::stringstream out;
	out <<  name << "  current size=" << size;
	if (maxSize > size)
    {
		maxSize = size;
    }

	for (int i=0; i <maxSize; i ++)
	{  
		if (i%PERLINE==0) out << std::endl;
		out << heap[i].toString() << "\t";
	}
	out << std::endl;
	return out.str();
}
