#include <iostream>

/*

【题目】
给定两个32位整数a和b，返回a和b中较大的.
【要求】
不用做任何比较判断。
*/

using namespace std;
int flip (int n)
{
	return n ^ 1;
}

int sign (int n)
{
	return flip((n >> 31) & 1);
}

int getMax1(int a, int b)
{
	int c = a - b;
	int scA = sign(c);
	int scB = flip(scA);
	return a * scA + b * scB;
}

int getMax2(int a, int b)
{
	int sa = sign(a);
	int sb = sign(b);
	int sc = sign(a-b);
	int difSab = sa ^ sb;
	int sameSab = flip(difSab);
	int ra = difSab * sa + sameSab * sc;
	int rb = flip(ra);
	return a*ra + b*rb;
}

int main()
{
	cout << getMax1(123,443) << endl;
	cout << getMax1(1233,443) << endl;

	cout << getMax2(123,443) << endl;
	cout << getMax2(-1233,443) << endl;
}
