#include <iostream>

/*
有序数组 arr 可能经过一次旋转处理，也可能没有，且 arr 可能存在重复的数。例如，有序 数组[1,2,3,4,5,6,7]，可以旋转处理成[4,5,6,7,1,2,3]等。给定一个可能旋转过的有序数组 arr，再 给定一个数 num，返回 arr 中是否含有 num。
*/

using namespace std;

#include <vector>

/*
本书提供的方式做到了尽可能多地利用二分查找，但是最差情况下仍无法避免 O(N)的时间 复杂度，以下是具体过程
*/

bool isContains(const vector<int>& arr, int num)
{
	int low = 0;
	int high = arr.size() - 1;
	int mid = 0;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (arr[mid] == num)
			return true;
		if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
			while (low != mid && arr[mid] == arr[low]) {
				low++;
			}
			if (low == mid) {
				low = mid + 1;
				continue;
			}
		}

		if (arr[low] != arr[mid])
		{
			if (arr[mid] > arr[low]) {
				if (num >= arr[low] && num < arr[mid])
					high = mid - 1;
				else
					low = mid + 1;
			}
			continue;
		}
		
		else
		{
			if (num > arr[mid] && num <= arr[high])
				low = mid + 1;
			else
				high = mid - 1;
		}
	}
	return false;
}

int main()
{
	cout << isContains({4,5,6,7,1,2,3}, 4) << endl;
	cout << isContains({4,5,6,7,1,2,3}, 9) << endl;
	return 1;
}
