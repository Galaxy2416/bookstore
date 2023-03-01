#include <iostream>
#include <vector>

using namespace std;

/*
给定一个数组 arr，已知其中所有的值都是非负的，将这个数组看作一个容器，请返回容器 能装多少水。
时间复杂度为 O(N)，额外空间复杂度为 O(1)。
*/

int getWater1(const vector<int>& arr)
{
	if (arr.empty() || arr.size() < 3)
		return 0;
	int res = 0;
	for (int i = 1; i != arr.size() - 1; ++i)
	{
		res += max(min(*max_element(arr.begin(), arr.begin()+i), *max_element(arr.begin()+i+1, arr.end())) - arr[i], 0);
	}
	return res;
}


int getWater2(const vector<int>& arr)
{
	if (arr.empty() || arr.size() < 3)
		return 0;
	int res = 0;
	vector<int> leftMax, rightMax;
	for (int i = 0; i != arr.size(); ++i)
	{
		leftMax.push_back(leftMax.empty() ? arr[i] : max(leftMax.back(), arr[i]));
	}
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		rightMax.push_back(rightMax.empty() ? arr[i] : max(rightMax.back(), arr[i]));
	}
	reverse(rightMax.begin(), rightMax.end());

	for (int i = 1; i != arr.size() - 1; ++i)
	{
		res += max(min(leftMax[i-1], rightMax[i+1]) - arr[i], 0);
	}
	return res;
}

int getWater3(const vector<int>& arr)
{
	if (arr.empty() || arr.size() < 3)
		return 0;
	int res = 0;
	int L = 1, R = arr.size() - 1;
	int leftMax = arr[0];
	int rightMax = arr.back();
	while (L <= R)
	{
		if (arr[L] <= arr[R])
		{
			res += max(leftMax - arr[L], 0);
			leftMax = max(leftMax, arr[L++]);
		}
		else
		{
			res += max(rightMax - arr[R], 0);
			rightMax = max(rightMax, arr[R--]);
		}
	}
	return res;
}


int main()
{
	cout << getWater1({3,1,2,5,2,4}) << endl;
	cout << getWater1({4,5,1,3,2}) << endl;

	cout << getWater2({3,1,2,5,2,4}) << endl;
	cout << getWater2({4,5,1,3,2}) << endl;

	cout << getWater3({3,1,2,5,2,4}) << endl;
	cout << getWater3({4,5,1,3,2}) << endl;
	
}
