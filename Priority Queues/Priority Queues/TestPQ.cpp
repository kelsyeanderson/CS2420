//Kelsye Anderson
//A02093326

#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Node.h"
#include "Median.hpp"
//#include "SkewHeap.h"
#include "LeftistHeap.hpp"
#include "PQHeap.h"

LeftistHeap createLeft(bool readLeft, int limit, std::string txt); //inserts words from txt into a leftist heap
Median createMed(bool readMed, int limit, std::string txt); //inserts words from txt into a Median heap
void insertNext(PQ & pq,std::ifstream & fin,int limit=0); //Insert limit elements of the file fin into heap.
PQHeap createPqheap(bool readPQ, int const HOWMANY, std::string txt); //inserts words from txt into a PQ heap

int main()
{
//    int const DELETE_CT=20;
//    int const PRINTSIZE=30;
    std::string fileToReadIn = "Prog5In.txt"; //change to file name you want
    
    int const pqLimit = 100; //change to the sample size you want for PQ
    int leftLimit = 60; //change to the sample size you want for Leftist
    int medLimit = 500; //change to the sample size you want for median
    
    bool readPQ = false; //change to true to print pqLimit number of max ItemTypes removed from PQ heap
    bool readLeft = false; //change to true to print the leftist tree
    bool readMed = true; //change to true to print every hundren medians and final median with it's max and min heap sizes
    
    PQHeap pqHeap = createPqheap(readPQ, pqLimit, fileToReadIn);
    LeftistHeap leftHeap = createLeft(readLeft, leftLimit, fileToReadIn);
    Median medHeap = createMed(readMed, medLimit, fileToReadIn);
    


    return 0;
}

/*Creates a Leftist Heap from information in txt of limit size. Prints tree if readLeft is true. Returns leftist heap*/
LeftistHeap createLeft(bool readLeft, int limit, std::string txt)
{
    LeftistHeap leftist;
    std::ifstream fin(txt);
    if (!fin)
    {
        std::cout << "File not found :(" << std::endl;
        exit(-1);
    }
    
    if (limit == 0)
    {
        limit = std::numeric_limits<int>::max();
    }
    std::string word;
    int ct;
    for (int i = 0; i < limit && !fin.eof(); i++)
    {
        fin >> word >> ct;
        //std::cout << "inserting " << word << ct << std::endl;
        ItemType item(word, ct);
        leftist.insert(item);
    }
    if(readLeft == true)
    {
        leftist.toString();
    }
    
    return leftist;
}

/*Creates a Median Heap from information in txt of limit size. Prints every hundred medians, the final median, plus the max and min heap's size if readMed is true. Returns Median heap*/
Median createMed(bool readMed , int limit, std::string txt)
{
    Median myMedian;
    std::ifstream fin(txt);
    if (!fin)
    {
        std::cout << "File not found :(" << std::endl;
        exit(-1);
    }
    
    if (limit == 0)
    {
        limit = std::numeric_limits<int>::max();
    }
    std::string word;
    int ct;
    for (int i =0; i < limit && !fin.eof(); i++)
    {
        fin >> word >> ct;
        //std::cout << "inserting " << word << ct << std::endl;
        ItemType newVal(word, ct);
        myMedian.insert(newVal);
        if(readMed == true && i%100 == 0)
        {
            std::cout << i << ": ";
            myMedian.toString();
        }
    }
    if(readMed == true)
    {
        std::cout << "Final Median: ";
        myMedian.toString();
        std::cout << "maxHeap size: " << myMedian.maxHeap.size << std::endl;
        std::cout << "minHeap size: " << myMedian.minHeap.size << std::endl;
    }
    
    return myMedian;
}

/*Creates a PQ Heap from information in txt of limit size. Prints pqLimit number of max ItemTypes removed from PQ heap if readPQ is true. Returns PQ heap*/
PQHeap createPqheap(bool readPQ, int const HOWMANY, std::string txt)
{
    clock_t start = clock();
    
    PQHeap pqMax("MaxHeap",6000);
    
    std::ifstream fin;
    fin.open(txt);
    assert(fin);
    
    for (int i = 0; i < HOWMANY; i++)
    {
        insertNext(pqMax, fin, HOWMANY);
        if(readPQ == true)
        {
            std::cout << i << ": " <<  pqMax.deleteMax().toString() << std::endl;
        }
    }
    
    
    clock_t time = clock()-start;
    if(readPQ == true)
    {
        std::cout << "Elapsed time = " << ((float) time)/CLOCKS_PER_SEC << std::endl;
    }
    return pqMax;
}

/*Insert limit elements of the file fin into heap.*/
void insertNext(PQ & pq,std::ifstream & fin,int limit)
{
    if (limit ==0)
    {
        limit = std::numeric_limits<int>::max();
    }
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



