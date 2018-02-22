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
void avlOutput(bool seeAll, int index, GameState check);

/*creates input Boards and runs them through both aStarSolve and bruteForceSolve*/
int main()
{
    Board input0;
    Board input1;
    Board input2;
    Board example;
    
    input0.inputBoard("input0.txt");
    input1.inputBoard("input1.txt");
    input2.inputBoard("input2.txt");
    example.makeBoard(90);
    
    std::cout << "\n\nInput 0";
    aStarSolve(input0);
    bruteForceSolve(input0);
    
    std::cout << "\n\nInput 1";
    aStarSolve(input1);
    bruteForceSolve(input1);
    
    std::cout << "\n\nInput 2";
    aStarSolve(input2);
    bruteForceSolve(input2);
    
    std::cout << "\n\nExample";
    aStarSolve(example);
    bruteForceSolve(example);
    
    return 0;
}

void aStarSolve(Board inputBoard)
{
    bool seeAll = false; //set equal to true, if you want to see every board it checks
    
    std::cout << std::endl << "---------------\nAvl Tree" << "\n--------------------------------------\n";
    
    AvlTree<GameState> puzzleTree;
    Board solution;
    
    /*check to make sure the board isn't already correct*/
    if(solution == inputBoard)
    {
        std::cout << "Your board was already sorted!!" << std::endl << inputBoard.toString() << std::endl;
    }
    
    /*creates a board of type GameState and initializes the tree with it*/
    GameState fixMe(inputBoard, "", 0, 0);
    puzzleTree.insert(fixMe);
    
    bool found = false;
    int numBoards = 0;
    int boardID = 1;
    while(!found)
    {
        /*removes and outputs the GameState of lowest priority in the tree*/
        GameState check = puzzleTree.removeMin();
        numBoards++;
        avlOutput(seeAll, numBoards, check);//cout statements in here
        /*checks if the min priority GameState from the tree is the correct one*/
        if(check.m_board == solution)
        {
            found = true;
            avlOutput(!seeAll, numBoards, check);
        }
        else
        {
            /*creates a temp GameState with the board and memory from the GameState check above. Sets the
             parent to the current Board ID from check and sets the Board ID to the number of boards that
             have been created and put into the tree. It then moves the board, adding the move to the end
             of the string, and creates a new temp GameState with the new information from the move (you
             need to do this because the cost doesn't update right now without it). It then inserts the
             new temp GameState into the avl tree*/
            for(int i = 0; i < 12; i++)
            {
                GameState temp(check.m_board, check.m_memory, check.m_self, boardID);
                temp.m_memory += temp.m_board.move(i);
                GameState newTemp(temp.m_board, temp.m_memory, temp.m_parent, temp.m_self);
                //std::cout << "Score for ID: " << i << " " << newTemp.m_priority << std::endl;
                puzzleTree.insert(newTemp);
                boardID++;
            }
        }
    }
}

/*This function prints all the information for each of the boards if seeAll is set to true*/
void avlOutput(bool seeAll, int numBoards, GameState check)
{
    if(seeAll == true)
    {
        std::cout << std::endl << "Board ID:" << check.m_self << ", Parent ID:" << check.m_parent;
        std::cout << ", History" << check.m_memory << " (" << check.m_numMoves << "):[";
        std::cout<< check.m_priority << "]" << std::endl;
        std::cout << check.m_board.toString();
        std::cout << std::endl << "removed " << numBoards << " states" << std::endl;
    }
    
}

/*Solves the game rotate puzzle using a linked list*/
void bruteForceSolve(Board fixMe)
{
    std::cout << std::endl << "---------------\nBrute Force" << "\n--------------------------------------\n";
    Board solution; //solved board to check against
    
    List list;
    node* x = list.createNode(fixMe,"", 0 , 0);
    list.in(x);
    
    node* check = list.out();
    node* start = check;
    int index = 1;
    bool found = 0;
    int dequeued = 0;
    
    //checks if the board is already correct
    if(check->m_board == solution)
    {
        std::cout << "Your board was already sorted!!" << std::endl << check->m_board.toString() << std::endl;
    }
    else{
        
        /*prints the board without moves. Uncomment if printing every board*/
//        std::cout << "Board ID: " << check->m_self << ", Parent ID: " << check->m_parent;
//        std::cout << ", History" << check->m_memory << std::endl << check->m_board.toString() << std::endl;
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
                    std::cout << temp->m_board.toString() << std::endl;
                    std::cout << "States Dequeued: " << dequeued << std::endl;
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
            dequeued++;
        }
    }
    /*uncomment if printing original board*/
//    std::cout << std::endl << "Origial Board" << std::endl << start->m_board.toString();
}



