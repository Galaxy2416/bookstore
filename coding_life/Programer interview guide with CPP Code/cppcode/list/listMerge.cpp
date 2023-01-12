#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
给定两个有序单链表的头节点 head1 和 head2，请合并两个有序链表，合并后的链表依然
有序，并返回合并后链表的头节点。
例如：
0->2->3->7->null
1->3->5->7->9->null
合并后的链表为：0->1->2->3->3->5->7->7->9->nul
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
Node<T>* merge(Node<T> *head1, Node<T> *head2)
{   
    if(head1 == nullptr || head2 == nullptr)
    {
        return head1 == nullptr ? head2 : head1;
    }
    Node<T> *head = head1->value < head2->value ? head1 : head2;
    auto cur1 = head == head1 ? head1 : head2;
    auto cur2 = head == head1 ? head2 : head1;
    Node<T>* pre = nullptr;
    Node<T>* cur = nullptr;
    while(cur1 != nullptr && cur2 != nullptr)
    {
        if(cur1->value <= cur2->value)
        {
            pre = cur1;
            cur1 = cur1->next;
        }
        else
        {
            cur=cur2->next;
            pre->next = cur2;
            cur2->next = cur1;
            pre=cur2;
            cur2=cur;
        }
    }
    pre->next = cur1 == nullptr ? cur2 : cur1;
    return head;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {0,2,3,7})
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

    Node<int> *head2 = nullptr;

    for(auto i : {1,3,5,7,9})
    {
        if(head2 == nullptr)
        {
            head2 = new Node<decltype(i)>(i);
            c = head2;
        }
        else
        {
            c->next = new Node<decltype(i)>(i);
            c = c->next;
        }
    }

    printList(head);
    printList(head2);
    printList(merge(head, head2));
    return 0;
}

