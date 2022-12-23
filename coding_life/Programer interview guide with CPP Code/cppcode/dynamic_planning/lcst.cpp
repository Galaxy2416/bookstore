#include <iostream>
/*
题目
给定两个字符串 str1 和 str2，返回两个字符串的最长公共子串
举例
str1="1AB2345CD"，str2="12345EF"，返回"2345"。
要求
如果 str1 长度为 M，str2 长度为 N，实现时间复杂度为 O(M×N)，额外空间复杂度为 O(1) 的方法。
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
		dp[i][0] = s1[i] == s2[0] ? 1 : 0;
	}

	for (int j = 1; j < s2.size(); j++)
	{
		dp[0][j] = s1[0] == s2[j] ? 1 : 0;
	}

	for (int i = 1; i < s1.size(); i++)
		for (int j = 1; j < s2.size(); j++)
		{
			if (s1[i] == s2[j])
				dp[i][j] = dp[i-1][j-1] + 1;
		}
	return dp;
}

string lcst1(const string& s1, const string& s2)
{
	if (s1.empty() || s2.empty())
		return {};
	int **dp = getdp(s1, s2); 
	int max = 0; 
	int end= 0;
	for (int i = 0; i < s1.size(); i++)
		for (int j = 0; j < s1.size(); j++)
		{
			if (dp[i][j] > max)
			{
				end = i;
				max = dp[i][j];
			}
		}
	return s1.substr(end - max + 1, max);
}

string lcst2(const string& s1, const string& s2)
{
	if (s1.empty() || s2.empty())
		return {};

	int row = 0;
	int col = s2.size() - 1;
	int max = 0;
	int end = 0;
	while (row < s1.size())
	{
		int i = row;
		int j = col;
		int len = 0;
		while (i < s1.size() && j < s2.size())
		{
			if (s1[i] != s2[j])
				len = 0;
			else 
				len++;
			if (len > max)
			{
				end = i;
				max = len;
			}
			i++;
			j++;
		}
		if (col > 0)
			col--;
		else
			row++;
	}
	return s1.substr(end - max + 1, max);
}



int main()
{
	cout << lcst1("1AB2345CD", "12345EF") << endl;
	cout << lcst2("1AB2345CD", "12345EF") << endl;
	
	return 1;
}
