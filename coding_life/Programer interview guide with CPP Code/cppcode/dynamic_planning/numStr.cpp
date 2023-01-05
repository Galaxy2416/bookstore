#include <iostream>
/*
【题目】
给定一个字符串 str，str 全部由数字字符组成，如果 str 中某一个或某相邻两个字符组成的 子串值在 1~26 之间，则这个子串可以转换为一个字母。规定"1"转换为"A"，"2"转换为"B"，"3" 转换为"C"......"26"转换为"Z"。写一个函数，求 str 有多少种不同的转换结果，并返回种数。
【举例】
str="1111"。 能转换出的结果有"AAAA"、"LAA"、"ALA"、"AAL"和"LL"，返回 5。 str="01"。
"0"没有对应的字母，而"01"根据规定不可转换，返回 0。 str="10"。
能转换出的结果是"J"，返回 1。
*/

using namespace std;
int process(const string& str, size_t i)
{
	if (i == str.size())
		return 1;
	if (str[i] == '0')
		return 0;
	int res = process(str, i+1);
	if (i+1 < str.size() && (str[i] - '0') * 10 + str[i+1] - '0' < 27)
		res += process(str, i+2);
	return res;
}
int num1(string str)
{
	if (str.empty())
		return 0;
	return process(str, 0);
}

int num2(string str)
{
	int cur = str.back() == '0' ? 0 : 1;
	int next = 1;
	int tmp = 0;
	for (int i = str.size() - 2; i >= 0; i--)
	{
		if (str[i] == '0')
		{
			next = cur;
			cur = 0;
		}
		else
		{
			tmp = cur;
			if ((str[i] - '0') * 10 + str[i+1] - '0' < 27)
				cur += next;
			next = tmp;
		}
	}
	return cur;
}

int main()
{
	cout << num1("666666") << endl;
	cout << num1("0") << endl;
	cout << num2("1111") << endl;
}
