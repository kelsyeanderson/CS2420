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
    Graph g("prog7A.txt", fout);
    g.computeTour(cout);  // If I want the output to appear on console, I just make the parameter "cout"

    std::cout << "\n\n------------------g1----------------------" << std::endl;
    Graph g1("prog7B.txt", fout);
    g1.computeTour(cout);

    std::cout << "\n\n------------------g2----------------------" << std::endl;
    Graph g2("prog7C.txt",fout);
    g2.computeTour(cout);

    return 0;
}
