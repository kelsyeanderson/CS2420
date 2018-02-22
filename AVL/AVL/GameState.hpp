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
    int m_parent;
    int m_self;
    
    /*overloads the operators for << <= >= < > and == so it will work with GameStates*/
    friend std::ostream&  operator<<( std::ostream& ss, const GameState& gs);
    friend bool operator<=(const GameState& rhs, const GameState& lhs)
    {
        return rhs.m_priority <= lhs.m_priority;
    }
    friend bool operator>=(const GameState& rhs, const GameState& lhs)
    {
        return rhs.m_priority >= lhs.m_priority;
    }
    friend bool operator<(const GameState& rhs, const GameState& lhs)
    {
        return rhs.m_priority < lhs.m_priority;
    }
    friend bool operator>(const GameState& rhs, const GameState& lhs)
    {
        return rhs.m_priority > lhs.m_priority;
    }
    friend bool operator==(const GameState& rhs, const GameState& lhs)
    {
        return rhs.m_priority == lhs.m_priority;
    }
    
    //sets the GameState based on input information
    GameState(Board data, std::string memory, int parent, int self)
    {
        m_board = data;
        m_memory = memory;
        m_numMoves = memory.size()/3;
        m_parent = parent;
        m_self = self;
        m_cost = setCost(data);
        m_priority = m_cost + m_numMoves;
    }
    
    int setCost(Board data);
    
};



#endif /* GameState_hpp */
