#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <stack>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
在本题中，单链表可能有环，也可能无环。给定两个单链表的头节点 head1 和 head2，这
两个链表可能相交，也可能不相交。请实现一个函数，如果两个链表相交，请返回相交的第一
个节点；如果不相交，返回 null 即可。
要求：如果链表 1 的长度为 N，链表 2 的长度为 M，时间复杂度请达到 O(N+M)，额外空间
复杂度请达到 O(1)。
*/

using namespace std;

template<typename T>
struct Node 
{
    Node<T>(T i)
    :value(i), next(nullptr)
    {
    }

    Node<T>(const Node<T> &node)
    {
        value = node.value;
        next = nullptr;
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
Node<T>* getLoopNode(Node<T> *head)
{
    if(head == nullptr || head->next == nullptr)
        return nullptr;
    auto jump1 = head->next;
    auto jump2 = head->next->next;
    bool find = false;
    while(jump2 != nullptr)
    {
        if(jump1 == jump2)
        {
            find = true;
            break;
        }
        jump1 = jump1->next;
        jump2 = jump2->next ? jump2->next->next : nullptr;
    }
    if(find)
    {
        jump1 = head;
        while(jump1 != jump2)
        {
            jump1=jump1->next;
            jump2=jump2->next;
        }
        return jump1; // jump1 == jump2
    }
    return nullptr; 
}

template<typename T>
Node<T>* getIntersectNodeNoLoop(Node<T> *head, Node<T> *head2)
{   
    if(head == nullptr || head2 == nullptr)
        return nullptr;
    size_t a = 1;
    size_t b = 1;
    auto c1 = head;
    auto c2 = head2;
    while(c1->next != nullptr)
    {
        ++a;
        c1 = c1->next;
    }
    while(c2->next != nullptr)
    {
        ++b;
        c2 = c2->next;
    }
    if(c1 != c2)
    {
        return nullptr;
    }
    // c1 is longer and c1 is shorter now
    c1 = head;
    c2 = head2;
    if(a >= b)
    {
        for(int i = a - b; i != 0; --i)
            c1 = c1->next;
    }
    else
    {
        for(int i = b - a; i != 0; --i)
            c2 = c2->next;
    }
    while(c1 != c2)
    {
        c1 = c1->next;
        c2 = c2->next;
    }
    return c1;
}

template<typename T>
Node<T>* bothLoop(Node<T> *head1, Node<T> *loop1, Node<T> *head2, Node<T> *loop2)
{
    Node<T>* c1 = nullptr;
    Node<T>* c2 = nullptr;
    if(loop1 == loop2)
    {
        int n = 0;
        c1 = head1;
        c2 = head2;
        while(c1 != loop1)
        {
            n++;
            c1 = c1->next;
        }
        while(c2 != loop2)
        {
            n--;
            c2 = c2->next;
        }
        c1 = n >= 0 ? head1 : head2;
        c2 = c1 == head1 ? head2 : head1;
        n = abs(n);
        while(n-- != 0)
            c1 = c1->next;
        while(c1 != c2)
        {
            c1 = c1->next;
            c2 = c2->next;
        }
        return c1;
    }
    else
    {
        c1 = loop1->next;
        while(c1 != loop1)
        {
            if(c1 == loop2)
                return c1;
            c1 = c1->next;
        }
        return nullptr;
    }
}

template<typename T>
Node<T>* getIntersectNode(Node<T> *head1, Node<T> *head2)
{
    if (head1 == nullptr || head2 == nullptr)
    {
        return nullptr;
    }
    auto loop1 = getLoopNode(head1);
    auto loop2 = getLoopNode(head2);
    if(loop1 == nullptr && loop2 == nullptr)
    {
        return getIntersectNodeNoLoop(head1, head2);
    }
    else if(loop1 && loop2)
    {
        return bothLoop(head1, loop1, head2, loop2);
    }
    return nullptr;
}

int main()
{   
    // test the loop function
    Node<int> *head, *head2, *c;
    head = head2 = c = nullptr;
    for(auto i : {1,0,4,5,3}) // no loop
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
    cout << getLoopNode(head) << endl;
    for(auto i : {2,6,9,2,5,7,0}) 
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
    head2->next->next->next->next->next->next->next = head2->next->next->next->next; // loop 0->5
    // printList(head2);
    cout << getLoopNode(head2)->value << endl;
  
    // de-loop for following testing 
    head2->next->next->next->next->next->next->next = nullptr; // loop 0->5
    assert((nullptr == getIntersectNode(head, head2)));
    auto end1 = head->next->next->next->next;
    auto end2 = head2->next->next->next->next->next->next; 
    // test the getIntersectNodeNoLoop function

    for(auto i : {8,9,10,11,12}) // no loop
    {
        end1->next = end2->next =  new Node<decltype(i)>(i);
        end1 = end1->next;
        end2 = end2->next;
    }
    printList(head);
    printList(head2);
    assert((8 == getIntersectNode(head, head2)->value));
    cout << getIntersectNode(head, head2)->value<< endl;
    // test the getIntersectLoop function
    for(auto i : {13,14,15,16,17}) // no loop
    {
        end1->next =  new Node<decltype(i)>(i);
        end1 = end1->next;
    }
    end1->next = end2->next; // loop
    auto loop1 = getLoopNode(head); cout << loop1->value << endl;
    auto loop2 = getLoopNode(head2); cout << loop2->value << endl;
    assert((loop1->value == 13));
    assert((loop2->value == 13));
    assert((bothLoop(head, loop1, head2, loop2)->value == 8));
    assert((getIntersectNode(head, head2)->value == 8));
    cout << "finish" << endl;
    return 0;
}

