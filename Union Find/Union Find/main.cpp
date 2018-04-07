//Kelsye Anderson
//A02093326
#include "Union.hpp"
#include "Node.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>

void unionizeForNumSize(int size, bool printEvery, bool print);

int main()
{
    const int size = 1000; //changes the size of the array
    bool printEvery = false; //set to true if you want to see every value after it has been unionized
    bool print = true; //set to true to print number of unions, finds, and days
    unionizeForNumSize(size, printEvery, print);
    
    return 0;
}

/*This function fills an array of length size with Node* whose values are numbers 0 - size. It then randomly unionizes the Nodes in the array with each other until they are all friends. If printEvery is true it will print the value and height for every node looked at after they are unionized. If print is true it will print the number of unions, finds and days after they have all been unionized*/
void unionizeForNumSize(int size, bool printEvery, bool print)
{
    Node* myArray[size];
    srand(int(time(NULL)));
    
    for(int i = 0; i < size; i++)
    {
        Node* temp = new Node(i);
        myArray[i] = temp;
    }
    
    Union myUnion;
    int count = 0;
    while(myUnion.m_unions < size - 1)
    {
        int rand1 = rand() % size;
        int rand2 = rand() % size;
        myUnion.unionByHeight(myArray[rand1], myArray[rand2]);
        if(printEvery == true)
        {
            std::cout << "-----------Rand-1--------------" << std::endl;
            std::cout << "First input [v:h]: [" << myArray[rand1]->m_value << ":" << myArray[rand1]->m_height << "]\n";
            std::cout << "-------------------------" << std::endl;
            std::cout << "-----------Rand-2--------------" << std::endl;
            std::cout << "Second input [v: h]: [" << myArray[rand2]->m_value << ":" << myArray[rand2]->m_height << "]\n";
            std::cout << "-------------------------\n\n";
       }
        count++;
    }
    
    if(print == true)
    {
        std::cout << "Number of Unions: " << myUnion.m_unions << std::endl;
        std::cout << "Number of Finds: " << myUnion.m_numFind << std::endl;
        std::cout << "Number of Days: " << myUnion.m_days << std::endl;
    }
}





