#include <iostream>

/*
给定一个长度为 N 且没有重复元素的数组 arr 和一个整数 n，实现函数等概率随机打印 arr 中的M个数。
【要求】
1.相同的数不要重复打印。
2.时间复杂度为 O(M)，额外空间复杂度为 O(1)。
3.可以改变 arr 数组。
*/

#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

void printRandM(vector<int>&& arr, int m)
{
	if (arr.empty() || m < 0)
		return;
	m = std::min((int)arr.size(), m);
	int count = 0;
	int i = 0;
	while (count != m) 
	{
		int i = (int) (rand() % (arr.size() - count)) ;
		cout << arr[i] << ", ";
		swap(arr[i], arr[arr.size() - count++ - 1]);
	}
	cout << endl;
}


int main()
{
	printRandM({1,3,4,5,2,6,9,8,10}, 6);
}
