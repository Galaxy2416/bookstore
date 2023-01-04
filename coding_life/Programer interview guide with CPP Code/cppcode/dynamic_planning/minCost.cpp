#include <iostream>
/*
【题目】
给定两个字符串 str1 和 str2，再给定三个整数 ic、dc 和 rc，分别代表插入、删除和替换一 个字符的代价，返回将 str1 编辑成 str2 的最小代价。
【举例】
str1="abc"，str2="adc"，ic=5，dc=3，rc=2。 从"abc"编辑成"adc"，把'b'替换成'd'是代价最小的，所以返回 2。 str1="abc"，str2="adc"，ic=5，dc=3，rc=100。 从"abc"编辑成"adc"，先删除'b'，然后插入'd'是代价最小的，所以返回 8。 str1="abc"，str2="abc"，ic=5，dc=3，rc=2。 不用编辑了，本来就是一样的字符串，所以返回 0。
*/

using namespace std;

int minCost(string str1, string str2, int ic, int dc, int rc)
{
	if (str1.empty() || str2.empty())
		return 0;
	int row = str1.size() + 1;
	int col = str2.size() + 1;
	int **dp = new int*[row];
	for (int i = 0; i != row; ++i) {
		dp[i] = new int[col];
		dp[i][0] = dc * i;
		for (int j = 1; j != col; ++j)
			dp[0][j] = ic * j;
	}

	for (int i = 1; i != row; i++)
	{
		for (int j = 1; j != col; j++)
		{
			if (str1[i-1] == str2[j-1])
				dp[i][j] = dp[i-1][j-1];
			else
				dp[i][j] = min({dp[i][j-1]+ic, dp[i-1][j]+dc, dp[i-1][j-1]+rc});
		}
	}
	return dp[row-1][col-1];
}

int main()
{
	cout << minCost("abc", "adc", 5,3,2) << endl;
	cout << minCost("abc", "adc", 5,3,100) << endl;
	return 0;
}
