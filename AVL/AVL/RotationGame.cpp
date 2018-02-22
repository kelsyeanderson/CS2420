//
//  RotationGame.cpp
#include "AvlTree.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "GameState.hpp"
#include "List.hpp"

void aStarSolve(Board fixMe);
void bruteForceSolve(Board fixMe);

int main()
{
    Board input0;
    Board input1;
    Board input2;
    
    input0.inputBoard("input0.txt");
    input1.inputBoard("input1.txt");
    input2.inputBoard("input2.txt");
    
    Board test;
    test.makeBoard(14);
    
    aStarSolve(test);
    
    return 0;
}

void aStarSolve(Board inputBoard)
{
    std::cout << std::endl << "Avl Tree" << "\n-------------------------------------------\n\n";
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
                //std::cout << "Score for ID: " << i << " " << newTemp.m_priority << std::endl;
                puzzleTree.insert(newTemp);
            }
        }
    }
}

void bruteForceSolve(Board fixMe)
{
    std::cout << std::endl << "Brute Force" << "\n-------------------------------------------\n\n";
    Board solution; //solved board to check against
    
    List list;
    node* x = list.createNode(fixMe,"", 0 , 0);
    list.in(x);
    
    node* check = list.out();
    node* start = check;
    int index = 1;
    bool found = 0;
    
    //checks if the board is already correct
    if(check->m_board == solution)
    {
        std::cout << "Your board was already sorted!!" << std::endl << check->m_board.toString() << std::endl;
    }
    else{
        
        //prints the board without moves
        std::cout << "Board ID: " << check->m_self << ", Parent ID: " << check->m_parent;
        std::cout << ", History" << check->m_memory << std::endl << check->m_board.toString() << std::endl;
        while(!found)
        {
            for(int i = 0; i < 12; i++)
            {
                node* temp = new node(check->m_board,check->m_memory,check->m_parent,check->m_self);
                temp->m_memory += temp->m_board.move(i);
                temp->m_parent = temp->m_self;
                temp->m_self = index;
                
                //checks if the new board is correct; if true prints solved board
                if (temp->m_board == solution)
                {
                    found = true;
                    std::cout << "Board ID:" << temp->m_self << ", Parent ID:" << temp->m_parent;
                    std::cout << ", History" << temp->m_memory << std::endl;
                    std::cout << "You Won!!!!" << std::endl << temp->m_board.toString();
                    break;
                }
                //if board is not correct print the board and add the new board to the end of the list
                else
                {
                    /*uncomment to print every board along the way*/
//                    std::cout << "Board ID: " << temp->m_self << ", Parent ID: " << temp->m_parent;
//                    std::cout << ", History" << temp->m_memory << std::endl << temp->m_board.toString() << std::endl;
                    list.in(temp);
                    index++;
                }
                
            }
            //pulls the first node from the list off to check
            check = list.out();
        }
    }
    
    std::cout << std::endl << "Origial Board" << std::endl << start->m_board.toString();
}



