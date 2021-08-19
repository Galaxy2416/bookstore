#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>

/*
一个栈依次压入 1、2、3、4、5，那么从栈顶到栈底分别为 5、4、3、2、1。将这个栈转置
后，从栈顶到栈底为 1、2、3、4、5，也就是实现栈中元素的逆序，但是只能用递归函数来实
现，不能用其他数据结构
*/

int getLastElement(std::stack<int> &data)
{
    int top = data.top();
    data.pop();
    if (data.empty())
        return top;
    int last = getLastElement(data);
    data.push(top);
    return last;
}

void reverseStack(std::stack<int> &data)
{
    if (data.empty()) {
        return;
    }
    int i = getLastElement(data);
    reverseStack(data);
    data.push(i);
}

int main()
{
    std::stack<int> test;
    for (auto& item : {1,2,3,4,5}) {
        test.push(item);
    }
    reverseStack(test);
    while (!test.empty())
    {
        std::cout << test.top() << ", ";
        test.pop();
    }
    std::cout << std::endl;
    return 0;
}
