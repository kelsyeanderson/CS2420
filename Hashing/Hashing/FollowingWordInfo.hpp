//
//  FollowingWordInfo.hpp
//  Hashing
//
//  Created by Kelsye Anderson on 3/13/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef FollowingWordInfo_hpp
#define FollowingWordInfo_hpp

#include <stdio.h>
#include <iostream>

class FollowingWordInfo
{
public:
    std::string m_word;
    int m_count;
    //std::string toString() {return m_word;};
    FollowingWordInfo(std::string s, int c = 1)
    {
        m_word = s;
        m_count = c;
    };
    void increment() {m_count++;}
};

#endif /* FollowingWordInfo_hpp */
