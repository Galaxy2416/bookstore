#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>

using namespace std;

/*
先给出可整合数组的定义:如果一个数组在排序之后，每相邻两个数差的绝对值都为 1， 则该数组为可整合数组。例如，[5,3,4,6,2]排序之后为[2,3,4,5,6]，符合每相邻两个数差的绝对值 都为 1，所以这个数组为可整合数组。
给定一个整型数组 arr，请返回其中最大可整合子数组的长度。例如，[5,5,3,2,6,4,3]的最大 可整合子数组为[5,3,2,6,4]，所以返回 5。
*/

int getLIL2(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	int len = 0;
	int max = 0;
	int min = 0;
	unordered_set<int> set {};
	for (int i = 0; i < arr.size(); i++)
	{
		max = numeric_limits<int>::min();
		min = numeric_limits<int>::max();
		for (int j = i; j != arr.size(); j++)
		{
			if (set.contains(arr[j]))
				break;
			set.insert(arr[j]);
			max = std::max(max, arr[j]);
			min = std::min(min, arr[j]);
			if (max - min  == j - i)
				len = std::max(len, j - i + 1);
			set.clear();
		}
	}
	return len;
}

int main()
{
	cout << getLIL2({5,5,3,2,6,4,3}) << endl;
	return 1;
}
