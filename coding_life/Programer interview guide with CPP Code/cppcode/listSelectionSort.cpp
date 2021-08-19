#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
给定一个无序单链表的头节点 head，实现单链表的选择排序。
要求：额外空间复杂度为 O(1)
*/

using namespace std;

template<typename T>
struct Node 
{
    Node(int i)
    :value(i), next(nullptr)
    {
    }
    T value;
    Node<T> *next;
};

template<typename T>
void printList(Node<T> *head)
{
    for(auto c = head; c != nullptr; c = c->next)
    {
        std::cout << c->value << "->";
    }
     std::cout << "\b\b  " << std::endl;
}


template<typename T>
Node<T>* selectionSort(Node<T> *head)
{   
    if(head == nullptr)
    {
        return nullptr;
    }
    Node<T> *pre = head;
    Node<T> *cur = head->next;
    while(cur != nullptr)
    {
        if(cur->value < head->value)
        {
            auto chead = head;
            pre->next = cur->next;
            head = cur;
            head->next = chead;
            cur = pre->next;
            continue;
        }
        auto cur_new = head->next;
        auto pre_new = head;
        while(cur_new != cur && cur_new->value < cur->value)
        {
            cur_new = cur_new->next;
            pre_new = pre_new->next;
        }
        if(cur_new != cur)
        {
            pre_new->next = cur;
            pre->next = cur->next;
            cur->next = cur_new;
        }
        else
        {
            pre = pre->next;
        }
        cur = pre->next;
    }
    return head;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {3,3,3,1,2,3,4,3,5,6,7,1,1,1,8,3,9,3,3})
    {
        if(head == nullptr)
        {
            head = new Node<decltype(i)>(i);
            c = head;
        }
        else
        {
            c->next = new Node<decltype(i)>(i);
            c = c->next;
        }
    }

    printList(head);
    printList(selectionSort(head));
    // printList(head);
    return 0;
}

