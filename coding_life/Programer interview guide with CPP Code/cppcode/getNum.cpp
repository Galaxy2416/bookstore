#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>

/*
【题目】
给定数组 arr 和整数 num，共返回有多少个子数组满足如下情况：
max(arr[i..j]) - min(arr[i..j]) <= num
max(arr[i..j])表示子数组 arr[i..j]中的最大值，min(arr[i..j])表示子数组 arr[i..j]中的最小值。
【要求】
如果数组长度为 N，请实现时间复杂度为 O(N)的解法
*/


template <typename T, size_t N>
int getNum(const T(&data)[N])
{
    using namespace std;
    int ret = 0;
    deque<T> min; // current window min
    deque<T> max;
    for(int i = 0, j = 0; j != N;) 
    {
        // in fact. only for index 0
        if(min.empty())
            min.push_back(i);
        if(max.empty())
            max.push_back(i);
        // pop out window elements
        if(!min.empty() && min.front() < i) // no empty. since min window is 1
            min.pop_front();
        if(!max.empty() && max.front() < i)
            max.pop_front();
        if(data[max.front()] - data[min.front()] <= num) //calculate
        {
            ret += j++ - i;
            // cout<<ret;
            while(!min.empty() && data[j] <= min.back())
            {
                min.pop_back();
            }
            while(!max.empty() && data[j] >= max.back())
            {
                max.pop_back();
            }
            min.push_back(j);
            max.push_back(j);            
        }
        else
        {
            i++;
        }
    }
    return ret;
}

int main()
{
    int num[6] = {1, 2, 4, 8 , 2, 6};
    // std::cout << test.pop();
    std::cout << getNum(num) << std::endl;
}
