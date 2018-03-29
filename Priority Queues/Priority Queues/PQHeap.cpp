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
    ItemType orphan = heap[size];
    int hole = 0;
    
    bool done = false;
    while(!done)
    {
        int bestChild = getBestKid(hole, size);
        
        if(bestChild < 0)
        {
            done = true;
        }
        else if(orphan.priority < heap[bestChild].priority)
        {
            heap[hole] = heap[bestChild];
            hole = bestChild;
        }
        else
        {
            done = true;
        }
    } // endwhile
    
    heap[hole] = orphan;
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


int PQHeap::getBestKid(int hole, int size)
{
    int bestVal = (KIDS * hole) + 1;
    if(bestVal >= size)
    {
        return -1;
    }
    
    for (int i = bestVal + 1; i < size && i < bestVal + KIDS; i++)
    {
        if(heap[i].priority > heap[bestVal].priority)
        {
            bestVal = i;
        }
    }
    
    return bestVal;
}





