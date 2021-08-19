#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
给定一个单链表的头节点 head，实现一个调整单链表的函数，使得每 K 个节点之间逆序，
如果最后不够 K 个节点一组，则不调整最后几个节点。
例如：
链表：1->2->3->4->5->6->7->8->null，K=3。
调整后为：3->2->1->6->5->4->7->8->null。其中 7、8 不调整，因为不够一组。
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
    for(auto c = head; c->next != nullptr; c = c->next)
    {
        std::cout << c->value << "->";
    }
     std::cout << "\b\b  " << std::endl;
}


template<typename T>
Node<T>* listReverseKNodes(Node<T> *head, int k)
{   
    if(nullptr == head || k < 2) {
        return head;
    }

    Node<T>* cur = head;
    Node<T>* start, *pre, *end;
    start = pre = end = nullptr;

    int count = 1;
    while(cur != nullptr)
    {
        if(count == k)
        {
            count = 1;
            start = pre == nullptr ? head : pre->next;
            head = start == head ? cur : head;
            end = cur;
            printList(head);
            if(pre != nullptr)
            {
                pre->next = end;
            }
            pre = start;
            while(pre != end)
            {
                auto cur2 = start->next;
                start->next = cur2->next;
                cur2 ->next = pre;
                pre = cur2;
            }
            pre = start;
            cur = pre->next;
        }
        cur = cur->next;
        count++;
    }
    return head;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {1,2,3,4,5,6,7,8,9})
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
    printList(listReverseKNodes(head, 3));
    return 0;
}

