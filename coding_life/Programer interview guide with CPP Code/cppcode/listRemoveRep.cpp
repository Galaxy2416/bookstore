#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
给定一个无序单链表的头节点 head，删除其中值重复出现的节点。
例如：1->2->3->3->4->4->2->1->1->null，删除值重复的节点之后为 1->2->3->4->null。
请按以下要求实现两种方法。
方法 1：如果链表长度为 N，时间复杂度达到 O(N)。 -> 只实现此
方法 2：额外空间复杂度为 O(1)。
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
void removeRep(Node<T> *head)
{   
    if(nullptr == head) {
        return;
    }
    unordered_set<T> s = {head->value};
    auto pre = head;
    auto cur = head->next;
    while(cur != nullptr)
    {
        auto search = s.find(cur->value);
        if (search != s.end()) 
        {
            std::cout << "Found " << (*search) << '\n';
            pre->next = cur->next;
            delete cur;
            cur = pre->next;
            continue;
        }
        s.insert(cur->value);
        pre = cur;
        cur = cur->next;
    }
    return;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {1,2,3,4,3,5,6,7,1,1,1,8,9})
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
    removeRep(head);
    printList(head);
    return 0;
}

