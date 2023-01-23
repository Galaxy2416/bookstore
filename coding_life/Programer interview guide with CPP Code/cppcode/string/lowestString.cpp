#include <iostream>
#include <algorithm>
#include <vector>
/*
【题目】
给定一个字符串类型的数组 strs，请找到一种拼接顺序，使得将所有的字符串拼接起来组 成的大写字符串是所有可能性中字典顺序最小的，并返回这个大写字符串。
【举例】
strs=[ "abc"，"de" ]，可以拼成"abcde"，也可以拼成"deabc"，但前者的字典顺序更小，所以 返回"abcde"。
strs=["b"，"ba" ]，可以拼成"bba"，也可以拼成"bab"，但后者的字典顺序更小，所以返回 "bab"。
*/

using namespace std;

string lowestString(vector<string> str)
{
	if (str.empty())
		return "";
	sort(str.begin(), str.end(), [](const string& a, const string& b) {
			return (a + b) < (b + a);
			});
	string ret;
	for (const auto& s : str)
		ret += s;
	return ret;
}

int main()
{
	cout << lowestString({"abc", "de"}) << endl;
	return 1;
}
