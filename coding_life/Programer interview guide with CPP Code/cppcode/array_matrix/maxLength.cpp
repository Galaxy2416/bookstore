#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
【题目】
给定一个无序数组 arr，其中元素可正、可负、可 0。给定一个整数 k，求 arr 所有的子数组 中累加和为 k 的最长子数组长度。
补充问题 1:给定一个无序数组 arr，其中元素可正、可负、可 0。求 arr 所有的子数组中 正数与负数个数相等的最长子数组长度。
补充问题 2:给定一个无序数组 arr，其中元素只是 1 或 0。求 arr 所有的子数组中 0 和 1 个数相等的最长子数组长度。
*/

/* 时间复杂度为 O(N)、额外空间复杂度为 O(N) */

int getMaxLength(const vector<int>& arr, int k)
{
	if (arr.empty())
		return 0;
	unordered_map<int, int> map{}; // sum : most-left-position
	map[0] = -1; // important.
	int len = 0;
	int sum = 0;
	for (int i = 0; i != arr.size(); ++i)
	{
		sum += arr[i];
		if (map.contains(sum - k))
		{
			len = max(len, i - map[sum-k]);
		}
		if (!map.contains(sum))
			map[sum] = i;
	}
	return len;
}

int main()
{
	cout << getMaxLength({1,2,3,3}, 5) << endl;
	return 1;
}
