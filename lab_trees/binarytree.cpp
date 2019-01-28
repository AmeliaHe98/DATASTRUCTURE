/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file, as well as binarytree.h.
 */

#include <iostream>

using namespace std;
using std::stack;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>:: height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function, with an additional
 * Node* parameter to allow for recursive calls. NOTE: use this as an example
 * for writing your own private helper functions.
 * @param subRoot
 * @return The height of the subtree.
 */
template <typename T>
int BinaryTree<T>:: height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    printLeftToRight(root);

    // Do not remove this line - used for correct print output
    cout << endl;
}

template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
    if (subRoot == NULL)
        return;
    printLeftToRight(subRoot->left);
    cout << subRoot->elem << ' ';
    printLeftToRight(subRoot->right);
}
/**
 * Flips the tree over a vertical axis, modifying the tree itself
 * (i.e. not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}


template <typename T>
typename BinaryTree<T>::Node * BinaryTree<T>::mirror(Node * subRoot) const
{
    if(subRoot==NULL)
        return NULL;
    else{
        Node* temp = mirror(subRoot->left);
        subRoot->left = mirror(subRoot->right);
        subRoot->right = temp;
        return subRoot;
    }
}


/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    if(root==NULL)
        return;
    stack<T> temp_stack;
    preorder(root, temp_stack);

}

template <typename T>
void BinaryTree<T>::preorder(Node *subRoot, stack<T>& s) const
{
    if(subRoot==NULL)
        return;
    s.push(subRoot->elem);
    if(subRoot->left == NULL &&subRoot->right == NULL)
        printStack(s);
    else{
        if(subRoot->left!=NULL)
            preorder(subRoot->left, s);
        if(subRoot->right!=NULL)
            preorder(subRoot->right, s);
    }
    
}

template <typename T>
void BinaryTree<T>::printStack(stack<T>& s) const
{
    if(s.empty())
        return;
    cout<<"Path: ";
    while(!s.empty()){
        T temp = s.top();
        s.pop();
        cout<< temp;
        cout<<" ";
    }
    cout<<""<<endl;
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root.
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    if(root == NULL)
        return -1;
    int sum = 0;
    return sumDistances(root, sum);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node *subRoot, int sum) const
{
    if(subRoot == NULL)
        return 0;
    sum = sum + sumDistances(subRoot->left, sum+1)+ sumDistances(subRoot->right, sum+1);
    return sum;
}

/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // Your code here
    return false;
}
