#include <iostream>
#include <vector>

using namespace std;

/*
给定一个 double 类型的数组 arr，其中的元素可正、可负、可 0，返回子数组累乘的最大乘 积。例如，arr=[-2.5，4，0，3，0.5，8，-1]，子数组[3，0.5，8]累乘可以获得最大的乘积 12， 所以返回 12。
本题可以做到时间复杂度为 O(N)、额外空间复杂度为 O(1)。
*/

double maxProduct(const vector<double>& arr)
{
	if (arr.empty())
		return 0;
	double max = arr[0];
	double min = arr[0];
	double res = arr[0];
	double maxEnd = 0;
	double minEnd = 0;
	for (int i = 1; i != arr.size(); ++i)
	{
		maxEnd = max * arr[i];
		minEnd = min * arr[i];
		max = std::max({maxEnd, minEnd, arr[i]});
		min = std::min({maxEnd, minEnd, arr[i]});
		res = std::max(max, res);
	}
	return res;
}

int main()
{
	cout << maxProduct({-2.5, 4, 0, 3, 0.5, 8, -1}) << endl;
	return 1;
}


