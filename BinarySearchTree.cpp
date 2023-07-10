#include "BinarySearchTree.h"
#include <iostream>
using namespace std;


NodeBST* BinarySearchTree::insertWord(NodeBST* node, string w)
{
    // If node is null
    if (!node)
    {
        node = new NodeBST;
        node->word = w;
        node->count = 1;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    // Checks if word w is smaller, bigger or equal to the node's word
    if (w > node->word)
        node->right = insertWord(node->right, w);
    else if (w < node->word)
        node->left = insertWord(node->left, w);
    else
        (node->count)++;

    return node;
}

int BinarySearchTree::searchWord(NodeBST* node, string w)
{
    // If node is null
    if (!node)
        return 0;

    // Checks if word w is smaller, bigger or equal to the node's word
    if (w > node->word)
        return searchWord(node->right, w);
    else if (w < node->word)
        return searchWord(node->left, w);
    else
        return node->count;
}

NodeBST* BinarySearchTree::deleteWord(NodeBST* node, string w)
{
    // If node is null
    if (!node)
        return 0;

    // Checks if word w is smaller, bigger or equal to the node's word
     if (w > node->word)
        node->right = deleteWord(node->right, w);
    else if (w < node->word)
        node->left = deleteWord(node->left, w);
    else
    {
        // If word exists more than 1 time in the tree then remove its count by 1 and return
        if (node->count > 1)
        {
            node->count--;
            return node;
        }
        // If node has no children
        if (!node->left && !node->right)
        {
            node = nullptr; // delete node
            return node;

        }
        // If node has only right child
        else if (!node->left)
        {
            NodeBST* temp;
            temp = node->right;
            delete node;  // delete node
            return temp;  // replace the node with its right child
        }

        // If node has only left child
        else if (!node->right)
        {
            NodeBST* temp;
            temp = node->left;
            delete node; //delete node
            return temp; // replace the node with tis left child
        }
        // If node has both left and right child
        if (node->right && node->left)
        {
            NodeBST* temp;
            temp = node->right;
            while (temp->left != nullptr)
                temp = temp->left;

            node->word = temp->word;
            node->right = deleteWord(node->right, node->word);
        }
    }
    return node;
}

void BinarySearchTree::inOrder(NodeBST* node)
{
    if(node == nullptr)
        return;

    inOrder(node->left);
    cout << node->word << endl;
    inOrder(node->right);

}

void BinarySearchTree::preOrder(NodeBST* node)
{
    if (!node)
        return;
    cout << node->word << endl;
    preOrder(node->left);
    preOrder(node->right);
}

void BinarySearchTree::postOrder(NodeBST* node)
{
    if (!node)
        return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->word << endl;
}
