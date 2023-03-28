#include <iostream>

/*
【题目】
给定两个有序数组 arr1 和 arr2，已知两个数组的长度都为 N，求两个数组中所有数的上中 位数。
【举例】
arr1=[1,2,3,4]，arr2=[3,4,5,6]
总共有 8 个数，那么上中位数是第 4 小的数，所以返回 3。 arr1=[0,1,2]，arr2 =[3,4,5]
总共有 6 个数，那么上中位数是第 3 小的数，所以返回 2。
【要求】
时间复杂度为 O(logN)，额外空间复杂度为 O(1)。
*/

#include <vector>

using namespace std;

int getUpMedian(const vector<int>& arr1, const vector<int>& arr2)
{
	if (arr1.empty() || arr2.empty() || arr1.size() != arr2.size())
		return 0;
	int start1 = 0;
	int start2 = 0;
	int end1 = arr1.size() - 1;
	int end2 = arr2.size() - 1;
	int mid1 = 0;
	int mid2 = 0;
	int offset = 0;
	while (start1 < end1)
	{
		mid1 = (start1 + end1) / 2;
		mid2 = (start2 + end2) / 2;
		// 元素个数为奇数，offset为0；个数为偶数，则offset为1
		offset = ((end1 - start1 + 1) & 1) ^ 1;
		if (arr1[mid1] > arr2[mid2])
		{
			end1 = mid1;
			start2 = mid2 + offset;
		}
		else if (arr1[mid1] < arr2[mid2])
		{
			start1 = mid1 + offset;
			end2 = mid2;
		}
		else
		{
			return arr1[mid1];
		}
	}
	return std::min(arr1[start1], arr2[start2]);
}

int main()
{

	cout << getUpMedian({1,2,3,4}, {3,4,5,6}) << endl;
	cout << getUpMedian({0,1,2}, {3,4,5}) << endl;
}
