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
    std::string tour;
    std::vector<int> edgesPerNode;
    std::vector<std::vector<int>> adjMat;
    std::vector<std::vector<int>> allCyclesNum;
    std::vector<std::vector<std::string>> allCyclesStr;
    
    std::vector<bool> visitedCyc;
    std::vector<std::vector<int>> nodeArray;
    
    Graph(std::string txtName, std::ostream& output);
    void printMat(std::ostream & output = std::cout);
    void findCycles();
    void merge();
    void computeTour(std::ostream& output);
    
private:
    void eulerTourCheck();
    void setMat(std::ifstream& inFile);
    bool isAdjMatDone();
    int findRow();
    int findNextNode(int currRow, int currID);
    void update(int& currID, vector<std::string>& currCycle, vector<int> currCycleNum, int& nextNode);
    std::string toString(int toNode, int fromNode, int cycleID);
    
    void merge(int cycleNum, int node);
    void createNodeArray();
    
    bool hitAllEdges();
    int nextEdge(int currNode, vector<int>& startofCycles);
    bool alreadyDone(std::ostream& output);
    void computeStarts(std::vector<int>& startOfCycles);
    
    void computeTour(std::vector<int> startOfCycles, int currRow);
    
};

/*default constructor opens the txt file, inports the file into the adjMat, double checks that it is a euler tour, and then outputs the matrix into an ostream*/
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
    
    setMat(inFile);   //sets the matrix based on the input from the file
    eulerTourCheck(); //checks that it has a euler tour
    printMat(output); //prints the matrix into whatever ostream is provided
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

/*checks that there are an even number of edges for each node. Stores the number of edges per node in edgesPerNode vector while doing this*/
void Graph::eulerTourCheck()
{
    for(int i = 0; i < numNodes; i++)
    {
        int tempNumEdges = 0;
        edgesPerNode.push_back(tempNumEdges);
        for(int j = 0; j < numNodes; j++)
        {
            if(adjMat[i][j] == -1)
            {
                tempNumEdges++;
                edgesPerNode[i]++;
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
void Graph::update(int& currID, vector<std::string>& currCycle, vector<int> currCycleNum, int& nextNode)
{
    currID++;
    allCyclesStr.push_back(currCycle);
    allCyclesNum.push_back(currCycleNum);
    currCycle.erase(currCycle.begin(), currCycle.end());
    nextNode = -1;
}

std::string Graph::toString(int toNode, int fromNode, int cycleID)
{
    ostringstream os;  // allows string to act like stream to use stream operations
    char t = toNode + 'A';
    char f = fromNode + 'A';
    os << f << "-"<<t  << "(" << cycleID << ")" << "   ";
    return os.str();
}

void Graph::findCycles()
{
    int currID = 1;
    int origNode;
    std::vector<string> currCycleStr;
    std::vector<int> currCycleNum;
    int nextNode = -1;
    int currNode;
    
    /*problems to fix. finds cycles, but not necesarily the smallest*/
    while(!isAdjMatDone())
    {
        origNode = findRow();
        if(origNode == -1)
        {
            std::cerr << "findRow broke" << std::endl;
            exit(-1);
        }
        currNode = origNode;
        currCycleNum.push_back(origNode);
        while(nextNode != origNode)
        {
            nextNode = findNextNode(currNode, currID);
            if(nextNode == -1)
            {
                std::cerr << "findNextNode broke" << std::endl;
                exit(-1);
            }
            std::cout << toString(nextNode, currNode, currID);
            currCycleStr.push_back(toString(nextNode, currNode, currID));
            currCycleNum.push_back(nextNode);
            currNode = nextNode;
        }
        std::cout << std::endl;
        update(currID, currCycleStr, currCycleNum, nextNode);
        currCycleNum.erase(currCycleNum.begin(), currCycleNum.end());
    }
    std::cout << std::endl;
    printMat();
}


/*if there is only one cycle, it outputs the cycle*/
bool Graph::alreadyDone(std::ostream& output)
{
    if(allCyclesStr.size() == 1)
    {
        for(int i = 0; i < allCyclesStr[0].size(); i++)
        {
            output << allCyclesStr[0][i];
        }
        output << std::endl;
        return true;
    }
    return false;
}

/*puts the start of each cycle into the vector*/
void Graph::computeStarts(std::vector<int>& startOfCycles)
{
    for(int i = 0; i < allCyclesNum.size(); i++)
    {
        startOfCycles.push_back(allCyclesNum[i][0]);
    }
}

/*checks to see if the currNode has a cycle that goes off of it. Returns the row the cycle starts on if found and the currNode if not found*/
int Graph::nextEdge(int currNode, vector<int>& startOfCycles)
{
    for(int i = 1; i < startOfCycles.size(); i++)
    {
        if(currNode == startOfCycles[i])
        {
            startOfCycles.pop_back();
            return i;
        }
    }
    return -1;
}

void Graph::computeTour(std::ostream& output)
{
    findCycles();
    if(alreadyDone(output)) return;
    
    std::vector<int> startOfCycles;
    computeStarts(startOfCycles);
    
    int currRow = 0;
    computeTour(startOfCycles, currRow);
    
    output << tour << std::endl;
}

void Graph::computeTour(std::vector<int> startOfCycles, int currRow)
{
    for(int currCol = 0; currCol < allCyclesNum[currRow].size(); currCol++)
    {
        int currNode = allCyclesNum[currRow][currCol];
        int newStart = nextEdge(currNode, startOfCycles);
        if(newStart != -1)
        {
            std::cout << "new cycle" << std::endl;
            computeTour(startOfCycles, newStart);
            tour += allCyclesStr[currRow][currCol];
            std::cout << allCyclesStr[currRow][currCol];
        }
        else
        {
            tour += allCyclesStr[currRow][currCol];
            std::cout << allCyclesStr[currRow][currCol];
        }
    }
}



#endif /* graph_h */
