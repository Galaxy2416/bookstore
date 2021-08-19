#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
给定一个无序单链表的头节点 head，实现单链表的选择排序。
要求：额外空间复杂度为 O(1)
*/

/*
本题的思路很简单，举例就能说明具体的做法。
例如，链表 1->2->3->null，只知道要删除节点 2，而不知道头节点。那么只需把节点 2 的值
变成节点 3 的值，然后在链表中删除节点 3 即可。
这道题目出现的次数很多，这么做看起来非常方便，但其实是有很大问题的。
问题一：这样的删除方式无法删除最后一个节点。还是以原示例来说明，如果知道要删除
节点 3，而不知道头节点。但它是最后的节点，根本没有下一个节点来代替节点 3 被删除，那
么只有让节点 2 的 next 指向 null 这一种办法，而我们又根本找不到节点 2，所以根本没法正确
删除节点 3。读者可能会问，我们能不能把节点 3 在内存上的区域变成 null 呢？这样不就相当
于让节点 2 的 next 指针指向了 null，起到节点 3 被删除的效果了吗？不可以。null 在系统中是
一个特定的区域，如果想让节点 2 的 next 指针指向 null，必须找到节点 2。
问题二：这种删除方式在本质上根本就不是删除了 node 节点，而是把 node 节点的值改变，
然后删除 node 的下一个节点，在实际的工程中可能会带来很大问题。比如，工程上的一个节点
可能代表很复杂的结构，节点值的复制会相当复杂，或者可能改变节点值这个操作都是被禁止
的；再如，工程上的一个节点代表提供服务的一个服务器，外界对每个节点都有很多依赖，比
如，示例中删除节点 2 时，其实影响了节点 3 对外提供的服务。
这种删除方式的具体过程请参看如下代码中的 removeNodeWired 方法
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
void removeNodeWired(Node<T> *node)
{   
    if(node == nullptr)
    {
        return;
    }
    if(node->next == nullptr)
    {
        throw "Cannot remove last element.";
    }
    node->value = node->next->value;
    node->next = node->next->next;
    return;
}


int main()
{   
    Node<int> *head = nullptr;
    Node<int> *c = nullptr;
    for(auto i : {3,3,3,1,2,3,4,3,5,6,7,1,1,1,8,3,9,3,3})
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

    auto node_remove = head->next->next->next;

    printList(head);
    removeNodeWired(node_remove);
    printList(head);
    return 0;
}

