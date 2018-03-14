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

ifstream inputFile(std::string txtName);
void clean(std::string & nextToken);
void toHash(ifstream inFile, HashTable<std::string, FirstWordInfo>& Poem);
void generatePoem(HashTable<std::string, FirstWordInfo> Stats, vector<std::string>& poem, int size, std::string firstWord);
void printGreen(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem);
void printClown(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem);
void printInch(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem);
void printPoe(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem);
void printSeuss(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem);


int main()
{
    HashTable<std::string, FirstWordInfo> GreenPoem;
    vector<std::string> computerGreenPoem;
    printGreen(GreenPoem, computerGreenPoem);
    
    HashTable<std::string, FirstWordInfo> ClownPoem;
    vector<std::string> computerClownPoem;
    printClown(ClownPoem, computerClownPoem);
    
    HashTable<std::string, FirstWordInfo> InchPoem;
    vector<std::string> computerInchPoem;
    printInch(InchPoem, computerInchPoem);
    
    
    HashTable<std::string, FirstWordInfo> PoePoem;
    vector<std::string> computerPoePoem;
    printPoe(PoePoem, computerPoePoem);
    
    HashTable<std::string, FirstWordInfo> SeussPoem;
    vector<std::string> computerSeussPoem;
    printSeuss(SeussPoem, computerSeussPoem);
    

    return 0;
}

/*Creates an ifstream from the inputed txt name and verifies that it opens correctly*/
ifstream inputFile(std::string txtName)
{
    ifstream inFile;
    inFile.open(txtName);
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
    srand(time(0));
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


/*---------------------------Print-Functions----------------------------------------*/

void printGreen(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem)
{
    std::string txtName = "green.txt";
    std::cout << txtName << std::endl;
    std::cout << "------------------------\n\n";
    std::string firstWord = "sam";
    int length = 20;
    
    toHash(inputFile(txtName), Poem);
    std::cout << Poem.toString() <<std::endl;
    generatePoem(Poem, computerWrittenPoem, length, firstWord);
}

void printClown(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem)
{
    std::string txtName = "clown.txt";
    std::cout << "\n\n------------------------\n" << txtName << std::endl;
    std::cout << "------------------------\n\n";
    std::string firstWord = "go";
    int length = 20;
    
    toHash(inputFile(txtName), Poem);
    std::cout << Poem.toString() <<std::endl;
    generatePoem(Poem, computerWrittenPoem, length, firstWord);
}

void printInch(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem)
{
    std::string txtName = "inch.txt";
    std::cout << "\n\n------------------------\n" << txtName << std::endl;
    std::cout << "------------------------\n\n";
    std::string firstWord = "computer";
    int length = 50;
    
    toHash(inputFile(txtName), Poem);
    generatePoem(Poem, computerWrittenPoem, length, firstWord);
}

void printPoe(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem)
{
    std::string txtName = "poe.txt";
    std::cout << "\n\n------------------------\n" << txtName << std::endl;
    std::cout << "------------------------\n\n";
    std::string firstWord = "nevermore";
    int length = 50;
    
    toHash(inputFile(txtName), Poem);
    generatePoem(Poem, computerWrittenPoem, length, firstWord);
}

void printSeuss(HashTable<std::string, FirstWordInfo>& Poem, vector<std::string>& computerWrittenPoem)
{
    std::string txtName = "seuss.txt";
    std::cout << "\n\n------------------------\n" << txtName << std::endl;
    std::cout << "------------------------\n\n";
    std::string firstWord = "mordecai";
    int length = 50;
    
    toHash(inputFile(txtName), Poem);
    generatePoem(Poem, computerWrittenPoem, length, firstWord);
}




