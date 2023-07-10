#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include <string>
using namespace std;

class NodeAVL
{
public:
    string word;        // word of the current node
    int count;          // Number of times a word exists in the text
    NodeAVL* left;      // Left child of current node
    NodeAVL* right;     // Right child of current node
    int height;         // Height of current node
};

class AVL
{
public:
    AVL(){};                                // Empty constructor
    int setBalance(NodeAVL*);               // Find the balance of current node
    int height(NodeAVL*);                   // returns the height of current node
    int setHeight(NodeAVL*, NodeAVL*);      // Determine the height of the node
    NodeAVL* leftRotate(NodeAVL* &);        // Left rotate
    NodeAVL* rightRotate(NodeAVL* &);       // Right rotate
    NodeAVL* insertWord(NodeAVL*, string);  // Insertion
    NodeAVL *deleteWord(NodeAVL*, string);  // Deletion
    int searchWord(NodeAVL*, string);       // Search word
    void inOrder(NodeAVL*);                 // inorder access of AVL Tree
    void preOrder(NodeAVL*);                // preorder access of AVL Tree
    void postOrder(NodeAVL*);               // postorder access of AVL Tree
};

#endif // AVL_H_INCLUDED
