#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>
using namespace std;

/* 
【题目】
给定一个字符串 str，判断是不是整体有效的括号字符串。 【举例】
str="()"，返回 true;str="(()())"，返回 true;str="(())"，返回 true。 str="())"。返回 false;str="()("，返回 false;str="()a()"，返回 false。 补充问题:给定一个括号字符串 str，返回最长的有效括号子串。
【举例】
str="(()())"，返回 6;str="())"，返回 2;str="()(()()("，返回 4。
*/


bool isValid(const string& str)
{
	if (str.empty())
		return false;
	int status = 0;
	for (char s : str)
	{
		if (s != '(' && s != ')')
			return false;
		if (s == ')' && --status < 0)
			return false;
		if (s == '(')
			status++;
	}
	return status == 0;
}

int maxLength(const string& str)
{
	if (str.empty())
		return 0;
	
	int *dp = new int[str.size()];
	
	int pre = 0;
	int res = 0;
	dp[0] = 0;
	for (int i = 1; i != str.size(); ++i)
	{
		dp[i] = 0;
		if (str[i] == ')')
		{
			pre = i - dp[i-1] - 1;
			if (pre >= 0 && str[pre] == '(')
				dp[i] = dp[i-1] + 2 + (pre > 0 ? dp[pre - 1] : 0);
			//cout << i << ":" << dp[i] << endl;
		}
		res = max(res, dp[i]);
	}
	return res;
}

int main()
{
	cout << isValid("((((((()))))))") << endl;
	cout << isValid("((((((())))))") << endl;
	cout << isValid("((((())))))") << endl;
	cout << maxLength("((((((())))())))") << endl;
	return 1;
}

