//
//  GameState.cpp
//  AVL
//
//  Created by Kelsye Anderson on 2/20/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#include "GameState.hpp"
#include "Board.h"
#include <string>

/*Goes throught the inputed board and (under) estimates how many moves
 are needed to solve the board. Outputs the cost*/
int GameState::setCost(Board data)
{
    int count = 0;
    for(int i = 0; i < 3; i++ )
    {
        for(int j = 0; j < 3; j++)
        {
            if ((data.board[i][j]-1)/3 != i)
            {
                count++;
            }
            if((data.board[i][j]-1)%3 != j)
            {
                count++;
            }
        }
    }
    count /= 3;
    return count;
}

std::ostream&  operator<<(std::ostream& ss, const GameState& gs) {
    ss << gs.m_board.toString() << std::endl;
    return ss;
}
