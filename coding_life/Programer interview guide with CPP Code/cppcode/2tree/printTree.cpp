/*
二叉树可以用常规的三种遍历结果来描述其结构，但是不够直观，尤其是二叉树中有重复
值的时候，仅通过三种遍历的结果来构造二叉树的真实结构更是难上加难，有时则根本不可能。
给定一棵二叉树的头节点 head，已知二叉树节点值的类型为 32 位整型，请实现一个打印二叉
树的函数，可以直观地展示树的形状，也便于画出真实的结构。
*/
#include "printTree.h"
using namespace std;

void printTree(Node<int> *head) {
    cout << INT_MAX << " " << INT_MIN << endl;
    cout << "Binary Tree:" << endl;
    printInOrder(head, 0, "H", 17);
    cout << endl;
}   

void printInOrder(Node<int> *head, int height, string to, int len) 
{
    if (head == nullptr)
    {
        return;
    }
    printInOrder(head->right, height + 1, "v", len);
    std::stringstream ss;
    ss << to << head->value << to;
    string val = ss.str();
    int lenM = val.length();
    int lenL = (len - lenM) / 2;
    int lenR = len - lenM - lenL;
    val = string(lenL, ' ') + val + string(lenR, ' ');
    cout << string(height * len, ' ') + val << endl;
    printInOrder(head->left, height + 1, "^", len);
}

/*
int main()
{
    Node<int> *root = new Node<int>({1,2,3,4,-1,5,6,-1,7});
    printTree(root);
}
*/
