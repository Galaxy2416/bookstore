#include <iostream>
#include <vector>
using namespace std;

/*
【题目】
给定两个字符串 str1 和 str2，如果 str1 和 str2 中出现的字符种类一样且每种字符出现的次 数也一样，那么 str1 与 str2 互为变形词。请实现函数判断两个字符串是否互为变形词。
【举例】
str1="123"，str2="231"，返回 true。 str1="123"，str2="2331"，返回 false。
*/


bool isDeformation(string str1, string str2)
{
	if (str1.empty() || str2.empty())
		return false;
	
	vector<int> map(256, 0);

	for (auto i : str1)
		map[(int)i]++;
	for (auto i : str2)
	{
		if (map[(int)i]-- == 0)
			return false;
	}

	for (auto i : map)
		if (i)
			return false;

	return true;

}

int main()
{
	cout << isDeformation("abccb", "bcbca") << endl;

	// WARNING : The book solution is wrong for this
	cout << isDeformation("abccb2", "bcbca") << endl;
	cout << isDeformation("abccb", "bcbca2") << endl;
	return 1;
}
