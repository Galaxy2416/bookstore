#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>

/*
给定两个有序链表的头指针 head1 和 head2，打印两个链表的公共部分。
*/

using namespace std;

template<typename T>
void removeLastKthNode(list<T> &l, int k)
{
    cout << "list is : ";
    for(auto i : l)
    {
        cout << i << ",";
        --k;
    }
    cout << endl;
    
    auto it = l.begin();

    while(it != l.end()) 
    {
        if(k++ == 0)
        {
            l.erase(it);
            break;
        }
        ++it;
    }
    cout << "list 2 is : ";

    for(auto i : l)
    {
        cout << i << ",";
    }    
}

int main()
{
    list<int> l = { 5, 7, 8, 18 };
    removeLastKthNode(l, 3);
    return 0;
}
