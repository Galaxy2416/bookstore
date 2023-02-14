#include <iostream> 
#include <vector>

using namespace std;

/*
【题目】
给定一个长度不小于 2 的数组 arr，实现一个函数调整 arr，要么让所有的偶数下标都是偶 数，要么让所有的奇数下标都是奇数。
【要求】
如果 arr 的长度为 N，函数要求时间复杂度为 O(N)、额外空间复杂度为 O(1)。
*/

int main()
{	
	vector v{1,2,3,4,5,6,7,8,9};
	int even = 0;
	int odd = 1;
	while (even < v.size() || odd < v.size())
	{
		if (v.back() & 0x01) {
			swap(v[odd], v.back());
			odd += 2;
		}
		else {
			swap(v[even], v.back());
			even += 2;
		}
			
	}
	for_each(v.begin(), v.end(), [](auto i) { cout << i << ","; });
	cout << endl;
	return 1;
}
