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
    std::string toString();
    FollowingWordInfo(std::string s, int c = 1)
    {
        m_word = s;
        m_count = c;
    };
    void increment() {m_count++;}
};

/*Appends the count to the end of the word string*/
std::string FollowingWordInfo::toString()
{
    return m_word + "(" + std::to_string(m_count) + ")";
}


#endif /* FollowingWordInfo_hpp */
