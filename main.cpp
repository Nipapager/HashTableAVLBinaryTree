#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "BinarySearchTree.h"
#include "AVL.h"
#include "HashTable.h"


#define Q 10000                  // number of random words
#define P 246848/Q              // P helps on choosing random words

using namespace std;


bool readWords(BinarySearchTree& bst, NodeBST* &rootBST, AVL& avl, NodeAVL* &rootAVL, HashTable& ht, string *random)
{
    ifstream file;
    file.open("input.txt", ios::in);
    if (!file.is_open())
        return false;               // If file doesn't open return false

    string line;
    string word;
    int next_word =  rand()%P+1;    // Find the position of the next random word in the text file
    int curr_word = 0;              // Number of words read from text
    int i=0;                        // number of random word saved


    while (getline(file, line))     // Read text file line by line
    {
        word = "";                  // initialize string word as empty
        for (unsigned j=0; j<line.size(); j++)      // for each character of the line
        {
            if (line[j]>=65 && line[j]<=90)         // transform every capital letter into lowercase by using ASCII code
                line[j]+=32;

            if (line[j]>=97 && line[j]<=122)        // check if character is a letter between (a-z)
            {
                word+=line[j];
                if (j==line.size()-1)               // True only for the last word of each line
                {
                    bst.insertWord(rootBST, word);
                    rootAVL = avl.insertWord(rootAVL, word);
                    ht.insertWord(word);

                    curr_word++;
                    if (next_word == curr_word && i<Q)
                    {
                        random[i] = word;           // Save this word to the random words array
                        i++;
                        next_word += rand()%P+1;
                    }
                    word = "";
                }
            }
            else
            {
                if (!word.empty())
                {
                    if (!rootBST)                   // If Binary Search Tree is empty (only the first time)
                        rootBST = bst.insertWord(rootBST,word);
                    else
                        bst.insertWord(rootBST, word);
                    rootAVL = avl.insertWord(rootAVL, word);
                    ht.insertWord(word);
                    curr_word++;
                    if (next_word == curr_word && i<Q)
                    {
                        random[i] = word;           // Save this word to the random words array
                        i++;
                        next_word += rand()%P+1;
                    }
                    word = "";
                }
            }

        }
    }
    file.close();           // Close the file after reading the words
    return true;

}

void searchRandomWords(string *random, AVL& avl, BinarySearchTree& bst, HashTable& ht, NodeBST* rootBST, NodeAVL* rootAVL)
{
    double Avg_Time_Bst=0;              // Average time of Binary Search Tree
    double Avg_Time_Avl=0;              // Average time of AVL Tree
    double Avg_Time_Ht=0;               // Average time of Hash Table
    ofstream file;
    file.open("output.txt", ios::out);  // Results will be printed and saved the file "output.txt" of the project
    for (int i=0; i<Q; i++)
    {
        auto startBST = chrono::steady_clock::now();
        cout << i+1 << ". Word \"" << random[i] << "\" exists " <<  bst.searchWord(rootBST, random[i]) << " times! - USING BINARY TREE SEARCH" << endl;
        auto endBST = chrono::steady_clock::now();
        file << i+1 << ". Word \"" << random[i] << "\" exists " <<  bst.searchWord(rootBST, random[i]) << " times! - USING BINARY TREE SEARCH" << endl;
        Avg_Time_Bst += chrono::duration_cast<chrono::nanoseconds>(endBST - startBST).count();


        auto startAVL = chrono::steady_clock::now();
        cout << i+1 << ". Word \"" << random[i] << "\" exists " <<  avl.searchWord(rootAVL, random[i]) << " times! - USING AVL" << endl;
        auto endAVL = chrono::steady_clock::now();
        file << i+1 << ". Word \"" << random[i] << "\" exists " <<  avl.searchWord(rootAVL, random[i]) << " times! - USING AVL" << endl;
        Avg_Time_Avl += chrono::duration_cast<chrono::nanoseconds>(endAVL - startAVL).count();

        auto startHT = chrono::steady_clock::now();
        cout << i+1 << ". Word \"" << random[i] << "\" exists " <<  ht.searchWord(random[i]) << " times! - USING HASH TABLE" << endl;
        auto endHT = chrono::steady_clock::now();
        file << i+1 << ". Word \"" << random[i] << "\" exists " <<  ht.searchWord(random[i]) << " times! - USING HASH TABLE" << endl;
        Avg_Time_Ht += chrono::duration_cast<chrono::nanoseconds>(endHT - startHT).count();
    }

    cout << "\n==========================================================================================\n" << endl;
    file << "\n==========================================================================================\n" << endl;
    // nanoseconds to seconds by multiplying 0.000000001
    cout << "Time spent with Binary Search Tree method: " << Avg_Time_Bst*0.00000001/Q << " seconds" << endl;      // Print results
    cout << "Time spent with AVL Tree method: " << Avg_Time_Avl*0.00000001/Q << " seconds" << endl;                // Print results
    cout << "Time spent with Hash Table method: " << Avg_Time_Ht*0.00000001/Q << " seconds" << endl;               // Print results
    file << "Time spent with Binary Search Tree method: " << Avg_Time_Bst*0.000000001/Q << " seconds" << endl;      // Save results
    file << "Time spent with AVL Tree method: " << Avg_Time_Avl*0.000000001/Q << " seconds" << endl;                // Save results
    file << "Time spent with Hash Table method: " << Avg_Time_Ht*0.000000001/Q << " seconds" << endl;               // Save results

    file.close();       // Close file after saving results.

}

int main()
{

    BinarySearchTree bst;
    NodeBST *rootBST = nullptr;

    AVL avl;
    NodeAVL *rootAVL = nullptr;

    HashTable ht;

    string random[Q];

    if (readWords(bst, rootBST, avl, rootAVL, ht, random) == 0)
    {
        cout << "Error. Could not open the file" << endl;
        return 0;
    }

    searchRandomWords(random, avl, bst, ht, rootBST, rootAVL);
    return 0;
}
