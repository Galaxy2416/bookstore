#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>



using namespace std;

/*
给定一个整型数组 arr，返回不包含本位置值的累乘数组。 例如，arr=[2,3,1,4]，返回[12,8,24,6]，即除自己外，其他位置上的累乘。

1.时间复杂度为 O(N)。 2.除需要返回的结果数组外，额外空间复杂度为 O(1)。 进阶问题:对时间和空间复杂度的要求不变，而且不可以使用除法。

*/


vector<int> product1(const vector<int> arr)
{
	if (arr.empty())
		return {};
	int count = std::count(arr.begin(), arr.end(), 0);
	// int all = std::accumulate(arr.begin(), arr.end(), 1, std::multiplies<>());
	vector<int> ret(arr.size(), 0);
	int all = 1;
	for (int i = 0; i != arr.size(); ++i)
	{
		if (arr[i] != 0)
			all *= arr[i];
	}
	cout << count << endl;
	if (count == 0)
		for (int i = 0; i != arr.size(); ++i)
			ret[i] = all / arr[i];
	if (count == 1)
		for (int i = 0; i != arr.size(); ++i)
			if (arr[i] == 0)
				ret[i] = all;
	return ret;
}

vector<int> product2(const vector<int> arr)
{
	if (arr.empty())
		return {};
	vector<int> ret(arr.size(), 0);
	ret[0] = arr[0];
	for (int i = 1; i != arr.size(); ++i)
		ret[i] = ret[i-1] * arr[i];
	int tmp = 1;
	for (int i = arr.size() - 1; i > 0; i--)
	{
		ret[i] = ret[i-1] * tmp;
		tmp *= arr[i];
	}
	ret[0] = tmp;
	return ret;
}

int main()
{
	auto v = product1({2,3,1,4});
	for_each(v.begin(), v.end(), [](auto i) {cout << i << ", ";});
	cout << endl;
	v = product1({2,3,0,1,4});
	for_each(v.begin(), v.end(), [](auto i) {cout << i << ", ";});
	cout << endl;
	v = product1({2,3,0,1,0,4});
	for_each(v.begin(), v.end(), [](auto i) {cout << i << ", ";});
	cout << endl;
	
	v = product2({2,3,1,4});
	for_each(v.begin(), v.end(), [](auto i) {cout << i << ", ";});
	cout << endl;
	v = product2({2,3,0,1,4});
	for_each(v.begin(), v.end(), [](auto i) {cout << i << ", ";});
	cout << endl;
	v = product2({2,3,0,1,0,4});
	for_each(v.begin(), v.end(), [](auto i) {cout << i << ", ";});
	cout << endl;
	return 1;
}
