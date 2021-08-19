#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
一个环形单链表从头节点 head 开始不降序，同时由最后的节点指回头节点。给定这样一个
环形单链表的头节点 head 和一个整数 num，请生成节点值为 num 的新节点，并插入到这个环
形链表中，保证调整后的链表依然有序。
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
void printListCycle(Node<T> *head)
{
    if(head == nullptr)
    {
        return;
    }
    std::cout << head->value << "->";
    for(auto c = head->next; c != head ; c = c->next)
    {
        std::cout << c->value << "->";
    }
     std::cout << "\b\b  " << std::endl;
}


template<typename T>
Node<T>* insertNum(Node<T> *head, T number)
{   

    auto new_node = new Node<decltype(number)>(number);
    if(head == nullptr)
    {
        new_node->next = new_node;
        return new_node;
    }
    auto cur = head->next;
    auto pre = head;
    while(cur != head)
    {
        if(pre->value <= number && cur->value >= number)
        {
            break;
        }
        cur = cur->next;
        pre = pre->next;
    }
    pre->next = new_node;
    new_node->next = cur;
    return head->value <= number ? head : new_node;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {1,2,3,6,7,8,9,10})
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
    c->next = head;

    printListCycle(head);
    head = insertNum(head, 4);
    printListCycle(head);
    head = insertNum(head, 12);
    printListCycle(head);
    head = insertNum(head, 0);
    printListCycle(head);

    return 0;
}

