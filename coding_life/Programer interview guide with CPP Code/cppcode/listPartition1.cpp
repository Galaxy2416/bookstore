#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
给定一个单向链表的头节点 head，节点的值类型是整型，再给定一个整数 pivot。实现一个
调整链表的函数，将链表调整为左部分都是值小于 pivot 的节点，中间部分都是值等于 pivot 的
节点，右部分都是值大于 pivot 的节点。除这个要求外，对调整后的节点顺序没有更多的要求。
例如：链表 9->0->4->5->1，pivot=3。
调整后链表可以是 1->0->4->9->5，也可以是 0->1->9->5->4。总之，满足左部分都是小于 3
的节点，中间部分都是等于 3 的节点（本例中这个部分为空），右部分都是大于 3 的节点即可。
对某部分内部的节点顺序不做要求。
进阶：
在原问题的要求之上再增加如下两个要求。
 在左、中、右三个部分的内部也做顺序要求，要求每部分里的节点从左到右的顺序与
原链表中节点的先后次序一致。
例如：链表 9->0->4->5->1，pivot=3。调整后的链表是 0->1->9->4->5。在满足原问题要求的
同时，左部分节点从左到右为 0、1。在原链表中也是先出现 0，后出现 1；中间部分在本例中
为空，不再讨论；右部分节点从左到右为 9、4、5。在原链表中也是先出现 9，然后出现 4，最
后出现 5。
 如果链表长度为 N，时间复杂度请达到 O(N)，额外空间复杂度请达到 O(1)。
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
Node<T>* listPartition(Node<T> *head, int pivot)
{   

    Node<T> *sh = nullptr; Node<T> *se = nullptr;
    Node<T> *eh = nullptr; Node<T> *ee = nullptr;
    Node<T> *bh = nullptr; Node<T> *be = nullptr;
    Node<T> *tmp = nullptr;

    for(Node<T> *i = head; i != nullptr;)
    {
        if(i->value < pivot)
        {
            if(sh == nullptr)
            {
                sh = i;
                se = sh;
            }
            else
            {
                se->next = i;
                se = se->next;
            }
        }
        else if(i->value > pivot)
        {
            if(bh == nullptr)
            {
                bh = i;
                be = bh;
            }
            else
            {
                be->next = i;
                be = be->next;
            }
        }
        else
        {
            if(eh == nullptr)
            {
                eh = i;
                ee = eh;
            }
            else
            {
                ee->next = i;
                ee = ee->next;
            }
        }     
        tmp = i->next;
        i->next = nullptr;
        i = tmp;
    }

    printList(sh);
    printList(eh);  
    printList(bh);

    // smaller -> mid
    if(se != nullptr)
    {
        se->next = eh;
        ee = ee == nullptr ? se : ee; // mid null. ee is the same with se 
    }
    
    if(ee != nullptr)
    {
        ee->next = bh;
    }

    printList(sh);

    return sh == nullptr ? (eh == nullptr ? bh : eh ): sh; 
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

    printList(head);
    printList(listPartition(head, 3));
    return 0;
}

