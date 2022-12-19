#include <iostream>
#include <vector>
/*
【题目】
给定数组 arr，返回 arr 的最长递增子序列。
【举例】
+ dp[i + 1][R]); arr=[2,1,5,3,6,4,8,9,7]，返回的最长递增子序列为[1,3,4,8,9]。
【要求】
如果 arr 长度为 N，请实现时间复杂度为 O(NlogN)的方法
*/

using namespace std;
vector<int> getdp1(const vector<int>& arr)
{
	vector<int> dp(arr.size());
	for (int i=0; i < arr.size(); i++) 
	{
		dp[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (arr[i] > arr[j]) 
				dp[i] = max(dp[i], dp[j] + 1);
		}
	}
	return dp;
}

vector<int> generateLIS(const vector<int>& arr, const vector<int>& dp) 
{
	int len = 0;
	int index = 0;
	for (int i=1; i < dp.size(); i++)
	{
		if (dp[i] > len) 
		{
			len = dp[i];
			index = i;
		}
	}
	vector<int> lis(len);
	lis[--len] = arr[index];
	for (int i = index; i >= 0; i--)
	{
		if (arr[i] < arr[index] && dp[i] == dp[index] - 1)
		{
			lis[--len] = arr[i];
			index = i;
		}
	}
	return lis;
}

vector<int> getdp2(const vector<int>& v)
{
	vector<int> dp(v.size());
	vector<int> ends(v.size());
	dp[0] = 1;
	int right = 0;
	int l = 0;
	int r = 0;
	int m = 0;
	for (int i = 1; i < v.size(); i++)
	{
		l = 0;
		r = right;
		while (l <= r)
		{
			m = (l+r)/2;
			if (v[i] > ends[m])
				l = m + 1;
			else
				r = m -1;
		}
		right = max(right, l);
		ends[l] = v[i];
		dp[i] = l + 1;
	}
	return dp;
}

vector<int> lis1(const vector<int>& arr)
{
	if (arr.empty())
		return {};
	return generateLIS(arr, getdp1(arr));
}

vector<int> lis2(const vector<int>& v) 
{
	if (v.empty())
		return {};
	return generateLIS(v, getdp2(v));
}

int main()
{
	auto res = lis1({2,1,5,3,6,4,8,9,7});
	for (auto& i : res)
		cout << i << ", ";
	cout << endl;

	res = lis2({2,1,5,3,6,4,8,9,7});
	for (auto& i : res)
		cout << i << ", ";
	cout << endl;
	return 1;
}
