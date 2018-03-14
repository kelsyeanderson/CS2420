//
//  FirstWordInfo.hpp
//  Hashing
//
//  Created by Kelsye Anderson on 3/13/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef FirstWordInfo_hpp
#define FirstWordInfo_hpp

#include <stdio.h>
#include <vector>
#include "FollowingWordInfo.hpp"

class FirstWordInfo
{
    std::string m_word;
    int m_count;
public:
    std::vector<FollowingWordInfo> secondWordList;
    std::string toString();
    FirstWordInfo(std::string s, int c = 1)
    {
        m_word = s;
        m_count = c;
    };
    void updateList(std::string w);
    void incrementCount(){ m_count++;}
};

/*Checks secondWordList to see if w is in there. If it is, it increments that word's count. If it is not in there it creates a FollowingWordInfo and pushes it onto the list*/
void FirstWordInfo::updateList(std::string w)
{
    bool found = false;
    int count = 0;
    int pos = NULL;
    while(!found || count < secondWordList.size())
    {
        if (secondWordList[count].m_word == w)
        {
            found = true;
            pos = count;
        }
        else
        {
            count++;
        }
    }
    
    if (pos != NULL)
    {
        secondWordList[pos].increment();
    }
    else
    {
        FollowingWordInfo temp(w);
        secondWordList.push_back(temp);
    }
}


#endif /* FirstWordInfo_hpp */
