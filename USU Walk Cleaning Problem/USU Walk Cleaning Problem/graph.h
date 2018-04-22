//
//  graph.h
//  USU Walk Cleaning Problem
//
//  Created by Kelsye Anderson on 4/21/18.
//  Copyright © 2018 Kelsye Anderson. All rights reserved.
//

#ifndef graph_h
#define graph_h
#include <vector>
#include <iostream>
#include <fstream>
#include "edge1.h"

class Graph
{
public:
    int numNodes;
    int numEdges;
    std::vector<std::vector<int>> adjMat;
    std::vector<std::vector<std::string>> allCycles;
    
    Graph(std::string txtName, std::ostream& fout);
    void printMat(std::ostream & output = std::cout);
    void findCycles();
    
private:
    void eulerTourCheck();
    void setMat(std::ifstream& inFile);
    bool isAdjMatDone();
    int findRow();
    int findNextNode(int currRow, int currID);
    void update(int& currID, vector<std::string>& currCycle, int& nextNode);
    std::string toString(int toNode, int fromNode, int cycleID);
    
};

/*default constructor opens the txt file, inports the file into the adjMat, double checks that it is a euler tour, and then puts the matrix into an ostream*/
Graph::Graph(std::string txtName, std::ostream& output)
{
    /*opens the txt file and makes sure that it is open*/
    std::ifstream inFile;
    inFile.open(txtName);
    if(!inFile)
    {
        std::cerr << "Could not open file!!" << std::endl;
        exit(-1);
    }
    
    /*grab the number of nodes and number of edges from first line in file*/
    inFile >> numNodes;
    inFile >> numEdges;
    
    setMat(inFile);
    eulerTourCheck();
    printMat(output);
}

/*sets the matrix given the input from the txt file*/
void Graph::setMat(std::ifstream& inFile)
{
    /*initializes the vector to all 0's*/
    vector<int> tempVec;
    for(int j = 0; j < numNodes; j++)
    {
        tempVec.push_back(0);
    }
    for(int i = 0; i < numNodes; i++)
    {
        adjMat.push_back(tempVec);
    }
    
    /*sets the adjMat with -1 where there are edges*/
    for(int i=0 ; i < numEdges; i++)
    {
        Edge tempEdge;
        char outNode, inNode;
        inFile >> outNode;
        inFile >> inNode;
        
        tempEdge.set(outNode, inNode);
        adjMat[tempEdge.fromNode][tempEdge.toNode] = -1;
        adjMat[tempEdge.toNode][tempEdge.fromNode] = -1;
    }
}

/*checks that there are an even number of edges for each node*/
void Graph::eulerTourCheck()
{
    for(int i = 0; i < numNodes; i++)
    {
        int tempNumEdges = 0;
        for(int j = 0; j < numNodes; j++)
        {
            if(adjMat[i][j] == -1)
            {
                tempNumEdges++;
            }
        }
        if((tempNumEdges % 2) != 0)
        {
            std::cerr << "No Euler Tour Available" << std::endl;
        }
    }
}

/*outputs the matrix*/
void Graph:: printMat(std::ostream& output)
{
    for(int i = 0; i < numNodes; i++)
    {
        for(int j = 0; j < numNodes; j++)
        {
            output << setw(3) << adjMat[i][j];
        }
        output << endl;
    }
}

/*goes through the matrix and returns false if a side hasn't been looked at yet*/
bool Graph::isAdjMatDone()
{
    for(int i = 0; i < numNodes; i++)
    {
        for(int j = 0; j < numNodes; j++)
        {
            if(adjMat[i][j] == -1)
            {
                return false;
            }
        }
    }
    return true;
}

/*goes through matrix and returns the first row that has a -1 in it (the row is a node)*/
int Graph::findRow()
{
    for(int row = 0; row < numNodes; row++)
    {
        for(int col = 0; col < numNodes; col++)
        {
            if(adjMat[row][col] == -1)
            {
                return row;
            }
        }
    }
    
    return -1;
}

/*goes through matrix and returns the column that has a -1 in it (the column is the next node)*/
int Graph::findNextNode(int currRow, int currID)
{
    for(int col = 0; col < numNodes; col++)
    {
        if(adjMat[currRow][col] == -1)
        {
            adjMat[currRow][col] = currID;
            adjMat[col][currRow] = currID;
            return col;
        }
    }
    
    return -1;
}

/*incraments currID, puts currCycle into all*/
void Graph::update(int& currID, vector<std::string>& currCycle, int& nextNode)
{
    currID++;
    allCycles.push_back(currCycle);
    currCycle.erase(currCycle.begin(), currCycle.end());
    nextNode = -1;
}

std::string Graph::toString(int toNode, int fromNode, int cycleID)
{
    ostringstream os;  // allows string to act like stream to use stream operations
    char t = toNode + 'A';
    char f = fromNode + 'A';
    os << "   "<<f << "-"<<t  << "(" << cycleID << ")" ;
    return os.str();
}

void Graph::findCycles()
{
    int currID = 1;
    int origNode;
    std::vector<string> currCycle;
    int nextNode = -1;
    int currNode;
    while(!isAdjMatDone())
    {
        origNode = findRow();
        if(origNode == -1)
        {
            std::cerr << "findRow broke" << std::endl;
            exit(-1);
        }
        currNode = origNode;
        int count = 0;
        while(nextNode != origNode)
        {
            nextNode = findNextNode(currNode, currID);
            if(nextNode == -1)
            {
                std::cerr << "findNextNode broke" << std::endl;
                exit(-1);
            }
            currCycle.push_back(toString(nextNode, currNode, currID));
            std::cout << currCycle[count] << " ";
            count++;
            currNode = nextNode;
        }
        update(currID, currCycle, nextNode);

    }
    
    for(int i = 0; i < allCycles.size(); i++)
    {
        for(int j = 0; j < allCycles[i].size(); j++)
        {
            std::cout << allCycles[i][j] << " ";
        }
        std::cout << std::endl;
    }
}





#endif /* graph_h */
