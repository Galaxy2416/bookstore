#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
一种特殊的链表节点类描述如下：
template<typename T>
struct Node 
{
    Node(int i)
    :value(i), next(nullptr)
    {
    }
    T value;
    Node<T> *next;
    Node<T> *rand;
};

Node 类中的 value 是节点值，next 指针和正常单链表中 next 指针的意义一样，都指向下一
个节点，rand 指针是 Node 类中新增的指针，这个指针可能指向链表中的任意一个节点，也可
能指向 null。
给定一个由 Node 节点类型组成的无环单链表的头节点 head，请实现一个函数完成这个链
表中所有结构的复制，并返回复制的新链表的头节点。例如：链表 1->2->3->null，假设 1 的 rand
指针指向 3，2 的 rand 指针指向 null，3 的 rand 指针指向 1。复制后的链表应该也是这种结构，
比如，1′->2′->3′->null，1′的 rand 指针指向 3′，2′的 rand 指针指向 null，3′的 rand 指针指向 1′，
最后返回 1′。
阶：不使用额外的数据结构，只用有限几个变量，且在时间复杂度为 O(N)内完成原问题
要实现的函数。
*/

using namespace std;

template<typename T>
struct Node 
{
    Node<T>(T i)
    :value(i), next(nullptr), rand(nullptr)
    {
    }

    Node<T>(const Node<T> &node)
    {
        value = node.value;
        next = nullptr;
        rand = nullptr;
    }
    T value;
    Node<T> *next;
    Node<T> *rand;
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
Node<T>* listCopyWithRand(Node<T> *head)
{   
    if(head == nullptr)
        return nullptr;
    
    Node<T> *tmp = nullptr;
    // 1-1'-2-2'-3-3'-4-4'
    for(auto s = head; s != nullptr; s=tmp)
    {
        tmp = s->next;
        s->next = new Node<T>(*s);
        s->next->next = tmp;
    }
    printList(head);    
    // link random
    for(auto s = head; s != nullptr; s=s->next->next)
    {
        s->next->rand = s->rand == nullptr ? nullptr : s->rand->next;
    }

    // split
    tmp = head->next;
    auto head2 = tmp;
    head->next = tmp->next;
    for(auto s = head->next; s != nullptr; s = tmp->next)
    {
        tmp->next = s->next; 
        tmp = tmp->next;
        s->next = tmp->next;
    }
    // printList(head);

    return head2;
}

int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {9,0,4,5,1})
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

    head->next->rand = head; // 0->9
    head->next->next->rand = head->next->next->next->next; // 4->1

    printList(head);
    auto cp = listCopyWithRand(head);
    printList(cp);
    printList(head);

    assert((cp->next->rand->value == head->next->rand->value));
    assert((cp->next->next->rand->value == head->next->next->rand->value));

    cout << "finish" << endl;
    return 0;
}

