#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>

/*
编写一个类，用两个栈实现队列，支持队列的基本操作（add、poll、peek）
*/

template <typename T>
class TwoStackQueue
{
    private:
        std::stack<T> pushStack;
        std::stack<T> popStack;
        void push2pop()
        {
            while(!pushStack.empty())
            {
                popStack.push(pushStack.top());
                pushStack.pop();
            }
        }
    public:
        TwoStackQueue& add(T data)
        {
            pushStack.push(data);
            return *this;
        }
        
        T poll()
        {
            if (pushStack.empty() && popStack.empty())
                throw "The queue is empty.";
            if (popStack.empty())
                push2pop();
            const T& temp =  popStack.top();
            popStack.pop();
            return temp;
        }

        T& peak()
        {
            if (pushStack.empty() && popStack.empty())
                throw "The queue is empty.";
            if (popStack.empty())
                push2pop();
            return popStack.top();         
        }
};

int main()
{
    TwoStackQueue<int> test;
    test.add(1).add(2).add(3).add(4).add(5);
    assert(1 == test.peak());
    assert(1 == test.poll());
    assert(2 == test.peak());
    test.poll();
    test.poll();
    assert(4 == test.peak());
    test.add(20);
    assert(4 == test.peak());
    test.poll();
    test.poll();
    assert(20 == test.peak());
    return 0;
}
