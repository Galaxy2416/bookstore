#include <iostream>
#include <memory>
#include <stdlib.h>
#include <deque>
#include <algorithm>
#include <assert.h>

/*
有一个整型数组 arr 和一个大小为 w 的窗口从数组的最左边滑到最右边，窗口每次向右边
滑一个位置。
例如，数组为[4,3,5,4,3,3,6,7]，窗口大小为 3 时：
[4 3 5] 4 3 3 6 7 窗口中最大值为 5
4 [3 5 4] 3 3 6 7 窗口中最大值为 5
4 3 [5 4 3] 3 6 7 窗口中最大值为 5
4 3 5 [4 3 3] 6 7 窗口中最大值为 4
4 3 5 4 [3 3 6] 7 窗口中最大值为 6
4 3 5 4 3 [3 6 7] 窗口中最大值为 7
如果数组长度为 n，窗口大小为 w，则一共产生 n-w+1 个窗口的最大值。
请实现一个函数。
 输入：整型数组 arr，窗口大小为 w。
 输出：一个长度为 n-w+1 的数组 res，res[i]表示每一种窗口状态下的最大值。
以本题为例，结果应该返回{5,5,5,4,6,7}。
*/

using namespace std;
template <typename T>
vector<T> getMaxWindow(const vector<T> &data, int w)
{
    vector<T> ret;
    deque<T> d;
    if(data.empty() || w > data.size())
        return ret;
    for(int i = 0; i != data.size(); ++i)
    {
        if(!d.empty() && (i - d.back() == w))
        {
            d.pop_back();
        }
        while(!d.empty() && data[i] >= data[d.front()])
        {
            d.pop_front();
        }
        d.push_front(i);
        if (i >= w -1)
            ret.push_back(data[d.back()]);
    }
}

template <typename T>
void printVector(const vector<T> &data)
{
    cout << "{ ";
    for(const auto &i : data)
    {
        cout << i << ", ";
    }
    cout << "} " << endl;
}

int main()
{
    // std::cout << test.pop();
    printVector(getMaxWindow(vector<int>{4,3,5,4,3,3,6,7}, 3));
}
