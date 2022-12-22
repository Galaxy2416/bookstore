#include <iostream>
/*
【题目】
给定两个字符串 str1 和 str2，返回两个字符串的最长公共子序列。
【举例】
str1="1A2C3D4B56"，str2="B1D23CA45B6A"。 "123456"或者"12C4B6"都是最长公共子序列，返回哪一个都行
*/

using namespace std;


string lcse1(const string& s1, const string& s2)
{
	string r;

	// cout << s1 << ":" << s2 << ", ";
	if (s1.empty() || s2.empty())
		return r;
	string r1 = lcse1(s1.substr(0, s1.size() - 1), s2);
	string r2 = lcse1(s1, s2.substr(0, s2.size() - 1));
	r = r1.size() >= r2.size() ? r1 : r2;
	string r3;
	if (s1.back() == s2.back()) {
		r3 = lcse1(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() - 1));
		r3 += s1.back();
		if (r3.size() > r.size())
			r = r3;
	}
	return r;
}

int** getdp(const string& s1, const string& s2)
{
	int **dp = new int*[s1.size()];
	for (int i = 0; i < s1.size(); i++)
		dp[i] = new int[s2.size()];
	dp[0][0] = s1[0] == s2[0] ? 1 : 0;
	for (int i = 1; i < s1.size(); i++)
	{
		dp[i][0] = max(dp[i-1][0], s1[i] == s2[0] ? 1 : 0);
	}

	for (int j = 1; j < s2.size(); j++)
	{
		dp[0][j] = max(dp[0][j-1], s1[0] == s2[j] ? 1 : 0);
	}

	for (int i = 1; i < s1.size(); i++)
		for (int j = 1; j < s2.size(); j++)
		{
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			if (s1[i] == s2[j])
				dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
		}
	return dp;
}

string lcse2(const string& s1, const string& s2)
{
	if (s1.empty() || s2.empty())
		return {};
	int **dp = getdp(s1, s2); 
	int m = s1.size() - 1;
	int n = s2.size() - 1;
	int index = dp[m][n] - 1; 
	string res(" ",index+1);
	while (index >= 0)
	{
		if (n > 0 && dp[m][n]  == dp[m][n-1])
			n--;
		else if (m > 0 && dp[m][n] == dp[m-1][n])
			m--;
		else {
			res[index--] = s1[m];
			m--;
			n--;
		}
	}
	return res;
}

int main()
{
	cout << lcse1("1A2C3D4B56", "B1D23CA45B6A") << endl;
	cout << lcse2("1A2C3D4B56", "B1D23CA45B6A") << endl;
	
	return 1;
}
