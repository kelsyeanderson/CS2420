//
//  GameState.hpp
//  AVL
//
//  Created by Kelsye Anderson on 2/20/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp

#include <string>
#include "Board.h"

class GameState
{
public:
    Board m_board;
    std::string m_memory;
    int m_numMoves;
    int m_cost;
    int m_priority;
    
    //sets the node based on input information
    GameState(Board data, std::string memory)
    {
        m_board = data;
        m_memory = memory;
        m_numMoves = memory.size()/2;
        m_cost = setCost(data);
        m_priority = m_cost + m_numMoves;
    }
    
    int setCost(Board data);
    void incMoves();
    
};

#endif /* GameState_hpp */
