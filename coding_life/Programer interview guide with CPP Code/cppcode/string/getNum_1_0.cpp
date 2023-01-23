#include <iostream>

/*
【题目】
给定一个整数 N，求由"0"字符与"1"字符组成的长度为 N 的所有字符串中，满足"0"字符的 左边必有"1"字符的字符串数量。
【举例】
N=1。只由"0"与"1"组成，长度为 1 的所有字符串:"0"、"1"。只有字符串"1"满足要求，所 以返回 1。
N=2。只由"0"与"1"组成，长度为 2 的所有字符串为:"00"、"01"、"10"、"11"。只有字符串 "10"和"11"满足要求，所以返回 2。
N=3。只由"0"与"1"组成，长度为 3 的所有字符串为:"000"、"001"、"010"、"011"、"100"、 "101"、"110"、"111"。字符串"101"、"110"、"111"满足要求，所以返回 3。
*/

/*
i < N-1 时，p(i) = p(i+1)+p(i+2)
i = N-1时，p(i) = 2
i = N 时，p(i) = 1
*/
using namespace std;
int process(int i, int n)
{
	if (i == n -1)
		return 2;
	if (i == n)
		return 1;
	return process(i + 1, n) + process(i + 2, n);
}

int getNum1(int n)
{
	if (n < 1)
		return 0;
	return process(1, n);
}

int getNum2(int n)
{
	if (n < 1)
		return 0;
	if (n == 1)
		return 1;
	
	int pre = 1;
	int cur = 1;
	int tmp = 0;
	for (int i = 2; i != n + 1; ++i)
	{
		tmp = cur;
		cur = pre + cur;
		pre = tmp;
	}
	return cur;
}

int main()
{
	cout << getNum1(3) << endl;
	cout << getNum2(3) << endl;
	return 1;
}
