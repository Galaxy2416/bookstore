#include <iostream>
#include <vector>
#include <limits>
/*
【题目】
给定一个字符串 str，返回把 str 全部切成回文子串的最小分割数。
【举例】
str="ABA"。
不需要切割，str 本身就是回文串，所以返回 0。
str="ACDCDCDAD"。
最少需要切 2 次变成 3 个回文子串，比如"A"、"CDCDC"和"DAD"，所以返回 2。
*/

using namespace std;
int minCut(const string& str)
{
	if (str.empty())
		return 0;
	int len = str.size();
	vector<int> dp (len+1, 0);
	vector<vector<bool>> p(len, vector<bool>(len, false));

	for (int i = len -1; i >= 0; i--)
	{
		 dp[i] = numeric_limits<int>::max();
		 for (int j = i; j != len; j++)
		 {
			 if (str[i] == str[j] && (j - i < 1 || p[i+1][j-1]))
			 {
				 p[i][j] = true;
				 dp[i] = min(dp[i], dp[j+1] + 1);
			 }
		 }
	}
	return dp[0];
}

int main()
{
	cout << minCut("ACDCDCDAD") << endl;
	return 1;
}
