#include <iostream>
#include <vector>

using namespace std;

/*
给定一个整型数组 arr，返回排序后相邻两数的最大差值。

【举例】
arr=[9,3,1,10]。如果排序，结果为[1,3,9,10]，9 和 3 的差为最大差值，故返回 6。 arr=[5,5,5,5]。返回 0。

【要求】
如果 arr 的长度为 N，请做到时间复杂度为 O(N)。
*/

int maxGap(const vector<int> nums) 
{
	auto bucket = [](long num, long len, long min, long max) 
	{
		return (int) ((num - min) * len / (max - min));
	};

	if (nums.empty())
		return 0;
	int max_ = *std::max_element(nums.begin(), nums.end());
	int min_ = *std::min_element(nums.begin(), nums.end());
	if (min_ == max_)
		return 0;

	int len = nums.size();
	vector<bool> hasNum(len + 1, 0);
	vector<int> maxs(len + 1, 0);
	vector<int> mins(len + 1, 0);
	for (int i : nums)
	{
		int bid = bucket(i, len, min_, max_);
		mins[bid] = hasNum[bid] ? min(mins[bid], i) : i;
		maxs[bid] = hasNum[bid] ? max(maxs[bid], i) : i;
		hasNum[bid] = true;
	}
	int res = 0;
	int lastMax = maxs[0];
	for (int i = 1; i <= len; i++)
	{
		if (hasNum[i])
		{
			res = max(res, mins[i] - lastMax);
			lastMax = maxs[i];
		}
	}
	return res;
}

int main()
{
	cout << maxGap({9,3,1,0}) << endl;
	cout << maxGap({5,5,5,5}) << endl;
	return 1;
}

