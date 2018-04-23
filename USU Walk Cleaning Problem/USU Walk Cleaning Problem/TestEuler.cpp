#include <iostream>
#include <iomanip>
#include "graph.h"
#include <assert.h>
#include <fstream>
using namespace std;

int main ()
{
    ofstream fout;
	fout.open("tourOut.txt");
	assert(fout);

    std::cout << "------------------g----------------------" << std::endl;
    Graph g("prog7A.txt", cout);
    g.findCycles();
//    g.computeTour(fout);  // If I want the output to appear on console, I just make the parameter "cout"
//
//    std::cout << "\n\n------------------g1----------------------" << std::endl;
//    Graph g1("prog7B.txt", cout);
//    g1.findCycles();
//    g1.computeTour(fout);
//
//    std::cout << "\n\n------------------g2----------------------" << std::endl;
//    Graph g2("prog7C.txt",cout);
//    g2.findCycles();
//    g2.computeTour(cout);
//    
    return 0;
}
