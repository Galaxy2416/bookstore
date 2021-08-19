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
void printCommonPart(const list<T> &a, const list<T> &b)
{
    auto ia = a.begin();
    auto ib = b.begin();
    while(ia != a.end() && ib != b.end())
    {
        if(*ia == *ib)
        {
            cout << *ia << "," << endl;
            ++ia;
            ++ib;
        }
        else if(*ia > *ib)
        {
            ++ib;
        }
        else
        {
            ++ia;
        }
    }
    cout << endl;
}

int main()
{
    printCommonPart(list<int>{ 5, 7, 8, 18 }, list<int>{ 3, 5, 7, 8 });
    return 0;
}
