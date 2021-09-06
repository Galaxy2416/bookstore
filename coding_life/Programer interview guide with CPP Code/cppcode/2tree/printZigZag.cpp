#include "node.h"
#include <iostream>
#include <deque>

/*
给定一棵二叉树的头节点 head，分别实现按层和 ZigZag 打印二叉树的函数。
*/
using namespace std;

template <typename T>
void printZigZap(Node<T> *root)
{
    std::deque<Node<T> *> mydeque;
    bool flag = true;
    if(root == nullptr)
    {
        return;
    }
    Node<T> *last, *nlast;
    last = root;
    nlast = nullptr;
    mydeque.push_back(root);
    while(!mydeque.empty())
    {
        if(flag)
        {
            cout << mydeque.front()->value << " ";
            if (mydeque.front()->left)  { mydeque.push_back(mydeque.front()->left); nlast = nlast ? nlast : mydeque.front()->left; }
            if (mydeque.front()->right) { mydeque.push_back(mydeque.front()->right); nlast = nlast ? nlast : mydeque.front()->right; }
            if (last == mydeque.front())
            {
                last = nlast;
                nlast = nullptr;
                flag = !flag;
                cout << endl;
            }
            mydeque.pop_front();
        }
        else
        {
            cout << mydeque.back()->value << " ";
            if (mydeque.back()->right) { mydeque.push_front(mydeque.back()->right); nlast = nlast ? nlast : mydeque.back()->right; }
            if (mydeque.back()->left)  { mydeque.push_front(mydeque.back()->left); nlast = nlast ? nlast : mydeque.back()->left; }

            if (last == mydeque.back())
            {
                last = nlast;
                nlast = nullptr;
                flag = !flag;
                cout << endl;
            }
            mydeque.pop_back();
        }
    }
}


int main()
{
    Node<int> *root = new Node<int>({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16});
    printZigZap(root);
}