#include <iostream>
#include <vector>

/*
【题目】
给定一个无序数组 arr，求出需要排序的最短子数组长度。 例如:arr = [1,5,3,4,2,6,7]返回 4，因为只有[5,3,4,2]需要排序。
*/

/*
解决这个问题可以做到时间复杂度为 O(N)、额外空间复杂度为 O(1)。
*/

using namespace std;
int getMinLength(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	int min = arr.back();
	int noMinIndex = -1;
	for (int i = arr.size() - 1; i >= 0; --i)
	{
		if (min < arr[i]) {
			noMinIndex = i;
		}
		else {
			min = std::min(arr[i], min);
		}
	}

	if (noMinIndex == -1)
		return 0;

	int max = arr[0];
	int noMaxIndex = -1;
	for (int i = 0; i != arr.size() - 1; ++i)
	{
		if (max > arr[i]) {
			noMaxIndex = i;
		}
		else {
			max = std::max(arr[i], max);
		}
	
	}
	cout << noMaxIndex << ", " << noMinIndex << endl;
	return  noMaxIndex - noMinIndex + 1;
}

int main()
{
	cout << getMinLength({1,3,5,2,4,6,7}) << endl;
	return 1;
}

