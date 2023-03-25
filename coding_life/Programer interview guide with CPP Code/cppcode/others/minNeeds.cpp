#include <iostream>

/*
给定一个有序的正数数组 arr 和一个正数 range，如果可以自由选择 arr 中的数字，想累加 得到 1~range 范围上所有的数，返回 arr 最少还缺几个数。
*/

/*
 时间复杂 度不会比 O(log range)高
*/

#include <vector>

using namespace std;

int minNeeds(const vector<int>& arr, int range)
{
	int needs = 0;
	int touch = 0;
	for (int i : arr)
	{
		while (i > touch - 1)
		{
			touch += touch + 1;
			cout << "add : " << touch + 1 << endl; 
			needs++;
			if (touch >= range)
				return needs;
		}
		touch += i;
		if (touch >= range)
			return needs;
	}
	while (range >= touch + 1) {
		touch += touch + 1;
		needs++;
	}
	return needs;
}

int main()
{
	cout << minNeeds({3,17,21,78}, 67) << endl;
	return 1;
}

