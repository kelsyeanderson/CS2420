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
            if((data.board[i][j]%3 != j))
            {
                count++;
            }
        }
    }
    count /= 3;
    return count;
}

void GameState::incMoves()
{
    m_numMoves++;
    m_priority++;
}
