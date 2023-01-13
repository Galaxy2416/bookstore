#include <iostream>
#include <vector>
using namespace std;

/*
题目】
给定一个整型数组 arr，其中只有一个数出现了奇数次，其他的数都出现了偶数次，打印这 个数。
  进阶问题:有两个数出现了奇数次，其他的数都出现了偶数次，打印这两个数。
【要求】
时间复杂度为 O(N)，额外空间复杂度为 O(1)。
*/

int printOddTimesNum(const vector<int>& n)
{
	int eo = 0;
	for (auto i : n)
		eo ^= i;
	return eo;
	
}

pair<int, int> printOddTimesNum2(const vector<int>& n)
{
	int eo = 0, eo1 = 0;
	for (auto i : n)
		eo ^= i;
	int right_one = eo & (~eo+1);
	for (auto i : n)
	{
		if (i&right_one)
			eo1 ^= i;
	}
	return {eo1, eo^eo1};
}

int main()
{
	cout << printOddTimesNum({5,6,7,9,7,6,5}) << endl;
	int eo1, eo0;
	tie(eo1, eo0) = printOddTimesNum2({5,6,7,9,11,6,7,5}); 
	cout << eo1 << ", " << eo0 << endl;
}
