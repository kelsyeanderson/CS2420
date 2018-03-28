// LeftistHeap.cpp - wdg 2008
#ifndef PQHeap_H
#define PQHeap_H

#include "PQ.h"

class PQHeap: public PQ 
{
public:
    static const int KIDS = 4; //changed the number of kids to be for a d=4 d-ary heap
    static const int OLDKIDS = 2;
	PQHeap(std::string name, int size);
	void insert(ItemType &);  //    virtual void insert(ItemType & x )=0 ;
	ItemType oldDeleteMax();
    ItemType deleteMax();
	int getCount() const;
	void merge(PQ *h);  // merges h into current heap  
	std::string toString(int size) const;
private:
	int getBestKid(int hole, int size);
	ItemType * heap;   // Heap Array
	int physicalSize;  // Physical size of heap
};


#endif


