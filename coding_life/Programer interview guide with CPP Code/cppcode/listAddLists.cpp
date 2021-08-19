#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <stack>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
假设链表中每一个节点的值都在 0～9 之间，那么链表整体就可以代表一个整数。
例如：9->3->7，可以代表整数 937。
给定两个这种链表的头节点 head1 和 head2，请生成代表两个整数相加值的结果链表。
例如：链表 1 为 9->3->7，链表 2 为 6->3，最后生成新的结果链表为 1->0->0->0。
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
Node<T>* listAddLists(Node<T> *head, Node<T> *head2)
{   
    if(head == nullptr)
        return head2; // copy(head2)
    if(head2 == nullptr)
        return head; // copy(head)
    
    Node<T> *ret = nullptr;
    Node<T> *tmp = nullptr;

    stack<T> a;
    stack<T> b;
    stack<T> c;

    for(auto s = head; s != nullptr; s=s->next)
    {
        a.push(s->value);
    }    

    for(auto s = head2; s != nullptr; s=s->next)
    {
        b.push(s->value);
    }
    
    int topa, topb, carry;
    carry = 0;
    while(!a.empty() || !b.empty())
    {
        topa = topb = 0;
        if(!a.empty())
        {
            topa = a.top();
            a.pop();
        }
        if(!b.empty())
        {
            topb = b.top();
            b.pop();
        }
        c.push((carry + topa + topb)%10);
        carry = (carry + topa + topb)/10;
    }
    while(!c.empty())
    {
        if(ret == nullptr)
        {
            ret = new Node<T>(c.top());
            tmp = ret;
        }
        else
        {
            tmp->next = new Node<T>(c.top());
            tmp = tmp->next;
        }
        c.pop();
    }
    return ret;
}

int main()
{   
    Node<int> *head, *head2, *c;
    head = head2 = c = nullptr;
    for(auto i : {1,0,4,5,3})
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
    printList(head2);
    auto cp = listAddLists(head, head2);
    printList(cp);

    cout << "finish" << endl;
    return 0;
}

