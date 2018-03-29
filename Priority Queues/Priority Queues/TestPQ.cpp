#include "PQHeap.h"
#include <time.h>
//#include "SkewHeap.h"
#include "LeftistHeap.hpp"
#include <fstream>
#include <iostream>
#include "Node.h"

//Insert limit elements of the file fin into heap.
void insertLeft(bool readLeft);
void insertNext(PQ & pq,std::ifstream & fin,int limit=0);

int main()
{

//    insertLeft(false);  // uncomment line to check leftist heap. Change input to true to have it print tree
    
    
    clock_t start = clock();
    int const DELETE_CT=20;
    int const PRINTSIZE=30;
    int const HOWMANY = 100;

    PQHeap pqMax("MaxHeap",6000);
    PQHeap oldMax("OldMaxHeap",6000);

    std::ifstream fin;
    fin.open("sixty1.txt");
    assert(fin);
    
    std::ifstream fin2;
    fin2.open("sixty2.txt");
    assert(fin2);

    for (int i = 0; i < 60; i++)
    {
        insertNext(pqMax, fin, HOWMANY);
        std::cout << i << " New delete\n--------------------" << std::endl;
        std::cout << pqMax.deleteMax().toString() << std::endl << std::endl;
        /*
        insertNext(oldMax, fin2, HOWMANY);
        std::cout << i << " Old delete\n--------------------" << std::endl;
        std::cout << oldMax.oldDeleteMax().toString() << std::endl << std::endl;*/
    }


    clock_t time = clock()-start;
    std::cout << "Elapsed time = " << ((float) time)/CLOCKS_PER_SEC << std::endl;
    return 0;
}

void insertLeft(bool readLeft)
{
    LeftistHeap leftist;
    std::ifstream fin("Prog5In.txt");
    if (!fin)
    {
        std::cout << "File not found :(" << std::endl;
        exit(-1);
    }
    
    int limit=0;
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
        leftist.insert(item);
    }
    if(readLeft == true)
    {
        leftist.toString();
    }
}

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

