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
    std::vector<std::vector<int>> adjMat;
    std::vector<std::vector<int>> allCycles;
    
    Graph(std::string txtName, std::ostream& output); // constructor for Graph
    void printMat(std::ostream & output = std::cout); //prints the current adjMat
    void computeTour(std::ostream& output); //finds a path in the matrix that hits every edge exactly once
    
private:
    /*helper functions for constructor*/
    void eulerTourCheck(); //checks that all the nodes have an even number of edges
    void setMat(std::ifstream& inFile); //sets the adjMat based on the txt file
    
    /*findCycles and helper functions*/
    void findCycles(); //puts all the different cycles into allCyclesNum
    bool isAdjMatDone(); //returns true if there are no -1s in the matrix
    int findRow(); //finds the first row that has a -1 in it
    int findNextNode(int currRow, int currID); //returns the column of the first -1 in a given row, sets those to currID in the matrix
    void update(int& currID, vector<int>& currCycle, int& nextNode); //updates the currID, nextNode, and allCycles after a cycle run
    std::string toString(int toNode, int fromNode, int cycleID); //creates a string ouput for two nodes
    
    /*computeTour helper functions*/
    void mergeCycles(std::vector<int> startOfCycles, int currRow); //recursively merges the cycles in allCycles
    void mergeCycles(std::ostream& output = std::cout); //helper function for recursive merge function
    std::vector<int> computeStarts(); //makes a vector that holds the first node in every cycle found in allCycles
    int nextEdge(int currNode, vector<int>& startofCycles); //finds if the inputted node has a full cycle that goes off from it
    bool alreadyDone(std::ostream& output = std::cout); //checks if the allCycles vector only has one cycle in it
    void printCycles(std::ostream& output = std::cout); //prints all the cycles in the allCycles function

    
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

/*--------------------------findCycles and it's helper functions--------------------------------------*/

/*finds cycles that combined hit every edge in the matrix. Puts the different cycles in the allCycles vector*/
void Graph::findCycles()
{
    int currID = 1;
    int origNode;
    std::vector<int> currCycle;
    int nextNode = -1;
    int currNode;
    
    /*loops throught the adjMat until it has grabbed all the edges*/
    while(!isAdjMatDone())
    {
        origNode = findRow();
        if(origNode == -1)
        {
            std::cerr << "findRow broke" << std::endl;
            exit(-1);
        }
        currNode = origNode;
        currCycle.push_back(origNode);
        
        /*loops until it creates a full cycle*/
        while(nextNode != origNode)
        {
            nextNode = findNextNode(currNode, currID);
            if(nextNode == -1)
            {
                std::cerr << "findNextNode broke" << std::endl;
                exit(-1);
            }
//            std::cout << toString(nextNode, currNode, currID); //uncomment to check for different cycles
            currCycle.push_back(nextNode);
            currNode = nextNode;
        }
        update(currID, currCycle, nextNode);
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

/*incraments currID, puts currCycle into allCyclesNum, erases the currCycle, and sets nextNode to -1*/
void Graph::update(int& currID, vector<int>& currCycle, int& nextNode)
{
    currID++;
    allCycles.push_back(currCycle);
    currCycle.erase(currCycle.begin(), currCycle.end());
    nextNode = -1;
}

/*converts the nodes into an output that shows the where the path is going and what the cycle ID is*/
std::string Graph::toString(int toNode, int fromNode, int cycleID)
{
    ostringstream os;  // allows string to act like stream to use stream operations
    char t = toNode + 'A';
    char f = fromNode + 'A';
    os << f << "-"<<t  << "(" << cycleID << ")" << "   ";
    return os.str();
}

/*------------------------------------computeTour and it's helper functions--------------------------------------------*/

/*calls the findCycles function and mergeCycles functions*/
void Graph::computeTour(std::ostream& output)
{
    findCycles();
    mergeCycles(output);
}

/*checks if findCycles only found one cycle, so it doesn't need to find another, then puts the cycle/cycles in the output. It then prints the matrix and makes a vector that holds the first node in each cycle. Finally it calls the merge cycles function and puts the tour into the output*/
void Graph::mergeCycles(std::ostream& output)
{
    if(alreadyDone(output)) return;
    else printCycles(output);
    printMat(output);
    
    std::vector<int> startOfCycles = computeStarts();
    
    mergeCycles(startOfCycles, 0);
    
    output << "Tour: " << tour << std::endl;
}

/*recursively merges the smaller cycles into a tour. Appends the path onto the string tour*/
void Graph::mergeCycles(std::vector<int> startOfCycles, int currRow)
{
    for(int currCol = 0; currCol < allCycles[currRow].size(); currCol++)
    {
        int currNode = allCycles[currRow][currCol];
        int newStart = nextEdge(currNode, startOfCycles);
        if(newStart != -1)
        {
            mergeCycles(startOfCycles, newStart);
        }
        else
        {
            tour += allCycles[currRow][currCol] + 'A';
            tour += " ";
        }
    }
}

/*switches the cycles into letters and then puts them into output*/
void Graph::printCycles(std::ostream& output)
{
    for(int i = 0; i < allCycles.size(); i++)
    {
        output << "Cycle " << i << ": ";
        for (int j = 0; j < allCycles[i].size(); j++)
        {
            char tempLetter = allCycles[i][j] + 'A';
            output << tempLetter << " ";
        }
        output << std::endl;
    }
}

/*if there is only one cycle, it outputs the cycle*/
bool Graph::alreadyDone(std::ostream& output)
{
    if(allCycles.size() == 1)
    {
        for(int i = 0; i < allCycles[0].size(); i++)
        {
            char tempLetter = allCycles[0][i] + 'A';
            output << tempLetter << " ";
        }
        output << std::endl;
        return true;
    }
    return false;
}

/*puts the start of each cycle into the vector*/
std::vector<int> Graph::computeStarts()
{
    std::vector<int> startOfCycles;
    for(int i = 0; i < allCycles.size(); i++)
    {
        startOfCycles.push_back(allCycles[i][0]);
    }
    return startOfCycles;
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





#endif /* graph_h */
