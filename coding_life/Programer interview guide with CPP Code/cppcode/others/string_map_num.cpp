#include <iostream>
#include <vector>

using namespace std;

/*
【题目】
一个 char 类型的数组 chs，其中所有的字符都不同。
例如，chs=['A', 'B', 'C', ... 'Z']，则字符串与整数的对应关系如下:
A, B... Z, AA,AB...AZ,BA,BB...ZZ,AAA... ZZZ, AAAA...
1, 2...26,27, 28... 52,53,54...702,703...18278, 18279...
例如，chs=['A', 'B', 'C']，则字符串与整数的对应关系如下: A,B,C,AA,AB...CC,AAA...CCC,AAAA...
1, 2,3,4,5...12,13...39,40...
给定一个数组 chs，实现根据对应关系完成字符串与整数相互转换的两个函数。
*/

string getString(string chs, int n)
{
	if (chs.empty() || n < 1)
		return "";
	int cur = 1;
	int base = chs.size();
	int len = 0;
	while (n >= cur) {
		len++;
		n -= cur;
		cur *= base;
	}
	string res(len, '\0');
	int index = 0;
	int nCur = 0;
	do 
	{
		cur /= base;
		res[index++] = chs[n/cur];
		n %= cur;
	}
	while (index != res.size());
	return res;
}

int getNumber(const string& chs, const string& str)
{
	if (chs.empty() || str.empty())
		return 0;
	int base = chs.size();
	int cur_base = 1;
	int res = 0;
	char first_char = chs[0];
	for (auto i = str.crbegin(); i != str.crend(); i++)
	{
		res += cur_base * (*i - first_char + 1) ;
		cur_base *= base;
	}
	return res;
}

int main()
{
	cout << getString({'A', 'B', 'C'}, 72) << endl;
	cout << getNumber({'A', 'B', 'C'}, "ABBA") << endl;
	return 1;
}

