#include <iostream>
#include "AVL.h"

using namespace std;

int AVL::setBalance(NodeAVL* node)
{
    // If node is null then its balance is zero
    if (!node)
        return 0;
    return height(node->left) - height(node->right);
}

int AVL::height(NodeAVL* node)
{
    // If node is null then its height is 0
    if (!node)
        return 0;
    return node->height;
}

int AVL::setHeight(NodeAVL* leftChild, NodeAVL* rightChild)
{
    // find the height of node's left and right children
    int leftHeight = height(leftChild);
    int rightHeight = height(rightChild);

    // Height of a node is equal to the height of his child with the biggest height, increased by 1
    if (leftHeight > rightHeight)
        return 1+leftHeight;
    else
        return 1+rightHeight;

}



NodeAVL* AVL::leftRotate(NodeAVL* &node)
{
    NodeAVL* temp = node->right;    // Use the right child of node
    NodeAVL* temp2 = temp->left;    // Use the left child of node's right child
    temp->left = node;
    node->right = temp2;
    node->height = setHeight(node->left, node->right);  //update height
    temp->height = setHeight(temp->left, temp->right);  //update height

    return temp;
}

NodeAVL* AVL::rightRotate(NodeAVL* &node)
{
    NodeAVL* temp = node->left;     // Use the left child of node
    NodeAVL* temp2 = temp->right;   // Use the right child of node's left child
    temp->right = node;
    node->left = temp2;
    node->height = setHeight(node->left, node->right);  // update height
    temp->height = setHeight(temp->left, temp->right);  // update height

    return temp;
}

NodeAVL* AVL::insertWord(NodeAVL* node, string w)
{
    // If node is null
    if (!node)
    {
        node = new NodeAVL;
        node->word = w;
        node->count = 1;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    // Checks if word w is smaller, bigger or equal to the node's word
    if (w > node->word)
        node->right = insertWord(node->right, w);
    else if (w < node->word)
        node->left = insertWord(node->left, w);
    else
    {
        (node->count)++;
        return node;
    }

    node->height = setHeight(node->left, node->right);  // determine the height of the node
    int balance = setBalance(node);                     // determine the balance of the node

    // if AVL tree is not balanced and left child has bigger height than right child
    if (balance > 1)
    {
        if (w < node->left->word)
            return rightRotate(node); // if word is the left child of node's left child then rightrotate
        if (w > node->left->word)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);   // if word is the right child of node's left child then leftrotate first and then rightrotate
        }
    }

    // if AVL tree is not balanced and right child has bigger height than left child
    if (balance < -1)
    {
        if (w > node->right->word)
            return leftRotate(node); // if word is the right child of node's right child then leftrotate
        if (w < node->right->word)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node); // if word is the left child of node's right child then rightrotate first and then leftrotate
        }
    }

    return node;
}

NodeAVL* AVL::deleteWord(NodeAVL* node, string w)
{
    // Checks if word w is smaller, bigger or equal to the node's word
     if (w > node->word)
        node->right = deleteWord(node->right, w);
    else if (w < node->word)
        node->left = deleteWord(node->left, w);
    else
    {
        // If word exists more than 1 time in the AVL tree then remove its count by 1 and return
        if (node->count > 1)
        {
            node->count--;
            return node;
        }

        // If node has no children
        if (!node->left && !node->right)
        {
            node = nullptr;
            return node;

        }

         // If node has only right child
        else if (!node->left)
        {
            NodeAVL* temp;
            temp = node->right;
            delete node;    // delete node
            return temp;    // replace the node with its right child
        }

        // If node has only left child
        else if (!node->right)
        {
            NodeAVL* temp;
            temp = node->left;
            delete node;    // delete node
            return temp;    // replace the node with its left child
        }

        // If node has both left and right child
        if (node->right && node->left)
        {
            NodeAVL* temp;
            temp = node->right;
            while (temp->left)
                temp = temp->left;
            node->word = temp->word;
            node->right = deleteWord(node->right, node->word);
        }
    }


    node->height = setHeight(node->left, node->right); // update the height after deletion of node

    int nodeBalance = setBalance(node);                 // Check if balance of tree ruined
    int leftChildBalance = setBalance(node->left);
    int rightChildBalance = setBalance(node->right);

    // if AVL tree is not balanced and left child has bigger height than right child
    if (nodeBalance > 1)
    {
        if (leftChildBalance>=0)
            return rightRotate(node); // if word is the left child of node's left child then rightrotate
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node); // if word is the right child of node's left child then leftrotate first and then rightrotate
        }
    }

    // if AVL tree is not balanced and right child has bigger height than left child
    if (nodeBalance < -1)
    {
        if (rightChildBalance<=0)
            return leftRotate(node); // if word is the right child of node's right child then leftrotate
        else
        {
            node->right = rightRotate(node->right);
            return leftRotate(node); // if word is the left child of node's right child then rightrotate first and then leftrotate
        }
    }

    return node;

}

int AVL::searchWord(NodeAVL* node, string w)
{
    // if node is null word w doesn't exist
    if (!node)
        return 0;

    // Checks if word w is smaller, bigger or equal to the node's word
    if (w > node->word)
        return searchWord(node->right, w);
    else if (w < node->word)
        return searchWord(node->left, w);
    else
        return node->count; // If word is found then return its count
}


void AVL::inOrder(NodeAVL* node)
{
    if(node == nullptr)
        return;

    inOrder(node->left);
    cout << node->word << endl;
    inOrder(node->right);

}

void AVL::preOrder(NodeAVL* node)
{
    if (!node)
        return;
    cout << node->word << endl;
    preOrder(node->left);
    preOrder(node->right);
}

void AVL::postOrder(NodeAVL* node)
{
    if (!node)
        return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->word << endl;
}


