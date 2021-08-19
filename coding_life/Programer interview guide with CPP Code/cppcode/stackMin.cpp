#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>

/*

【题目】
实现一个特殊的栈，在实现栈的基本功能的基础上，再实现返回栈中最小元素的操作。
【要求】
1．pop、push、getMin 操作的时间复杂度都是 O(1)。
2．设计的栈类型可以使用现成的栈结构。
*/

template <typename T>
class MyStack
{
    private:
        std::stack<T> stackData;
        std::stack<T> stackMin;
    
    public:
        MyStack<T>& push (T data)
        {
            stackData.push(data);
            stackMin.push(stackMin.empty() ? data : std::min(data, stackMin.top())); //data < stackMin.top() ? data : stackMin.top());
            return *this;
        }
        T pop()
        {
            stackData.pop();
            stackMin.pop();
        }
        T getmin()
        {
            if (stackMin.empty())
                throw "Your stack is empty.";
            return stackMin.top();
        }
};

int main()
{
    MyStack<int> test;
    // std::cout << test.pop();
    test.push(2).push(7).push(3).push(5).push(1);
    assert(test.getmin() == 1);
    test.pop();
    assert(test.getmin() == 2);
    test.pop();
    assert(test.getmin() == 2);
    return 0;
}
