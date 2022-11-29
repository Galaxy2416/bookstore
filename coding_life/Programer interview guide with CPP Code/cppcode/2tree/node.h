// C++ program of AVL tree that 
// handles duplicates 
#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <queue>          // std::queue

using namespace std;

template<typename T>
struct Node
{
    Node(T _value):value(_value), left(nullptr), right(nullptr), parent(nullptr){}
    Node(std::initializer_list<T> list)
    {
        value = *list.begin();
        std::queue<Node<T>*> myqueue;
        myqueue.push(this);
        for(auto it = list.begin() + 1; it != list.end(); ++it)
        {
            auto the_node = myqueue.front(); myqueue.pop();
            the_node->left = !isEnd(*it) ? new Node(*it) : nullptr;
            if(the_node->left != nullptr) {
                myqueue.push(the_node->left);
				the_node->left->parent = the_node;
			}
            if(++it != list.end())
            {
                the_node->right = !isEnd(*it) ? new Node(*it) : nullptr;
            }
            else
            {
                 break;
            }
            if(the_node->right != nullptr) {
                myqueue.push(the_node->right);
				the_node->right->parent = the_node;
			}
        }
    }

    bool isEnd(int val)
    {
        return val == -1;
    }

    bool isEnd(string val)
    {
        return val == "#";
    }

    T value;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    /* data */
};

