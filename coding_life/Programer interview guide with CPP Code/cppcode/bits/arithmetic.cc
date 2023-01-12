#include <iostream>
#include <bitset>
#include <stdexcept>
#include <limits>
/*
【题目】
给定两个 32 位整数 a 和 b，可正、可负、可 0。不能使用算术运算符，分别实现 a 和 b 的 加减乘除运算。
【要求】
如果给定的 a 和 b 执行加减乘除的某些结果本来就会导致数据的溢出，那么你实现的函数 不必对那些结果负责。
*/

using namespace std;
int add(int a, int b)
{
	int sum = a;
	while (b)
	{
		// cout << "a:" << bitset<32>(a) << endl;
		// cout << "b:" << bitset<32>(b) << endl;
		sum = a ^ b;
		b = (a & b) << 1;
		a = sum;
	}
	return sum;
}

int negNum(int n)
{
	return add(~n, 1);
}
int min(int a, int b)
{
	return add(a,negNum(b));
}

int multi(int a, int b)
{
	int res = 0;
	while (b)
	{
		if ((b & 1) != 0)
			res = add(res, a);
		a <<= 1;
		b >>= 1;
	}
	return res;
}

bool isNeg(int n)
{
	return n < 0;
}

int div_2(int a, int b)
{
	int x = isNeg(a) ? negNum(a) : a;
	int y = isNeg(b) ? negNum(b) : b;
	int res = 0;
	for (int i = 31; i > -1; i = min(i, 1))
	{
		if ((x >> i) >= y) {
			res |= (1 << i);
			x = min(x, y << i);
		}
	}
	return isNeg(a) ^ isNeg(b) ? negNum(res) : res;
}

int divide(int a, int b)
{
	if (b == 0)
		throw std::runtime_error("divide 0");
	if (a == std::numeric_limits<int>::min() && b == std::numeric_limits<int>::min())
		return 1;
	else if (b == std::numeric_limits<int>::min())
		return 0;
	else if (a == std::numeric_limits<int>::min())
	{
		int res = div_2(add(a, 1), b);
		return add(res, div_2(min(a, multi(res, b)), b));
	}
	else
		return div_2(a, b);
}

int main()
{
	cout << add(5, -1) << endl;
	cout << min(5, 2) << endl;
	cout << multi(26, 87) << endl; 
	cout << div_2(25, 5) << endl;
	cout << div_2(25, 5) << endl;
	cout << div_2(25, -5) << endl;
	cout << div_2(-25, -5) << endl;
	cout << divide(-30, -4) << endl;
	cout << divide(-2147483648, 2) << endl;
}
