#include <iostream>
#include <vector>

using namespace std;

/*
定义局部最小的概念。arr 长度为 1 时，arr[0]是局部最小。arr 的长度为 N(N>1)时，如 果 arr[0]<arr[1]，那么 arr[0]是局部最小;如果 arr[N-1]<arr[N-2]，那么 arr[N-1]是局部最小;如 果 0<i<N-1，既有 arr[i]<arr[i-1]，又有 arr[i]<arr[i+1]，那么 arr[i]是局部最小。
给定无序数组 arr，已知 arr 中任意两个相邻的数都不相等。写一个函数，只需返回 arr 中 任意一个局部最小出现的位置即可。
本题可以利用二分查找做到时间复杂度为 O(logN)、额外空间复杂度为 O(1)
*/

int getLessIndex(const vector<int>& arr)
{
	if (arr.empty())
		return -1;
	if (arr.size() == 1 || arr[0] < arr[1])
		return 0;
	if (arr[arr.size() - 1] < arr[arr.size() - 2])
		return arr.size() - 1;
	int left = 1;
	int right = arr.size() - 2;
	int mid = 0;
	while (left < right)
	{
		cout << left << ", " << mid << ", " << right << endl;
		mid = (left + right) / 2;
		if (arr[mid] > arr[mid-1])
			right = mid - 1;
		else if (arr[mid] > arr[mid+1])
			left = mid + 1;
		else
			return mid;
	}
	return left;
}

int main()
{
	cout << getLessIndex({5,2,1,4,7,8,9,10}) << endl;
	return 1;
}
