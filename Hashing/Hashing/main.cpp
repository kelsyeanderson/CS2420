//Kelsye Anderson
//A02093326

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "FollowingWordInfo.hpp"
#include "FirstWordInfo.hpp"
#include "HashTable.h"

ifstream inputFile();
void clean(std::string & nextToken);
void toHash(ifstream inFile, HashTable<std::string, FirstWordInfo> Poem);

int main()
{
    HashTable<std::string, FirstWordInfo> Poem;
    toHash(inputFile(), Poem);
    
    return 0;
}




/*Creates an ifstream from the inputed txt name and verifies that it opens correctly*/
ifstream inputFile()
{
    std::string txt;
    std::cout << "File Name: ";
    cin >> txt;
    ifstream inFile;
    inFile.open(txt);
    if (!inFile)
    {
        std::cout << "File not found :(" << std::endl;
        exit(-1);
    }
    return inFile;
}

/*Removes punctuation and special characters. Makes everything lowercase*/
void clean(std::string & nextToken)
{
    for (int i = 0; i < nextToken.length();)
    {
        if (nextToken[i] >255 || nextToken[i] < 0 || ispunct(nextToken[i]))
            nextToken.erase(i, 1);
        else {
            nextToken[i] = tolower(nextToken[i]);
            i++;
        }
    }
}

/*Puts the words from inFile into a hash table.*/
void toHash(ifstream inFile, HashTable<std::string, FirstWordInfo> Poem)
{
    std::string initializer;
    inFile >> initializer;
    clean(initializer);
    std::string previous;
    inFile >> previous;
    clean(previous);
    
    FirstWordInfo input(initializer);
    input.updateList(previous);
    Poem.insert(initializer, &input);
    
    while(!inFile.eof())
    {
        std::string next;
        inFile >> next;
        clean(next);
        
        FirstWordInfo* hashPos = Poem.find(previous);
        if (hashPos != nullptr)
        {
            hashPos->incrementCount();
            hashPos->updateList(next);
        }
        else
        {
            FirstWordInfo input(previous);
            input.updateList(next);
            Poem.insert(previous, &input);
        }
    }
    
    Poem.toString();
}





