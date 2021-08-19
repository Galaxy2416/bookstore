#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
给定一个单链表的头部节点 head，链表长度为 N，如果 N 为偶数，那么前 N/2 个节点算作
左半区，后 N/2 个节点算作右半区；如果 N 为奇数，那么前 N/2 个节点算作左半区，后 N/2+1
个节点算作右半区。左半区从左到右依次记为 L1->L2->…，右半区从左到右依次记为
R1->R2->…，请将单链表调整成 L1->R1->L2->R2->…的形式。
例如：
1->null，调整为 1->null。
1->2->null，调整为 1->2->null。
1->2->3->null，调整为 1->2->3->null。
1->2->3->4->null，调整为 1->3->2->4->null。
1->2->3->4->5->null，调整为 1->3->2->4->5->null。
1->2->3->4->5->6->null，调整为 1->4->2->5->3->6->null。
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
void relocate(Node<T> *head)
{   
    if(head == nullptr || head->next == nullptr)
    {
        return;
    }
    auto jump1 = head;
    auto jump2 = head;
    auto pre = jump1;
    while(jump2 != nullptr && jump2->next != nullptr)
    {
        pre = jump1;
        jump1 = jump1->next;
        jump2 = jump2->next->next;
    }
    pre->next = nullptr;
    // printList(jump1);
    // printList(head);
    auto cur = head; // jump1 is the mid start
    Node<T> *tmp = nullptr;
    while(cur != nullptr)
    {
        tmp = cur->next;
        cur->next = jump1;
        jump1 = jump1->next;
        if(tmp != nullptr)
            cur->next->next = tmp;
        cur=tmp;
        // printList(head);
        // printList(tmp);
        // printList(jump1);
    }
    return;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {0,1,2,3,4,5,6})
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
    relocate(head);
    printList(head);

    return 0;
}

