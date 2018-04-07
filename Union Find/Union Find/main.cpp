//Kelsye Anderson
//A02093326
#include "Union.hpp"
#include "Node.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>



int main()
{
    const int size = 10;
    
    Node* myArray[size];
    srand(time(NULL));
    
    for(int i = 0; i < size; i++)
    {
        Node* temp = new Node(i);
        myArray[i] = temp;
    }
    
    Union myUnion;
    
    while(myUnion.m_unions < size - 1)
    {
        int rand1 = rand() % size;
        int rand2 = rand() % size;
        myUnion.unionByHeight(myArray[rand1], myArray[rand2]);
    }
    
    std::cout << "Number of Unions: " << myUnion.m_unions << std::endl;
    std::cout << "Number of Finds: " << myUnion.m_numFind << std::endl;
    std::cout << "Number of Days: " << myUnion.m_days << std::endl;
    
    
    return 0;
}
