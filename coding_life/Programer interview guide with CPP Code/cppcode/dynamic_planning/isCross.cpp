#include <iostream>
using namespace std;

/*
【题目】
 给定三个字符串 str1、str2 和 aim，如果 aim 包含且仅包含来自 str1 和 str2 的所有字符，而 且在aim中属于str1的字符之间保持原来在str1中的顺序，属于str2的字符之间保持原来在str2 中的顺序，那么称 aim 是 str1 和 str2 的交错组成。实现一个函数，判断 aim 是否是 str1 和 str2 交错组成。
【举例】
str1="AB"，str2="12"。那么"AB12"、"A1B2"、"A12B"、"1A2B"和"1AB2"等都是 str1 和 str2 的 交错组成。
【解答】
如果 str1 的长度为 M，str2 的长度为 N，经典动态规划的方法可以达到时间复杂度为 O(M×N)，额外空间复杂度为 O(M×N)。如果结合空间压缩的技巧，可以把额外空间复杂度减至 O(min{M,N})。
*/

bool isCross(string str1, string str2, string aim)
{
	if (str1.empty() || str2.empty() || aim.empty())
		return false;
	if (aim.size() != str2.size() + str1.size())
		return false;
	bool **dp = new bool*[str1.size()+1];
	for (int i = 0; i <= str1.size(); i++)
	{
		dp[i] = new bool[str2.size() + 1];
	}
	dp[0][0] = true;
	
	for (int i = 1; i <= str1.size(); i++)
	{
		if (str1[i-1] != aim[i-1])
			break;
		dp[i][0] = true;
	}

	for (int j = 1; j <= str2.size(); j++)
	{
		if (str2[j-1] != aim[j-1])
			break;
		dp[0][j] = true;
	}

	for (int i = 1; i <= str1.size(); i++)
		for (int j = 1; j <= str2.size(); j++)
			if ((str1[i-1] == aim[i+j-1] && dp[i-1][j]) || (str2[j-1] == aim[i+j-1] && dp[i][j-1]))
				dp[i][j] = true;
	return dp[str1.size()][str2.size()];
}


int main()
{
	
	cout << isCross("AB", "12", "AB12") << endl;
	cout << isCross("AB", "12", "A1B2") << endl;
	cout << isCross("AB", "12", "A12B") << endl;
	cout << isCross("AB", "12", "1A2B") << endl;
	cout << isCross("AB", "12", "1AB2") << endl;
	cout << isCross("AB", "12", "1B2A") << endl;
	return 0;
}


