#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
给定一个链表的头节点 head，请判断该链表是否为回文结构。
例如：
1->2->1，返回 true。
1->2->2->1，返回 true。
15->6->15，返回 true。
1->2->3，返回 false。
解法1 ： 使用栈结构，压栈反向一样
进阶：
如果链表长度为 N，时间复杂度达到 O(N)，额外空间复杂度达到 O(1)。
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
bool isPalindrome(Node<T> *head)
{   
    bool ret = true;
    if(nullptr == head || nullptr == head->next) {
        return true;
    }

    auto n1 = head;
    auto n2 = head;
    
    while(n2->next != nullptr && n2->next->next != nullptr)
    {
        n1 = n1->next;
        n2 = n2->next->next;
    }

    // mid is the next n1
    n2 = n1->next;
    n1->next = nullptr;
    auto tmp = n2;
    // reverse the mid list
    while(n2 != nullptr)
    {
        tmp = n2->next;
        n2->next = n1;
        n1 = n2; // as head
        n2 = tmp;
    } 
    tmp = n1; // right head
    n2 = head; // left
    // check palindome
    while(n1 != nullptr && n2 != nullptr)
    {
        if(n1->value != n2->value)
        {
            ret = false;
            break;
        }
        n1 = n1->next;
        n2 = n2->next;
    }

    n1 = tmp;
    n2 = n1->next;
    n1->next = nullptr;
    while(n2 != nullptr)
    {
        tmp = n2->next;
        n2->next = n1;
        n1 = n2; // as head
        n2 = tmp;
    }
    return ret;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {1,2,3,4,5,4,3,2,1})
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
    cout << isPalindrome(head) << endl;
    printList(head);
    return 0;
}

