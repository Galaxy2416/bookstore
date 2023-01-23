#include <iostream>
#include <cctype>

/*
【题目】
新类型字符的定义如下:
1.新类型字符是长度为 1 或者 2 的字符串。 2.表现形式可以仅是小写字母，例如，"e";也可以是大写字母+小写字母，例如，"Ab";
还可以是大写字母+大写字母，例如，"DC"。
现在给定一个字符串 str，str 一定是若干新类型字符正确组合的结果。比如"eaCCBi"，由新
类型字符"e"、"a"、"CC"和"Bi"拼成。再给定一个整数 k，代表 str 中的位置。请返回被 k 位置指 定的新类型字符。
【举例】
str="aaABCDEcBCg"。 1.k=7 时，返回"Ec"。 2.k=4 时，返回"CD"。 3.k=10 时，返回"g"。
*/

using namespace std;
string pointNewChar(const string& str, int k)
{
	if (str.empty() || k < 0 || k >= str.size())
		return "";
	int uNum = 0;
	for (int i = k - 1; i >= 0; i--)
	{
		if (islower(str[i]))
			break;
		uNum++;
	}

	if (uNum & 1)
		return str.substr(k-1, 2);
	return islower(str[k]) ? str.substr(k, 1) : str.substr(k, 2);
}

int main()
{
	cout << pointNewChar("aaABCDEcBCg", 7) << endl;
	cout << pointNewChar("aaABCDEcBCg", 4) << endl;
	cout << pointNewChar("aaABCDEcBCg", 10) << endl;
	return 1;
}
