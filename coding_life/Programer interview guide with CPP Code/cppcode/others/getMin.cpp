#include <iostream>

/*
有序数组 arr 可能经过一次旋转处理，也可能没有，且 arr 可能存在重复的数。例如，有序 数组[1,2,3,4,5,6,7]，可以旋转处理成[4,5,6,7,1,2,3]等。给定一个可能旋转过的有序数组 arr，返 回 arr 中的最小值。
*/

/*
本书提供的方式做到了尽可能多地利用二分查找，但是最差情况下仍无法避免 O(N)的时间 复杂度
*/

#include <vector>

using namespace std;

int getMin(const vector<int>& arr)
{
	int low = 0;
	int high = arr.size() - 1;
	int mid = 0;

	while (low < high)
	{
		if (low == high - 1)
			break;
		if (arr[low] < arr[high])
			return arr[low];
		mid = (low + high) / 2;
		if (arr[low] > arr[mid]) {
			high = mid;
			continue;
		}
		if (arr[high] < arr[mid]){
			low = mid;
			continue;
		}
		while (low < mid) { // arr[mid] == arr[low] == arr[high]
			if (arr[low] == arr[mid])
				low++;
			else if (arr[low] < arr[mid]) {
				return arr[low];
			}
			else {
				high = mid;
				break;
			}
		}
	}

	return std::min(arr[low], arr[high]);
}

int main()
{
	cout << getMin({4,5,6,7,1,2,3}) << endl;
	cout << getMin({3,2,2,3,3,3,3}) << endl;
	cout << getMin({3,4,5,3,3,3,3}) << endl;
}

