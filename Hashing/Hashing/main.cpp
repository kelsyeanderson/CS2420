//Kelsye Anderson
//A02093326

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "FollowingWordInfo.hpp"
#include "FirstWordInfo.hpp"
#include "HashTable.h"

ifstream inputFile();
void clean(std::string & nextToken);
void toHash(ifstream inFile, HashTable<std::string, FirstWordInfo>& Poem);
void generatePoem(HashTable<std::string, FirstWordInfo> Stats, vector<std::string>& poem, int size, std::string firstWord);
void printGreen(HashTable<std::string, FirstWordInfo> Poem, vector<std::string> computerWrittenPoem);

int main()
{
    HashTable<std::string, FirstWordInfo> Poem;
    vector<std::string> computerWrittenPoem;
    std::string firstWord = "go";
    int length = 20;
    
    toHash(inputFile(), Poem);
    generatePoem(Poem, computerWrittenPoem, length, firstWord);
    for(int i = 0; i < computerWrittenPoem.size(); i++)
    {
        std::cout << computerWrittenPoem[i] << " ";
    }
    std::cout << std::endl;
    
    //std::cout << Poem.toString() <<std::endl;
    
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

/*Puts the words from inFile into a hash table. Adds the next word into the vector for FirstWordInfo and increments
 the count*/
void toHash(ifstream inFile, HashTable<std::string, FirstWordInfo>& Poem)
{
    std::string initializer;
    inFile >> initializer;
    clean(initializer);
    
    std::string current;
    inFile >> current;
    clean(current);
    
    FirstWordInfo* input = new FirstWordInfo(initializer);
    input->updateList(current);
    Poem.insert(initializer, input);
    
    std::string next;
    while(inFile >> next)
    {
        clean(next);
        
        FirstWordInfo* hashPos = Poem.find(current);
        if (hashPos != nullptr)
        {
            hashPos->incrementCount();
            hashPos->updateList(next);
        }
        else
        {
            FirstWordInfo* input = new FirstWordInfo(current);
            input->updateList(next);
            Poem.insert(current, input);
        }
        
        current = next;
    }
}

/*Creates a poem based on the previously made Hash Table. couts words while inputting into poem vector*/
void generatePoem(HashTable<std::string, FirstWordInfo> Stats, vector<std::string>& poem, int size, std::string firstWord)
{
    FirstWordInfo* word = Stats.find(firstWord);
    if(word == nullptr)
    {
        std::cout << "Sorry, that word was not found in the poem you requested" << std::endl;
        exit(-1);
    }
    std::cout << firstWord << " ";
    poem.push_back(firstWord);
    
    for(int i = 0; i < size - 1; i++)
    {
        int wordCount = word->getCount();
        srand(time(NULL));
        int num = (rand() % wordCount) + 1;
        
        int count = -1;
        while(num > 0)
        {
            count++;
            num -= word->secondWordList[count].m_count;
        }
        std::string inputWord = word->secondWordList[count].m_word;
        poem.push_back(inputWord);
        word = Stats.find(inputWord);
        std::cout << inputWord << " ";
    }
    std::cout << std::endl;
}




