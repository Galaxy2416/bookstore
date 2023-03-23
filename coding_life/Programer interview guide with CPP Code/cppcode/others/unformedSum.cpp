#include <iostream>

/*
arr=[3,2,5]。子集{2}相加产生 2 为 min，子集{3,2,5}相加产生 10 为 max。在区间[2,10]上，4、 6 和 9 不能被任何子集相加得到，其中 4 是 arr 的最小不可组成和。
arr=[1,2,4]。子集{1}相加产生 1 为 min，子集{1,2,4}相加产生 7 为 max。在区间[1,7]上，任 何数都可以被子集相加得到，所以 8 是 arr 的最小不可组成和。
进阶问题:如果已知正数数组 arr 中肯定有 1 这个数，是否能更快地得到最小不可组成和?
*/


#include <vector>
#include <unordered_set>
#include <limits>

using namespace std;

using namespace std;
void process(const vector<int>& arr, int i, int sum, unordered_set<int>& set)
{
	if (i == arr.size()) {
		set.insert(sum);
		return;
	}
	process(arr, i+1, sum, set);
	process(arr, i+1, sum + arr[i], set);
}

int unformedSum1(const vector<int>& arr)
{
	if (arr.empty())
		return 1;
	unordered_set<int> set;
	process(arr, 0, 0, set);
	int min_ = *min_element(arr.begin(), arr.end());
	for (int i = min_ + 1; i != std::numeric_limits<int>::max(); i++)
	{
		if (!set.contains(i))
			return i;
	}
	return 1;
}

#include <numeric>

int unformedSum2(const vector<int>& arr)
{
	if (arr.empty())
		return 1;

	auto dp = vector<bool>(std::accumulate(arr.begin(), arr.end(), 0) + 1, false);
	dp[0] = true;

	for (auto a : arr)
		for (int i = dp.size() - 1; i >= a; i--)
		{
			dp[i] = dp[i-a] ? true : dp[i];
		}
	
	for (int i = *min_element(arr.begin(), arr.end()); i != dp.size(); ++i)
	{
		if (!dp[i])
			return i;
	}
	return dp.size();
}

/*
进阶问题，如果正数数组 arr 中肯定有 1 这个数，求最小不可组成和的过程可以得到很好 的优化，优化后可以做到时间复杂度为 O(NlogN)，额外空间复杂度为 O(1)。具体过程为:
*/


int unformedSum3(vector<int> arr)
{
	assert(!arr.empty());
	sort(arr.begin(), arr.end());
	assert(arr[0] == 1);
	int range = 0;
	for (auto i : arr)
	{
		if (i > range + 1)
			break;
		else
			range += i;
	}
	return range + 1;
}

int main()
{
	cout << unformedSum1({3,2,5}) << endl;
	cout << unformedSum2({3,2,5}) << endl;
	cout << unformedSum3({3,8,1,2}) << endl;
}
