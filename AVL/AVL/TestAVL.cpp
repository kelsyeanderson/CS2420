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
    
    Board test;
    test.makeBoard(3);
    solvePuzzle(input1);
    
    
    
    
    
//    char p;
//    std::cin >> p;

	return 0;
}

void solvePuzzle(Board inputBoard)
{
    AvlTree<GameState> puzzleTree;
    Board solution;
    
    if(solution == inputBoard)
    {
        std::cout << "Your board was already sorted!!" << std::endl << inputBoard.toString() << std::endl;
    }
    
    GameState fixMe(inputBoard, "", 0, 0);
    puzzleTree.insert(fixMe);
    
    bool found = false;
    int numBoards = 0;
    
    while(!found)
    {
        GameState check = puzzleTree.removeMin();
        numBoards++;
        std::cout << std::endl << "Board ID:" << check.m_self << ", Parent ID:" << check.m_parent;
        std::cout << ", History" << check.m_memory << " (" << check.m_numMoves << "):[";
        std::cout<< check.m_priority << "]" << std::endl;
        std::cout << check.m_board.toString();
        std::cout << std::endl << "removed " << numBoards << " states" << std::endl;
        if(check.m_board == solution)
        {
            found = true;
        }
        else
        {
            for(int i = 0; i < 12; i++)
            {
                GameState temp(check.m_board, check.m_memory, check.m_self, i);
                temp.m_memory += temp.m_board.move(i);
                GameState newTemp(temp.m_board, temp.m_memory, temp.m_parent, temp.m_self);
                puzzleTree.insert(newTemp);
            }
        }
        
        
    }
    
    
    
    
}





