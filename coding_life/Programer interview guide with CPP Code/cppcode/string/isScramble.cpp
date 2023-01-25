#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
(N>1)，左部分长度可以为 1~N-1，剩下的为右部分的长度。左部分和右部分都可以按照 同样的逻辑，继续分解。形成的所有结构都是 str 的二叉树结构。比如，字符串"abcd"，可以分
解成五种结构.
给定两个字符串 str1 和 str2，判断 str2 是不是 str1 的旋变字符串。
【要求】
str1 和 str2 长度为 N，时间复杂度做到 O(N4)。
*/

bool sameTypeSameNumber(const string& str1, const string& str2)
{
	if (str1.size() != str2.size())
		return false;
	vector<int> map(256, 0);
	for (int i = 0; i != str1.size(); i++)
		map[str1[i]]++;
	for (int i = 0; i != str2.size(); i++)
		if (--map[str2[i]]  < 0)
			return false;
	return true;
}

bool process(const string& str1, const string& str2, int L1, int L2, int size)
{
	if (size == 1)
		return str1[L1] == str2[L2];
	for (int leftpart = 1; leftpart != size; leftpart++)
	{
		if ((process(str1, str2, L1, L2, leftpart) && process(str1, str2, L1+leftpart, L2+leftpart, size-leftpart)) || 
			(process(str1, str2, L1, L2 + size - leftpart, leftpart) && process(str1, str2, L1 + leftpart, L2, size - leftpart)))  
			return true;
	}
	return false;
}

bool isScramble1(const string& str1, const string& str2)
{
	if ((str1.empty() && !str2.empty()) || (!str1.empty() && str2.empty())) 
		return false;
	if (str1 == str2)
		return true;
	if (!sameTypeSameNumber(str1, str2))
		return false;
	int N = str1.size();
	return process(str1, str2, 0, 0, N);
}

bool isScramble2(const string& str1, const string& str2)
{
	if ((str1.empty() && !str2.empty()) || (!str1.empty() && str2.empty())) 
		return false;
	if (str1 == str2)
		return true;
	if (!sameTypeSameNumber(str1, str2))
		return false;
	int N = str1.size();

	vector<vector<vector<bool>>> dp(N, vector<vector<bool>>(N, vector<bool>(N+1, false)));
	for (int L1 = 0; L1 < N; L1++)
		for (int L2 = 0; L2 < N; L2++)
			dp[L1][L2][1] = str1[L1] == str2[L2];

	for (int size = 2; size <= N; size++) {
		for (int L1 = 0; L1 <= N - size; L1++) {
			for (int L2 = 0; L2 <= N - size; L2++) {
				for (int leftpart = 1; leftpart < size; leftpart++) {
					if ((dp[L1][L2][leftpart] && dp[L1+leftpart][L2+leftpart][size-leftpart]) || 
						 (dp[L1][L2+size-leftpart][leftpart] && dp[L1+leftpart][L2][size-leftpart]))  {
						dp[L1][L2][size] = true;
						break;
					}
				}
			}
		}
	}
	return dp[0][0][N];
}


int main()
{
	cout << isScramble1("abcd", "cadb") << endl;
	cout << isScramble1("abcd", "dbac") << endl;

	cout << isScramble2("abcd", "cadb") << endl;
	cout << isScramble2("abcd", "dbac") << endl;
}
