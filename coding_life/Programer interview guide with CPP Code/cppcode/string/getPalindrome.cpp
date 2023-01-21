#include <iostream>
#include <vector>
/*
【题目】
给定一个字符串 str，如果可以在 str 的任意位置添加字符，请返回在添加字符最少的情况下，让 str 整体都是回文字符串的一种结果。
【举例】
str="ABA"。str 本身就是回文串，不需要添加字符，所以返回"ABA"。
str="AB"。可以在'A'之前添加'B'，使 str 整体都是回文串，故可以返回"BAB"。也可以在'B' 之后添加'A'，使 str 整体都是回文串，故也可以返回"ABA"。总之，只要添加的字符数最少，返 回其中一种结果即可。
进阶问题:给定一个字符串 str，再给定 str 的最长回文子序列字符串 strlps，请返回在添加 字符最少的情况下，让 str 整体都是回文字符串的一种结果。进阶问题比原问题多了一个参数， 请做到时间复杂度比原问题的实现低。
【举例】
str="A1B21C"，strlps="121"，返回"AC1B2B1CA"或者"CA1B2B1AC"。总之，只要是添加的字 符数最少，只返回其中一种结果即可。
*/

using namespace std;

vector<vector<int>> getDP(const string& str)
{
	vector<vector<int>> dp(str.size(), vector<int>(str.size(), 0));
	for (int j = 1; j < str.size(); ++j)
	{
		dp[j][j] = 0;
		dp[j-1][j] = str[j-1] == str[j] ? 0 : 1;
		for (int i = j - 2; i > -1; i--)
		{
			if (str[i] == str[j])
				dp[i][j] = dp[i+1][j-1];
			else 
			{
				dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
			}
		}
	}
	return dp;
}

string getPalindrome(const string& str)
{
	if (str.empty() || str.size() < 2)
		return str;
	auto dp = getDP(str);
	string res(str.size() + dp[0][str.size()-1], 0);
	int i =0, j=str.size() - 1;
	int resi =0, resj=res.size() - 1;
	while(i <= j)
	{
		if (str[i] == str[j])
		{
			res[resi++] = str[i++];
			res[resj--] = str[j--];
		}
		else if (dp[i][j -1] < dp[i+1][j])
		{
			res[resi++] = str[j];
			res[resj--] = str[j--];
		}
		else
		{
			res[resj--] = str[i];
			res[resi++] = str[i++]; 
		}
	}
	return res;
}


string getPalindrome2(const string& chas, const string& strlps)
{
	if (chas.empty())
		return chas;

	string res(2 * chas.size() - strlps.size(), 0);
	int chasl = 0, chasr = chas.size() - 1;
	int lpsl = 0, lpsr = strlps.size() - 1;
	int resl = 0, resr = res.size() - 1;
	int templ = 0, tempr = 0;
	while (lpsl <= lpsr)
	{
		templ = chasl;
		tempr = chasr;
		while (chas[chasl] != strlps[lpsl])
			chasl++;
		while(chas[chasr] != strlps[lpsr])
			chasr--;

		// copy to res
		for (int i = templ; i < chasl; i++ )
		{
			res[resl++] = chas[i];
			res[resr--] = chas[i];
		}
		for (int i = tempr; i > chasr; i--)
		{
			res[resl++] = chas[i];
			res[resr--] = chas[i];
		}
		
		res[resl++] = chas[chasl++];
		res[resr--] = chas[chasr--];

		lpsl++;
		lpsr--;
	}
	return res;
}

int main()
{
	cout << getPalindrome("A1B21C") << endl;
	cout << getPalindrome2("A1BC22DE1F", "1221") << endl;
	return 1;
}
