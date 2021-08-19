#include <iostream>
#include <memory>
#include <stdlib.h>
#include <stack>
#include <algorithm>
#include <assert.h>

/*
【题目】
一个不含有负数的数组可以代表一圈环形山，每个位置的值代表山的高度。比如，
{3,1,2,4,5}、{4,5,3,1,2}或{1,2,4,5,3}都代表同样结构的环形山。3->1->2->4->5->3 方向叫作 next 方
向（逆时针），3->5->4->2->1->3 方向叫作 last 方向（顺时针）

山峰 A 和山峰 B 能够相互看见的条件为：
1．如果 A 和 B 是同一座山，认为不能相互看见。
2．如果 A 和 B 是不同的山，并且在环中相邻，认为可以相互看见
3．如果 A 和 B 是不同的山，并且在环中不相邻，假设两座山高度的最小值为 min。如果 A
通过 next 方向到 B 的途中没有高度比 min 大的山峰，或者 A 通过 last 方向到 B 的途中没有高度
比 min 大的山峰，认为 A 和 B 可以相互看见。比如图 1-8 中，高度为 3 的山和高度为 4 的山，
两座山的高度最小值为 3。3 从 last 方向走向 4，中途会遇见 5，所以 last 方向走不通；3 从 next
方向走向 4，中途会遇见 1 和 2，但是都不大于两座山高度的最小值 3，所以 next 方向可以走通。

有一个能走通就认为可以相互看见。再如，高度为 2 的山和高度为 5 的山，两个方向上都走不
通，所以不能相互看见

给定一个不含有负数且没有重复值的数组 arr，请返回有多少对山峰能够相互看见。
进阶问题：给定一个不含有负数但可能含有重复值的数组 arr，返回有多少对山峰能够相互
看见。

【要求】
如果 arr 长度为 N，没有重复值的情况下时间复杂度达到 O(1)，可能有重复值的情况下时间
复杂度请达到 O(N)。
【难度】
原问题 士 ★☆☆☆
进阶问题 将 ★★★★
*/

// 如果 k==1，返回 0；如果 k>1，返回 C(2,k)
int getInternalSum(int k) {
return k == 1 ? 0 : (k * (k - 1) / 2);
}
// 环形数组中当前位置为 i，数组长度为 size，返回 i 的下一个位置
int nextIndex(int i, int size) {
return i < (size - 1) ? (i + 1) : 0;
}

template <typename T, size_t N>
int getVisiableNum(const T(&data)[N])
{
    using namespace std;
    if(data == nullptr || N < 2)
        return 0;
    int ret = 0;
    stack<pair<T, int>> st;
    // get the largest number
    int maxIndex = 0;
    for(int i = 0; i != N; ++i)
    {
        maxIndex = data[i] > data[maxIndex] ? i : maxIndex;
    }
    st.push(make_pair(data[maxIndex], 1));
    for(int index = nextIndex(maxIndex, N); index != maxIndex; index = nextIndex(index, N))
    {
        while(st.top().first < data[index])
        {
            ret += getInternalSum(st.top().second) + 2*st.top().second;
            st.pop();
        }
        if(st.top().first == data[index])
        {
            st.top().second++;
        }
        else
        {
            st.push(make_pair(data[index], 1));
        }
    }

    // clean
    while(st.size() > 2)
    {
        ret += getInternalSum(st.top().second) + 2*st.top().second;
        st.pop();
    }
    if(st.size() == 2)
    {   
        auto tmp = st.top().second;
        st.pop();
        ret += getInternalSum(tmp) + (st.top().first == 1 ? tmp : 2*tmp);
    }
    // the last one
    ret +=  getInternalSum(st.top().second);
    return ret;
}

int main()
{
    int num[6] = {1, 2, 4, 8 , 2, 6};
    int num2[5] = {2,4,4,5,3};

    // std::cout << test.pop();
    std::cout << getVisiableNum(num) << std::endl;
    std::cout << getVisiableNum(num2) << std::endl;

}
