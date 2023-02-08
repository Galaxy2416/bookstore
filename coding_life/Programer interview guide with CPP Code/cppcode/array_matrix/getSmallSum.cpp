#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
【题目】
数组小和的定义如下:
例如，数组 s=[1,3,5,2,4,6]，在 s[0]的左边小于或等于 s[0]的数的和为 0;在 s[1]的左边小于 或等于 s[1]的数的和为 1;在 s[2]的左边小于或等于 s[2]的数的和为 1+3=4;在 s[3]的左边小于或 等于 s[3]的数的和为 1;在 s[4]的左边小于或等于 s[4]的数的和为 1+3+2=6;在 s[5]的左边小于或 等于 s[5]的数的和为 1+3+5+2+4=15。所以 s 的小和为 0+1+4+1+6+15=27。
给定一个数组 s，实现函数返回 s 的小和。
*/

/*
时间复杂度为 O(NlogN)、额外空间复杂度为 O(N)的方法
*/


int func(vector<int>& arr, int l, int r);
int merge(vector<int>& arr, int left, int mid, int right);

int getSmallSum(vector<int> arr)
{
	if (arr.empty())
		return 0;
	return func(arr, 0, arr.size() - 1);
}

int func(vector<int>& s, int l, int r)
{
	if (l == r)
		return 0;
	int mid = (l + r) / 2;
	return func(s, l, mid) + func(s, mid + 1, r) + merge(s, l, mid, r);
}

int merge(vector<int>& s, int left, int mid, int right)
{
	vector<int> h(right-left+1, 0);
	int hi = 0;
	int i = left;
	int j = mid + 1;
	int smallSum = 0;
	while (i <= mid && j <= right)
	{
		if (s[i] <= s[j]) {
			smallSum += (s[i] * (right - j + 1)); // Key Point
			h[hi++] = s[i++];
		}
		else {
			h[hi++] = s[j++];
		}
	}
	for (; (j < right + 1) || (i < mid + 1); j++, i++) {
		h[hi++] = i > mid ? s[j] : s[i];
	}

	for (int k = 0; k != h.size(); k++) {
		s[left++] = h[k];
	}
	return smallSum;
}

int main()
{
	cout << getSmallSum({1,3,5,2,4,6}) << endl;
	return 1;
}

