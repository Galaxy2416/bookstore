#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
给定一个链表的头节点 head 和一个整数 num，请实现函数将值为 num 的节点全部删除。
例如，链表为 1->2->3->4->null，num=3，链表调整后为：1->2->4->null。
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
Node<T>* removeValue(Node<T> *head, T value)
{   
    if(nullptr == head) {
        return nullptr;
    }
    auto tmp = head;
    while(head->value == value)
    {
        tmp = head->next;
        delete head;
        head = tmp;
    }
    
    auto ret_head = head;
    while(head->next != nullptr)
    {
        if(head->next->value == value)
        {
            tmp = head->next;
            head->next = tmp->next;
            delete tmp;
            continue;
        }
        head = head->next;
    }
    return ret_head;
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
    head = removeValue(head, 3);
    printList(head);
    return 0;
}

