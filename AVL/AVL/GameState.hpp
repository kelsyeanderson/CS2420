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
    
    //sets the node based on input information
    GameState(Board data, std::string memory)
    {
        m_board = data;
        m_memory = memory;
        m_numMoves = memory.size()/3;
        m_cost = setCost(data);
        m_priority = m_cost + m_numMoves;
    }
    
    Board getBoard() {return m_board;}
    std::string getMemory() {return m_memory;}
    int getnumMoves() {return m_numMoves;}
    int getCost() {return m_cost;}
    int getPriority() {return m_priority;}
    int setCost(Board data);
    void incMoves();
private:
    Board m_board;
    std::string m_memory;
    int m_numMoves;
    int m_cost;
    int m_priority;
    
};

#endif /* GameState_hpp */
