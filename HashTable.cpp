#include "HashTable.h"
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

HashTable::HashTable()
{
    words = new NodeHash*[size];
    for (int i=0; i<size; i++)
        words[i] = nullptr;         //dynamically create words array and initialize its cells values as null

}

int HashTable::findHash(string w)
{
    int hash=0;
    for (unsigned i=0; i < w.size(); i++)
        hash = hash*37 + (int)w[i];
    hash = hash%15679 ;
    if (hash < 0)
        hash += 15679 ;
    return hash;

}

void HashTable::insertWord(string w)
{
    NodeHash *newWord = new NodeHash(w);
    position = findHash(w);

    while (size <= position)
        expandTable();                      // if position is bigger than hash table's size then expand it


    // find an empty cell of hash table to place the new word
    while (words[position]!=nullptr)
    {

        if (words[position]->word == w)
        {
            words[position]->count++; // if word already exists increase its size by 1
            return;
        }
        position = position + 37*w.size(); // if position is occupied by another word then increase the position by 37*(word's size)
        while (size <= position)
            expandTable();

    }
    words[position] = newWord;      // initialize the word to the hash table
    words[position]->count = 1;
}

int HashTable::searchWord(string w)
{
    position = findHash(w);
    // Search the word w in the hash table
    for (int i=position; i<size; i+=w.size()*37)
    {
        if (words[i]->word == w)
            return words[i]->count; // If exists then return its size
    }
    return 0; // if it doesn't exist return 0
}

void HashTable::expandTable()
{
    NodeHash **newTable;
    newTable = new NodeHash*[size+465];
    for (int i=0; i<size; i++)
        newTable[i] = words[i];     // Copy the values of old hash table into the new bigger one.
    for (int i=size; i<size+465; i++)
        newTable[i] = nullptr;      // initialize the new cells of hash table as null
    size+=465;
    delete []words;
    words = newTable;
}
