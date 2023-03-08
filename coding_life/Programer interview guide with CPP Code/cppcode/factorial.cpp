#include <iostream>
#include <vector>

using namespace std;

/*
给定一个非负整数 N，返回 N!结果的末尾为 0 的数量。
例如:3!=6，结果的末尾没有 0，则返回 0。5!=120，结果的末尾有 1 个 0，返回 1。1000000000!，
结果的末尾有 249999998 个 0，返回 249999998。
进阶问题:给定一个非负整数 N，如果用二进制数表达 N!的结果，返回最低位的 1 在哪个
位置上，认为最右的位置为位置 0。
例如:1!=1，最低位的 1 在 0 位置上。2!=2，最低位的 1 在 1 位置上。1000000000!，最低
位的 1 在 999999987 位置上。
*/

int zeroNum1(int num)
{
	if (num < 0)
		return 0;
	int res = 0;
	int cur = 0;
	for (int i = 5; i < num + 1;  i += 5)
	{
		cur = i;
		while (cur % 5 == 0)
		{
			res++;
			cur /= 5;
		}
	}
	return res;
}

int zeroNum2(int num)
{
	if (num < 0)
		return 0;
	int res = 0;
	while (num != 0)
	{
		res += num / 5;
		num /= 5;
	}
	return res;
}

int rightOne1(int num)
{
	if (num < 1)
		return -1;
	int res = 0;
	while (num != 0)
	{
		num >>= 1;
		res += num;
	}
	return res;
}

/*
如果把 N!的结果中因子 2 的总个数记为 Z，把 N 的二进制数表达式中 1 的个数记为 m，还存在如下一个关系 Z = N - m，也就是可以证明 N/2 + N/4 + N/8 + ...=N-m
*/

int rightOne2(int num)
{
	if (num < 1) 
		return -1;
	int ones = 0;
	int tmp = num;
	while (tmp != 0)
	{
		ones += (tmp & 1) != 0 ? 1 : 0;
		tmp >>= 1;
	}
	return num - ones;
}

int main()
{
	cout << zeroNum1(1000000000) << endl;
	cout << zeroNum2(1000000000) << endl;
	cout << rightOne1(1000000000) << endl;
	cout << rightOne2(1000000000) << endl;
}
