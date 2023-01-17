#include <iostream>
#include <vector>
#include <limits>
using namespace std;
/*
【题目】
给定一个字符串 str，如果 str 符合日常书写的整数形式，并且属于 32 位整数的范围，返回 str 所代表的整数值，否则返回 0。
【举例】
str="123"，返回 123。 str="023"，因为"023"不符合日常的书写习惯，所以返回 0。
str="A13"，返回 0。
str="0"，返回 0。
str="2147483647"，返回 2147483647。 str="2147483648"，因为溢出了，所以返回 0。 str="-123"，返回-123。
*/

bool isValid(const string& chas)
{
	if (chas[0] != '-' && (chas[0] < '0' || chas[0] > '9'))
		return false;
	if (chas[0] == '-' && (chas.size() == 1 || chas[1] == '0'))
		return false;
	if (chas[0] == '0' && chas.size() > 1)
		return false;
	for (int i = 1; i != chas.size(); i++)
		if (chas[i] < '0' || chas[i] > '9')
			return false;
	return true;
}

int convert(string str)
{
	if (str.empty())
		return 0;
	if (!isValid(str))
		return 0;
	bool posi = str[0] == '-' ? false : true;
	int minq = numeric_limits<int>::min() / 10;
	int minr = numeric_limits<int>::min() % 10;
	int res = 0;
	int cur = 0;
	for (int i = posi ? 0 : 1; i < str.size(); i++)
	{
		cur = '0' - str[i];
		if ((res < minq) || (res == minq && cur < minr))
			return 0;
		res = res * 10 + cur;
	}
	if (posi && res == numeric_limits<int>::min())
		return 0;
	return posi ? -res : res;
}

int main()
{
	cout << convert("34535") << endl;
	cout << convert("-34535") << endl;
	cout << convert("01") << endl;
	cout << convert("0") << endl;
	cout << convert("-0") << endl;
	cout << convert("2147483648") << endl;
	cout << convert("2147483647") << endl;
	cout << convert("-2147483648") << endl;
	
}
