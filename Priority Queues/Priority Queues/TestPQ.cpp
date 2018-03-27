#include "PQHeap.h"
#include <time.h>
//#include "SkewHeap.h"
#include "LeftistHeap.hpp"

//Insert limit elements of the file fin into heap.
void insertNext(PQ & pq,std::ifstream & fin,int limit=0) 
{	if (limit ==0) 
		limit = std::numeric_limits<int>::max();
	std::string word;
	int ct;
	for (int i =0; i <= limit && !fin.eof(); i++)
	{
		fin >> word >> ct;
		//std::cout << "inserting " << word << ct << std::endl;
		ItemType item(word, ct);
		pq.insert(item);
	}
}

int main()
{
    LeftistHeap test;
//    clock_t start = clock();
//    int const DELETE_CT=20;
//    int const PRINTSIZE=30;
//    int const HOWMANY = 100;
//
//    PQHeap pqMax("MaxHeap",6000);
//
//    std::ifstream fin;
//    fin.open("Prog5In.txt");
//    assert(fin);
//
//    for (int i = 0; i < 60; i++)
//    {
//        insertNext(pqMax, fin, HOWMANY);
//        std::cout << pqMax.deleteMax().toString() << std::endl;
//    }
//
//
//    clock_t time = clock()-start;
//    std::cout << "Elapsed time = " << ((float) time)/CLOCKS_PER_SEC << std::endl;
//    std::cin.ignore();
}


