#include "AvlTree.h"
#include <iostream>
#include <iomanip>
#include <string>

int main()
{
	AvlTree<int> t;
	for (int i=1; i < 30; i=i+3)
	     t.insert(i);
	t.insert(7);

	t.printTree();
	std::cout << std::endl << t.findMin() << std::endl;
	std::cout << t.findMax() << std::endl;
	int check = 23;
	if (!t.contains(check))
		std::cout << check << " ITEM_NOT_FOUND failed!" << std::endl;
	
	std::string name = "this";

	AvlTree<std::string> words;
	words.insert("help");
	words.insert("me");
	words.insert("please");
	words.insert("I");
	words.insert("said");
	words.insert("help");
	words.insert("me");
	words.insert("please");
	words.printTree();

	char p;
	std::cin >> p;

	return 0;
}
