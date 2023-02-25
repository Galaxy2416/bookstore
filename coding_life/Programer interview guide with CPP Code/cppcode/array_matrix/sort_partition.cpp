#include <iostream>
#include <vector>

/*
给定一个有序数组 arr，调整 arr 使得这个数组的左半部分没有重复元素且升序，而不用保 证右部分是否有序。
例如，arr=[1,2,2,2,3,3,4,5,6,6,7,7,8,8,8,9]，调整之后 arr=[1,2,3,4,5,6,7,8,9,...]。 补充问题:给定一个数组 arr，其中只可能含有 0、1、2 三个值，请实现 arr 的排序。 另一种问法为:有一个数组，其中只有红球、蓝球和黄球，请实现红球全放在数组的左边，蓝球放在中间，黄球放在右边。
另一种问法为:有一个数组，再给定一个值 k，请实现比 k 小的数都放在数组的左边，等
于 k 的数都放在数组的中间，比 k 大的数都放在数组的右边。
*/

/*
【要求】
1.所有题目实现的时间复杂度为 O(N)。 2.所有题目实现的额外空间复杂度为 O(1)。
*/

using namespace std;

void leftUnique(vector<int>& arr)
{
	if (arr.empty())
		return;
	int u = 0;
	int i = 1;
	while (i != arr.size())
	{
		if (arr[i++] != arr[u])
			std::swap(arr[++u], arr[i-1]);
	}
}


void sortThree(vector<int>& arr)
{
	if (arr.empty())
		return;
	int l = -1;
	int r = arr.size();
	int index = 0;
	while (index != r)
	{
		if (arr[index] == 0) {
			std::swap(arr[index++], arr[++l]);
		}
		else if (arr[index] == 2)
			std::swap(arr[--r], arr[index]);
		else
			index++;
	}
}

int main()
{
	vector<int> arr {1,2,2,2,3,3,4,5,6,6,7,7,8,8,8,9};
	leftUnique(arr);
	for_each(arr.begin(), arr.end(), [](auto i) {cout << i << ",";});
	cout << endl;

	vector<int> arr2 {1,2,2,2,0,2,1,0,2,2,1,1,2,0,1,2};
	sortThree(arr2);
	for_each(arr2.begin(), arr2.end(), [](auto i) {cout << i << ",";});
	cout << endl;

	return 1;
}
