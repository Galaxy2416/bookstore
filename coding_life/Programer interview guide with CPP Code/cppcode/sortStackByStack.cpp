#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>

/*
一个栈中元素的类型为整型，现在想将该栈从顶到底按从大到小的顺序排序，只许申请一
个栈。除此之外，可以申请新的变量，但不能申请额外的数据结构。如何完成排序？
*/

void sortStackByStack(std::stack<int> &data)
{
    std::stack<int> helper;
    int top;
    while(!data.empty())
    {
        top = data.top();
        data.pop();
        while (!helper.empty() && helper.top() > top)
        {
            data.push(helper.top());
            helper.pop();        
        }
        helper.push(top);
    }
    data = std::move(helper);
}

void printStack(std::stack<int> data)
{
    while(!data.empty())
    {
        std::cout << data.top() << "|";
        data.pop();
    }
    std::cout << std::endl;
}

int main()
{
    std::stack<int> test;
    for (auto& item : {4,2,1,3,5}) {
        test.push(item);
    }
    sortStackByStack(test);
    printStack(test);
    return 0;
}
