//
//  Node.hpp
//  Union Find
//
//  Created by Kelsye Anderson on 4/7/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef Node_h
#define Node_h

class Node
{
public:
    int m_value;
    Node* m_parent;
    int m_height;
    
    Node(int v, Node* p = nullptr, int h= -1):
    m_value(v), m_parent(p), m_height(h) {}
    
private:
    
};

#endif /* Node_h */
