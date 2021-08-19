#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>
#include <utility>

/*
定一个不含有重复值的数组 arr，找到每一个 i 位置左边和右边离 i 位置最近且值比 arr[i]
小的位置。返回所有位置相应的信息。

arr = {3,4,1,5,6,2,7}
返回如下二维数组作为结果：
{ 
 {-1, 2},
 { 0, 2},
 {-1,-1},
 { 2, 5},
 { 3, 5},
 { 2,-1},
 { 5,-1}
}
-1 表示不存在。所以上面的结果表示在 arr 中，0 位置左边和右边离 0 位置最近且值比 arr[0]
小的位置是-1 和 2；1 位置左边和右边离 1 位置最近且值比 arr[1]小的位置是 0 和 2；2 位置左
边和右边离 2 位置最近且值比 arr[2]小的位置是-1 和-1……
进阶问题：给定一个可能含有重复值的数组 arr，找到每一个 i 位置左边和右边离 i 位置最
近且值比 arr[i]小的位置。返回所有位置相应的信息。

如果 arr 长度为 N，实现原问题和进阶问题的解法，时间复杂度都达到 O(N)。

单调栈
*/

using namespace std;
vector<pair<int, int>> getNearLess(const vector<int> data)
{
    vector<pair<int, int>> ret(data.size(), make_pair(-2, -2));
    stack<vector<int>> st; // the stack always larger on top
    for(int i = 0; i != data.size(); ++i)
    {
        while(!st.empty() && data[i] < data[st.top()[0]])
        {
            auto e = st.top();
            st.pop();
            int right = i;
            int left = st.empty() ? -1 : st.top().back(); // next last one

            for (auto i : e)
            {
                ret[i] = make_pair(left, right);
            }
        }
        if (!st.empty() && data[i] == data[st.top()[0]])
        {
            st.top().push_back(i);
        }
        else // empty or normal
        {
            vector<int> tmp; tmp.push_back(i);
            st.push(tmp);           
        }
    }
    while (!st.empty()) // clean the stack
    {
        auto e = st.top();
        st.pop();
        int right = -1;
        int left = st.empty() ? -1 : st.top().back(); // next last one
        for (auto i : e)
        {
            ret[i] = make_pair(left, right);
        }
    }
    return ret;
}

void testPrint(vector<pair<int, int>> data)
{
    for(auto i : data)
    {
        cout << "{ " << i.first << " , " << i.second << " }" << endl; 
    }
    cout << endl;
}    

int main()
{
    testPrint(getNearLess(vector<int>{3,4,1,5,6,2,7}));
    testPrint(getNearLess(vector<int>{3,1,3,4,3,5,3,2,2}));
    return 0;
}
