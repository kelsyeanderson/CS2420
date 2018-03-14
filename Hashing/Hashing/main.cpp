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
void toHash(ifstream inFile, HashTable<std::string, FirstWordInfo>& Poem);
void generatePoem(HashTable<std::string, FirstWordInfo> Stats, vector<std::string> poem, int size, std::string firstWord);
bool frequency(HashTable<std::string, FirstWordInfo> Stats, FirstWordInfo* firstWord);

int main()
{
    HashTable<std::string, FirstWordInfo> Poem;
    vector<std::string> computerWrittenPoem;
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
    
    std::cout << Poem.toString() <<std::endl;
}


void generatePoem(HashTable<std::string, FirstWordInfo> Stats, vector<std::string>& poem, int size, std::string firstWord)
{
    poem.push_back(firstWord);
    FirstWordInfo* word = Stats.find(firstWord);
    
    for(int i = 0; i < size; i++)
    {
        int num = word->getCount();
        
        int count = 0;
        while(num > 0)
        {
            num -= word->secondWordList[count].m_count;
            count++;
        }
        poem.push_back(word->secondWordList[count].m_word);
        word = Stats.find(word->secondWordList[count].m_word);
    }
}




