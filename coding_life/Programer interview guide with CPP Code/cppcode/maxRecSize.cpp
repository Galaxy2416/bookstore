#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>
#include <string.h>

/*
给定一个整型矩阵 map，其中的值只有 0 和 1 两种，求其中全是 1 的所有矩形区域中，最
大的矩形区域为 1 的数量。
例如：
1 1 1 0
其中，最大的矩形区域有 3 个 1，所以返回 3。
再如：
1 0 1 1
1 1 1 1
1 1 1 0
其中，最大的矩形区域有 6 个 1，所以返回 6。
如果矩阵的大小为 O(N×M)，可以做到时间复杂度为 O(N×M)。
*/

int maxRecFromBottom(const int *h, int j)
{
    if(!h || j <= 0)
        return 0;
    std::stack<int> st;
    int maxArea = 0;
    for(int i = 0; i != j; ++i)
    {
        while(!st.empty() && h[i] <= h[st.top()])
        {
            int position = st.top(); st.pop();
            int left = st.empty() ? -1 : st.top();
            // std::cout << left << "-" << i << "-" << position << "-" <<  h[position] << "~";
            maxArea = std::max(maxArea, (i - left - 1) * h[position]);

        }
        st.push(i); 
    }
    while(!st.empty())
    {
        int position = st.top(); st.pop();
        int left = st.empty() ? -1 : st.top();              
        maxArea = std::max(maxArea, (j - left - 1) * h[position]); // end position is j

    }
    return maxArea;
}

template<int i, int j>
int maxRecSize(int a[i][j]) // row : i - col :j
{
    if(!a || i <=0 || j <= 0)
        return 0;
    int height[j];
    int maxArea = 0;
    memset(height, 0, j*sizeof(int));
    for(int r = 0; r != i; ++r)
    { 
        for(int c = 0; c != j; ++c)
        {
            height[c] = a[r][c] ? height[c] +  a[r][c] : 0;
        }
        maxArea = std::max(maxArea, maxRecFromBottom(height, j));
    }
    return maxArea;
}

int main()
{
    int a[][4] = { 1, 0, 1, 1,
                  1, 1, 1, 1,
                  1, 1, 1, 0};
    std::cout << maxRecSize<3, 4>(a) << std::endl;
}
