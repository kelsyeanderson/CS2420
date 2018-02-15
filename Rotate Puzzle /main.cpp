//Kelsye Anderson
//A02093326

#include <iostream>
#include "Board.h"
#include "List.hpp"

//Solves the puzzle
void solvePuzzel(Board fixMe);

int main()
{
    Board input1;
    Board input2;
    Board input3;
    Board input4;
    
    input1.inputBoard("input1.txt");
    solvePuzzel(input1);
    input2.inputBoard("input2.txt");
    solvePuzzel(input2);
    input3.inputBoard("input3.txt");
    solvePuzzel(input3);
    input4.makeBoard(3);
    solvePuzzel(input4);
    
    return 0;
}

void solvePuzzel(Board fixMe)
{
    std::cout << std::endl << "-------------------------------------------" << std::endl << std::endl;
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
                    std::cout << "Board ID: " << temp->m_self << ", Parent ID: " << temp->m_parent;
                    std::cout << ", History" << temp->m_memory << std::endl << temp->m_board.toString() << std::endl;
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







