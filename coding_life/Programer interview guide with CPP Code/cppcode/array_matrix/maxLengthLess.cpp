#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
给定一个无序数组 arr，其中元素可正、可负、可 0。给定一个整数 k，求 arr 所有的子数组 中累加和小于或等于 k 的最长子数组长度。
例如:arr=[3,-2,-4,0,6]，k=-2，相加和小于或等于-2 的最长子数组为{3,-2,-4,0}，所以结果返 回4。
*/

/* 时间复杂度为 O(N) */

int getMaxLengthAwesome(const vector<int>& arr, int k)
{
	if (arr.empty())
		return 0;
	vector<int> minSums(arr.size(),  0);
	vector<int> minSumEnds(arr.size(),  0);

	minSums.back() = arr.back();
	minSumEnds.back() = arr.size() - 1;

	for (int i = arr.size() - 2; i >= 0; i--)
	{
		if (minSums[i+1] < 0)
		{
			minSums[i] = arr[i] + minSums[i+1];
			minSumEnds[i] = minSumEnds[i+1];
		}
		else
		{
			minSums[i] = arr[i];
			minSumEnds[i] = i;
		}
	}

	int end = 0;
	int sum = 0;
	int res = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		while (end < arr.size() && sum + minSums[end] <= k)
		{
			sum += minSums[end];
			end = minSumEnds[end] + 1;
		}
		res = max(res, end - i);
		if (end > i) // 不关心i-end 之间更短的数组 只看能不能到更长
			sum -= arr[i];
		else // / 窗口内已经没有数了，说明从 i 开头的所有子数组累加和都不可能小于
// 或等于k
			end = i + 1;
	}
	return res;
}

int main()
{
	cout << getMaxLengthAwesome({-3, 9, -6, 4, -2, -1}, -2) << endl;
	return 1;
}
