#include <iostream>
#include <vector>
#include <limits>

/*
【题目】
给定字符串 str，其中绝对不含有字符'.'和'*'。再给定字符串 exp，其中可以含有'.'或'*'，'*' 字符不能是 exp 的首字符，并且任意两个'*'字符不相邻。exp 中的'.'代表任何一个字符，exp 中 的'*'表示'*'的前一个字符可以有 0 个或者多个。请写一个函数，判断 str 是否能被 exp 匹配。
【举例】
str="abc"，exp="abc"，返回 true。
str="abc"，exp="a.c"，exp 中单个'.'可以代表任意字符，所以返回 true。 str="abcd"，exp=".*"。exp 中'*'的前一个字符是'.'，所以可表示任意数量的'.'字符，当 exp
是"...."时与"abcd"匹配，返回 true。
str=""，exp="..*"。exp 中'*'的前一个字符是'.'，可表示任意数量的'.'字符，但是".*"之前还
有一个'.'字符，该字符不受'*'的影响，所以 str 起码有一个字符才能被 exp 匹配。所以返回 false。
*/

using namespace std;
bool isValid(const string& s, const string& e)
{
	for (char c : s)
	{
		if (c == '*' || c == '.')
			return false;
	}

	for (int i = 0; i != e.size(); ++i)
	{
		if (e[i] == '*' && (i == 0 || e[i-1] == '*'))
			return false;
	}
	return true;
}

bool process(const string& s, const string& e, int si, int ei)
{
	if (ei == e.size())
		return si == s.size();
	if (ei == e.size() -1 || e[ei+1] != '*')
	{
		return si != s.size() && (e[ei] == s[si] || e[ei] == '.') ?  process(s, e, si + 1, ei + 1) : false;
	}
	while(si != s.size() && (e[ei] == s[si] || e[ei] == '.'))
	{
		if (process(s, e, si, ei+2))
			return true;
		si++;
	}
	return process(s, e, si, ei+2);
}


bool isMatch(const string& s, const string& e)
{
	if (s.empty() || e.empty())
		return false;
	return isValid(s, e) ? process(s, e, 0, 0) : false;
}


vector<vector<bool>> initDPMap(const string& s, const string& e)
{
	int slen = s.size();
	int elen = e.size();
	
	vector<vector<bool>> dp(slen + 1, vector<bool>(elen + 1, false));
	dp[slen][elen] = true;
	for (int j = elen - 2; j > -1; j -= 2)
	{
		if (e[j] != '*' && e[j+1] == '*')
			dp[slen][j] = true;
		else
			break;
	}
	if (slen > 0 && elen > 0)
		if ((e[elen-1] == s[slen-1]) || e[elen-1] == '.')
			dp[slen-1][elen-1] = true;
	return dp;
}

bool isMatchDP(const string& s, const string& e)
{
	if (s.empty() || e.empty())
		return false;
	if (!isValid(s, e))
		return false;
	auto dp = initDPMap(s, e);
	for (int i = s.size() - 1; i > -1; i--)
		for (int j = e.size() - 2; j > -1; j--)
		{
			if (e[j+1] != '*')
				dp[i][j] = (e[j] == s[i] || e[j] == '.') && dp[i+1][j+1];
			else 
			{
				int si = i;
				while (si < s.size() && (e[j] == s[si] || e[j] == '.'))
				{
					if (dp[si][j+2])
					{
						dp[i][j] = dp[si][j+2];
						break;
					}
					si++;
				}
				if(!dp[i][j])
					dp[i][j] = dp[si][j+2];
			}
			cout << i << ", " << j << ":" << dp[i][j] << endl;
		}
	return dp[0][0];
}

int main()
{
	cout << isMatch("abc", "a.c") << endl;
	cout << isMatch("abc", "abc") << endl;
	cout << isMatch("abcd", ".*") << endl;
	cout << isMatch("", "..*") << endl;

	cout << isMatchDP("abc", "a.c") << endl;
	cout << isMatchDP("abc", "abc") << endl;
	cout << isMatchDP("abcd", ".*") << endl;
	cout << isMatchDP("", "..*") << endl;
}

