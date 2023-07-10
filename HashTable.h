#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <string>
#include <iostream>
using namespace std;

class NodeHash
{
public:
    string word;                     // word of the current node
    int count=0;                     // word of the current node
    NodeHash(string w): word(w) {};  // constructor that inserts the word w to word variable
};

class HashTable
{
private:
    NodeHash **words;                // Dynamically create an array of NodeHash items
    int size = 15679 ;                  // A random initial size for the hash table
    int position;                    // Position of a word in the hash table

public:
    HashTable();                     // constructor that dynamically creates the words array
    int findHash(string);            // hash function that determines the position of a word
    void insertWord(string);         // insert a word in the hash table
    void expandTable();              // expand the size of the hash table
    int searchWord(string);          // search a word in the hash table


};



#endif // HASHTABLE_H_INCLUDED
