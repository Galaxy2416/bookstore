#include <iostream>
#include <limits>
#include <vector>
#include <numeric>

/*
一条直线上有居民点，邮局只能建在居民点上。给定一个有序整型数组 arr，每个值表示居 民点的一维坐标，再给定一个正数 num，表示邮局数量.
选择 num 个居民点建立 num 个邮局， 使所有的居民点到邮局的总距离最短，返回最短的总距离。

【举例】
arr=[1,2,3,4,5,1000]，num=2。
第一个邮局建立在 3 位置，第二个邮局建立在 1000 位置。那么 
1 位置到邮局的距离为 2， 
2 位置到邮局距离为 1，
3 位置到邮局的距离为 0，
4 位置到邮局的距离为 1，
5 位置到邮局的距 离为 2，
1000 位置到邮局的距离为 0。
这种方案下的总距离为 6，其他任何方案的总距离都不会 比该方案的总距离更短，所以返回 6。
*/

// w 矩阵求解过程的时间复杂度为 O(N2)，动态规划求解过程的时间复杂度为 O(N2×num)。所 以方法一总的时间复杂度为 O(N2)+O(N2×num)，即 O(N2×num)

using namespace std;
int minDistances1(const vector<int>& arr, int num) 
{
	if (arr.empty() || num < 1)
		return 0;

	// w[i][j](0≤i≤j<N)的值 代表如果在 arr[i..j](0≤i≤j<N)区域上只建一个邮局，这一区间上的总距离为多少。
	vector<vector<int>> w(arr.size()+1, vector<int>(arr.size()+1, 0));

	for (int i = 0; i < arr.size(); i++)
		for (int j = i + 1; j < arr.size(); j++) 
			w[i][j] = w[i][j-1] + arr[j] - arr[(i+j)/2];

	vector<vector<int>> dp(num, vector<int>(arr.size(), 0));

	for (int i = 0; i != arr.size(); i++)
	{
		dp[0][i] = w[0][i];
	}

	// dp[a][b] = min { dp[a - 1][k] + w[k + 1][b] (0<=k<N) }。
	for (int i = 1; i < num; i++)
		for (int j = i+1; j < arr.size(); j++)
		{
			dp[i][j] = std::numeric_limits<int>::max();
			for (int k = 0; k <= j; k++)
				dp[i][j] = min(dp[i][j], dp[i-1][k] + w[k+1][j]);
		}

	return dp[num-1][arr.size()-1];
}

/*
方法二， 
用四边形不等式优化动态规划的枚举过程，使整个过程的时间复杂度降低至O(N^2)。
在方法一中求解dp[a][b]的时候，几乎枚举了所有的dp[a-1][0..b] 但这个枚举过程其实是可以得到加速的。

具体解释为:

1 当邮局为a-1个，区间为arr[0..b]时，如果在其最优划分方案中发现，邮局1~a-2
负责arr[0..l]，邮局a-1 负责arr[l+1..b]。
那么当邮局为a 个，区间为arr1[0..b]时，如果想得到最优方案，邮局1~a-1负责的区域不必尝试比arr[0..l]小的区域, 只需尝试arr[0..k](k<=m) 。

2. 当邮局为a 个，区间为arr[0..b+1]时，如果在其最优划分方案中发现，邮局1~a-1负责arr[0..m]，邮局a 负责arr[m+1..b+1]。那么当邮局为a个,
区间为arr[0..b]时，如果想得到最优方案，邮局1~a-1负责的区域不必尝试比arr[0..m] 大的区域，只尝试arr[0..k](k<=m).

本题为何能用四 边形不等式进行优化的证明略。有兴趣的读者可以自行学习 “四边形不等式〞的相关内容。有了这个枚举优化过程后，在算dp[a][b]时，
只用在dp[a-1][b] 的最优尝试位置1和dp[a][b+1] 的最优尝试位置m之间进行枚举，其他的位置一概不用再试。具体过程请参看如下代码中的minDistances2方法。
*/

int minDistances2(const vector<int>& arr, int num) 
{
	if (arr.empty() || num < 1)
		return 0;
	// w[i][j](0≤i≤j<N)的值 代表如果在 arr[i..j](0≤i≤j<N)区域上只建一个邮局，这一区间上的总距离为多少。
	vector<vector<int>> w(arr.size()+1, vector<int>(arr.size()+1, 0));

	for (int i = 0; i < arr.size(); i++)
		for (int j = i + 1; j < arr.size(); j++) 
			w[i][j] = w[i][j-1] + arr[j] - arr[(i+j)/2];

	vector<vector<int>> dp(num, vector<int>(arr.size(), 0));
	vector<vector<int>> s(num, vector<int>(arr.size(), 0));

	for (int i = 0; i != arr.size(); i++)
	{
		dp[0][i] = w[0][i];
		s[0][i] = 0;
	}

	int minK = 0;
	int maxK = 0;
	int cur = 0;

	// dp[a][b] = min { dp[a - 1][k] + w[k + 1][b] (0<=k<N) }。
	for (int i = 1; i < num; i++)
		for (int j = arr.size() - 1; j > i; j--)
		{
			minK = s[i-1][j];
			maxK = j == arr.size() - 1 ? arr.size() - 1 : s[i][j+1];
			dp[i][j] = std::numeric_limits<int>::max();
			for (int k = minK; k <= maxK; k++) {
				int cur = dp[i-1][k] + w[k+1][j];
				if (cur <= dp[i][j])
				{
					dp[i][j] = cur;
					s[i][j] = k;
				}
			}
		}

	return dp[num-1][arr.size()-1];
}

int main()
{
	cout << minDistances1({1,2,3,4,5,1000}, 2) << endl;
	cout << minDistances2({1,2,3,4,5,1000}, 2) << endl;
	return 1;
}
