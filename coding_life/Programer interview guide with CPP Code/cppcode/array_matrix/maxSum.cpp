#include <iostream> 
#include <vector>
#include <limits>

using namespace std;

/*
给定一个数组 arr，返回子数组的最大累加和。
例如，arr=[1,-2,3,5,-2,6,-1]，所有的子数组中，[3,5,-2,6]可以累加出最大的和 12，所以返回 12。
如果 arr 长度为 N，要求时间复杂度为 O(N)、额外空间复杂度为 O(1)
*/

int main()
{
	vector<int> arr {1,-2,3,5,-2,6,-1};
	int cur = 0;
	int max = numeric_limits<int>::min();
	for (int i : arr)
	{
		cur += i;
		cur = cur < 0 ? 0 : cur;
		max = std::max(max, cur);
	}
	cout << max << endl;
	return 1;
}

