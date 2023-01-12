#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
分别实现反转单向链表和反转双向链表的函数。
如果链表长度为 N，时间复杂度要求为 O(N)，额外空间复杂度要求为 O(1)。
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
Node<T>* reverseSignleList(Node<T> *head)
{
    if(nullptr == head)
        return head;
    
    Node<T> *p = head;
    Node<T> *c = head->next;
    while(c != nullptr)
    {
        head->next = c->next;        
        c->next = p;
        p = c;
        c = head->next;
    }
    return p;
}

int main()
{   
    Node<int> *head = new Node<decltype(0)>(0);
    Node<int> *c = head;
    for(auto i : {1,2,3,4,5,6,7,8,9})
    {
        c->next = new Node<decltype(i)>(i);
        c = c->next;
    }
    // cout << head->value <<endl;
    printList(head);
    printList(reverseSignleList(head));
    return 0;
}
