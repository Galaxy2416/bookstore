#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <math.h>

/*
给定链表的头节点 head，实现删除链表的中间节点的函数。
例如：
不删除任何节点；
1->2，删除节点 1；
1->2->3，删除节点 2；
1->2->3->4，删除节点 2；
1->2->3->4->5，删除节点 3；
进阶：
给定链表的头节点 head、整数 a 和 b，实现删除位于 a/b 处节点的函数。
例如：
链表：1->2->3->4->5，假设 a/b 的值为 r。
如果 r 等于 0，不删除任何节点；
如果 r 在区间(0, 1/5]上，删除节点 1；
如果 r 在区间(1/5, 2/5]上，删除节点 2；
如果 r 在区间(2/5, 3/5]上，删除节点 3；
如果 r 在区间(3/5, 4/5]上，删除节点 4；
如果 r 在区间(4/5, 1]上，删除节点 5；
如果 r 大于 1，不删除任何节点。
*/

using namespace std;

template<typename T>
void printList(const list<T> &a)
{
    for(auto i : a)
    {
        std::cout << i << "->";
    }
     std::cout << "\b\b  " << std::endl;
}

template<typename T>
void removeByRati(list<T> &l, int a, int b)
{
    int r = ceil((double)a/(double)b);
    if(r < 0)
        return;
    for(auto it = l.begin(); it != l.end(); ++it, --r)
    {
        if (0 == r)
        {
            l.erase(it);
            return;
        }
            
    }
}

int main()
{
    auto ltemp = list<int>{ 5, 7, 8, 18};
    removeByRati(ltemp, 3, 2);
    printList(ltemp);
    return 0;
}
