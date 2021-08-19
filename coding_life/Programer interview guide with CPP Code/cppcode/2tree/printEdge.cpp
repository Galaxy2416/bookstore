#include "node.h"
#include <iostream>
#include <vector>

/*
给定一棵二叉树的头节点 head，按照如下两种标准分别实现二叉树边界节点的逆时针打印。
标准一：
1．头节点为边界节点。
2．叶节点为边界节点。
3．如果节点在其所在的层中是最左的或最右的，那么该节点也是边界节点。
标准二：
1．头节点为边界节点。
2．叶节点为边界节点。
3．树左边界延伸下去的路径为边界节点。
4．树右边界延伸下去的路径为边界节点。

1．如果节点数为 N，两种标准实现的时间复杂度要求都为 O(N)，额外空间复杂度要求都为
O(h)，h 为二叉树的高度。
2．两种标准都要求逆时针顺序且不重复打印所有的边界节点。
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

void getLeftRightMapCore(Node<int> *root, int l, vector<pair<Node<int>*, Node<int>*>> &lrmap)
{
    if(root == nullptr)
    {
        return;
    }
    getLeftRightMapCore(root->left, l+1, lrmap);
    getLeftRightMapCore(root->right, l+1, lrmap);
    lrmap[l].first = lrmap[l].first == nullptr ? root : lrmap[l].first;
    lrmap[l].second = root;
}
vector<pair<Node<int>*, Node<int>*>> getLeftRightMap(Node<int> *root)
{
    vector<pair<Node<int>*, Node<int>*>> lrmap (10, {nullptr, nullptr}); // max level 10
    getLeftRightMapCore(root, 0, lrmap);
    return lrmap;
}

void printLeafNotInMap(Node<int> *root, int l, const vector<pair<Node<int>*, Node<int>*>> &lrmap)
{
    if(root == nullptr)
    {
        return;
    }
    if(root->left == nullptr && root->right == nullptr && root != lrmap[l].first && root != lrmap[l].second)
    {
        cout << root->value << ", ";
    }
    printLeafNotInMap(root->left, l+1, lrmap);
    printLeafNotInMap(root->right, l+1, lrmap);
}

void printEdge1(Node<int> *root)
{   
    if(root == nullptr)
    {
        return;
    }
    auto lrmap = getLeftRightMap(root);
    auto it = lrmap.begin();
    while((*it).first != nullptr)
    { 
        cout << (*it).first->value << ", ";
        it++;
    }    
    printLeafNotInMap(root, 0, lrmap);
    while(--it != lrmap.begin()) // bypass the root
    { 
        cout << (*it).second->value << ", ";
    }
}

void printEdge2Left(Node<int> *root, bool p)
{
    if(root == nullptr)
    {
        return;
    }
    if(p || (!root->left && !root->right))
    {
        cout << root->value << ", ";
    }
    printEdge2Left(root->left, p);
    printEdge2Left(root->right, p && root->left == nullptr ? true : false);
}

void printEdge2Right(Node<int> *root, bool p)
{
    if(root == nullptr)
    {
        return;
    }
    printEdge2Right(root->left, p && root->right == nullptr ? true : false);
    printEdge2Right(root->right, p);
    if(p || (!root->left && !root->right))
    {
        cout << root->value << ", ";
    }
}

void printEdge2(Node<int> *root)
{
    if(root == nullptr)
    {
        return;
    }
    cout << root->value << ", ";
    if(root->left != nullptr && root->right != nullptr)
    {
        printEdge2Left(root->left, true);
        printEdge2Right(root->right, true);
    }
    else
    {
       printEdge2(root->left ? root->left : root->right); 
    }
}


int main()
{
    Node<int> *root = new Node<int>({1,2,3,-1,4,5,6,7,8,9,10,-1,-1,-1,-1,-1,11,12,-1,-1,-1,13,14,15,16});
    printEdge1(root);
    cout << endl;
    printEdge2(root);
    cout << endl;
}