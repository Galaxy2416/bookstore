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
    auto c = head;
    for(; c->next != head; c = c->next)
    {
        std::cout << c->value << "->";
    }
    std::cout << c->value << std::endl;
}


template<typename T>
Node<T>* josephusKill1(Node<T> *head, int m)
{
    if(nullptr == head || head->next == head || m < 1) {
        return head;
    }
    
    auto last = head; // get the last
    while(last->next != head)
    {
        last = last->next;
    }
    int count = 0;
    while(head != last) // last one 
    {   
        if(++count == m)
        {
            last->next = head->next;
            count = 0;
            delete head;
        }
        else
        {
            last = last->next;
        }
        head = last->next;
    }
    return head;
}


template<int i, int m>
struct getLive {
    constexpr static int value = (getLive<i-1, m>::value + m - 1)%i + 1;
};

template<int m>
struct getLive<1, m> {
    constexpr static int value = 1;
};

int main()
{   
    Node<int> *head = new Node<decltype(0)>(0);
    Node<int> *c = head;
    for(auto i : {1,2,3,4,5,6,7,8,9})
    {
        c->next = new Node<decltype(i)>(i);
        c = c->next;
    }
    c->next = head;
    // cout << head->value <<endl;
    printList(head);
    int value = josephusKill1(head, 3)->value;
    cout << value << endl;
    // test 2
    assert(((value + 1) == getLive<10, 3>::value)); // value + 1 == position
    return 0;
}

