//Kelsye Anderson
//A02093326
#include "Union.hpp"
#include "Node.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>


int main()
{
    const int size = 1000; //changes the size of the array
    bool print = true; //set to true to print number of unions, finds, and days
    Union myUnion;
    myUnion.unionizeForNumSize(size, print);
    return 0;
}

