#include "node.h"
#include <iostream>

/*
用递归和非递归方式，分别按照二叉树先序、中序和后序打印所有的节点。我们约定：先
序遍历顺序为根、左、右；中序遍历顺序为左、根、右；后序遍历顺序为左、右、根。
*/
using namespace std;

void preOrderRecur(Node<int> *root)
{
    if(root == nullptr)
    {
        return;
    }
    cout << root->value << ", ";
    preOrderRecur(root->left);
    preOrderRecur(root->right);
}

void inOrderRecur(Node<int> *root)
{
    if(root == nullptr)
    {
        return;
    }
    inOrderRecur(root->left);
    cout << root->value << ", ";
    inOrderRecur(root->right);
}

void postOrderRecur(Node<int> *root)
{
    if(root == nullptr)
    {
        return;
    }
    postOrderRecur(root->left);
    postOrderRecur(root->right);
    cout << root->value << ", ";
}

int main()
{
    Node<int> *root = new Node<int>({1,2,3,-1,4,5,6,7,8,9,10,-1,-1,-1,-1,-1,11,12,-1,-1,-1,13,14,15,16});
    preOrderRecur(root);cout << endl;
    inOrderRecur(root);cout << endl;
    postOrderRecur(root);cout << endl;
     
}