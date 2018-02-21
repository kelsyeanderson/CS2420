#include "AvlTree.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "GameState.hpp"

void solvePuzzle(Board fixMe);

int main()
{
    /*uncomment to test AVL Tree*/
    
//    AvlTree<int> t;
//    for (int i=1; i < 30; i=i+3)
//         t.insert(i);
//    t.insert(7);
//
//    std::cout << "beginning of print" << std::endl;
//    t.printTree();
//    std::cout << std::endl << t.findMin() << std::endl;
//    std::cout << t.findMax() << std::endl;
//
//    int check = 23;
//    if (!t.contains(check))
//        std::cout << check << " ITEM_NOT_FOUND failed!" << std::endl;
//
//    std::string name = "this";
//
//    AvlTree<std::string> words;
//    words.insert("help");
//    words.insert("me");
//    words.insert("please");
//    words.insert("I");
//    words.insert("said");
//    words.insert("help");
//    words.insert("me");
//    words.insert("please");
//    words.printTree();
//
//
//    std::cout << std::endl << "My test code" << std::endl;
//    AvlTree<int> testTree;
//    for(int i = 1; i < 12 ; i+=2)
//    {
//        testTree.insert(i);
//    }
//    testTree.insert(2);
//    testTree.insert(4);
//    testTree.insert(8);
//    std::cout << "New Tree" << std::endl;
//    testTree.printTree();
//
//    testTree.remove(7);
//    testTree.remove(9);
//    std::cout << std::endl << "Removed 7 and 9" << std::endl;
//    testTree.printTree();
//
//    testTree.insert(50);
//    testTree.insert(30);
//    testTree.insert(15);
//    testTree.insert(18);
//    std::cout << std::endl << "Added 50, 30, 15, 18" << std::endl;
//    testTree.printTree();
//
//    testTree.removeMin();
//    std::cout << std::endl << "remove Min called 1st time" << std::endl;
//    testTree.printTree();
//
//    testTree.removeMin();
//    std::cout << std::endl << "remove Min called 2nd time" << std::endl;
//    testTree.printTree();
//
//    testTree.removeMin();
//    std::cout << std::endl << "remove Min called 3rd time" << std::endl;
//    testTree.printTree();
//
//    testTree.insert(17);
//    std::cout << std::endl << "Added 17" << std::endl;
//    testTree.printTree();
    
    std::cout << std::endl << std::endl << "Rotate Board" << std::endl;
    Board input0;
    Board input1;
    Board input2;
    
    input0.inputBoard("input0.txt");
    input1.inputBoard("input1.txt");
    input2.inputBoard("input2.txt");
    
    
    
    
    
    
//    char p;
//    std::cin >> p;

	return 0;
}

void solvePuzzle(Board inputBoard)
{
    AvlTree<GameState> puzzleTree;
    Board solution;
    
    GameState fixMe(inputBoard, "");
    puzzleTree.insert(fixMe);
    
    
    
}





