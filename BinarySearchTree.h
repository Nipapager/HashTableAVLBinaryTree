#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED
#include <string>
using namespace std;

//Nodes of Binary Tree Search
class NodeBST
{
public:
    string word;     // word of the current node
    int count;       // Number of times a word exists in the text
    NodeBST* left;   // Left child of current node
    NodeBST* right;  // Right child of current node
};


class BinarySearchTree
{
public:
    BinarySearchTree(){};                     // Empty constructor
    NodeBST* insertWord(NodeBST*, string);   // Insertion
    NodeBST* deleteWord(NodeBST*, string);   // Deletion
    int searchWord(NodeBST*, string);       // Search word
    void inOrder(NodeBST*);                 // inorder access of tree
    void preOrder(NodeBST*);                // preorder access of tree
    void postOrder(NodeBST*);               // postorder access of tree
};




#endif // BINARYSEARCHTREE_H_INCLUDED
