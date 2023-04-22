#include <iostream>
#include <vector>
#include <limits>

using namespace std;

/*
一座大楼有 0~N 层，地面算作第 0 层，最高的一层为第 N 层。已知棋子从第 0 层掉落肯定 不会摔碎，从第 i 层掉落可能会摔碎，也可能不会摔碎(1≤i≤N)。给定整数 N 作为楼层数， 再给定整数 K 作为棋子数，返回如果想找到棋子不会摔碎的最高层数，即使在最差的情况下扔 的最少次数。一次只能扔一个棋子。
*/

/*
【举例】
N=10，K=1。
返回 10。
因为只有 1 棵棋子，所以不得不从第 1 层开始一直试到第 10 层，在最差的情况 下，即第 10 层是不会摔坏的最高层，最少也要扔 10 次。

N=3，K=2。
返回 2。
先在 2 层扔 1 棵棋子，如果碎了，试第 1 层，如果没碎，试第 3 层。

N=105，K=2
返回 14。
第一个棋子先在 14 层扔，碎了则用仅存的一个棋子试 1~13。 
若没碎，第一个棋子继续在 27 层扔，碎了则用仅存的一个棋子试 15~26。 
若没碎，第一个棋子继续在 39 层扔，碎了则用仅存的一个棋子试 28~38。 
若没碎，第一个棋子继续在 50 层扔，碎了则用仅存的一个棋子试 40~49。 
若没碎，第一个棋子继续在 60 层扔，碎了则用仅存的一个棋子试 51~59。 
若没碎，第一个棋子继续在 69 层扔，碎了则用仅存的一个棋子试 61~68。 
若没碎，第一个棋子继续在 77 层扔，碎了则用仅存的一个棋子试 70~76。 
若没碎，第一个棋子继续在 84 层扔，碎了则用仅存的一个棋子试 78~83。 
若没碎，第一个棋子继续在 90 层扔，碎了则用仅存的一个棋子试 85~89。 
若没碎，第一个棋子继续在 95 层扔，碎了则用仅存的一个棋子试 91~94。 
若没碎，第一个棋子继续在 99 层扔，碎了则用仅存的一个棋子试 96~98。 
若没碎，第一个棋子继续在 102 层扔，碎了则用仅存的一个棋子试 100、101。 
若没碎，第一个棋子继续在 104 层扔，碎了则用仅存的一个棋子试 103。 
若没碎，第一个棋子继续在 105 层扔，
若到这一步还没碎，那么 105 便是结果。
*/

int Process1(int nLevel, int kChess)
{
	// cout << nLevel << ", " << kChess << endl;
	if (nLevel == 0)
		return 0;
	if (kChess == 1)
		return nLevel;
	int min_ = std::numeric_limits<int>::max();
	for (int i = 1; i != nLevel + 1; i++)
	{
		min_ = min(min_, max(Process1(i-1, kChess-1), Process1(nLevel-i, kChess)));
	}
	return min_ + 1;
}

// O(N!)
int solution1(int nLevel, int kChess)
{
	if (nLevel < 1 || kChess < 1)
		return 0;
	return Process1(nLevel, kChess);
}

// O(N2 ×K)
int solution2(int nLevel, int kChess) 
{
	if (nLevel < 1 || kChess < 1)
		return 0;
	if (kChess == 1)
		return nLevel;
	vector<vector<int>> dp (nLevel+1, vector<int>(kChess + 1, 0));
	// dp[0][K] = 0，dp[N][1] = N，dp[N][K] = min{max{dp[i-1][K-1], dp[N-i][K]} (1<= i<=N) } +1
	for (int i = 1; i != dp.size(); i++)
	{
		dp[i][1] = i;
	}
	for (int i = 1; i != dp.size(); i++)
	{
		for (int j = 2; j != dp[0].size(); j++) {
			int min_ = std::numeric_limits<int>::max();
			for (int k = 1; k != i + 1; k++) {
				min_ = min(min_, max(dp[k-1][j-1], dp[i-k][j]));
			}
			dp[i][j] = min_ + 1;
		}
	}
	return dp[nLevel][kChess];
}

// save space 
int solution3(int nLevel, int kChess) 
{
	if (nLevel < 1 || kChess < 1)
		return 0;
	if (kChess == 1)
		return nLevel;
	vector<int> preArr(nLevel+1, 0);
	vector<int> curArr(nLevel+1, 0);
	// dp[0][K] = 0，dp[N][1] = N，dp[N][K] = min{max{dp[i-1][K-1], dp[N-i][K]} (1<= i<=N) } +1
	for (int i = 1; i != curArr.size(); i++)
	{
		curArr[i] = i;
	}
	for (int i = 1; i != kChess; i++) {
		auto tmp = preArr;
		preArr = curArr;
		curArr = tmp;
		for (int j = 1; j != curArr.size(); j++) {
			int min_ = std::numeric_limits<int>::max();
			for (int k = 1; k != j + 1; k++) {
				min_ = min(min_, max(curArr[j-k], preArr[k-1]));
			}
			curArr[j] = min_ + 1;
		}
	}
	return curArr[nLevel];
}

// 四边形不等式 可以从 O(N2×k)或 O(N3)降到 O(N2)
int solution4(int nLevel, int kChess) 
{
	if (nLevel < 1 || kChess < 1)
		return 0;
	if (kChess == 1)
		return nLevel;
	vector<vector<int>> dp (nLevel+1, vector<int>(kChess + 1, 0));
	vector<int> cands(kChess+1, 0);
	// dp[0][K] = 0，dp[N][1] = N，dp[N][K] = min{max{dp[i-1][K-1], dp[N-i][K]} (1<= i<=N) } +1
	for (int i = 1; i != dp.size(); i++)
	{
		dp[i][1] = i;
	}
	for (int i = 1; i != dp[0].size(); i++)
	{
		dp[1][i] = 1;
		cands[i] = 1;
	}

	for (int i = 2; i != dp.size(); i++)
	{
		for (int j = kChess; j > 1; j--) {
			int min_ = std::numeric_limits<int>::max();
			int minEum = cands[j];
			int maxEum = j == kChess ? i / 2 - 1 : cands[j+1];
			for (int k = minEum; k <= maxEum; k++) {
				int cur = max(dp[k-1][j-1], dp[i-k][j]);
				if (cur <= min_) 
				{
					min_ = cur;
					cands[j] = k;
				}
			}
			dp[i][j] = min_ + 1;
		}
	}
	return dp[nLevel][kChess];
}

/*
如果棋子数为 K、楼层数为 N，最终的结果为 M 次，那么最优解的时间复杂度为 O(K×M)， 在棋子数大于 logN+1 时，时间复杂度为 O(logN)。在只有一个棋子的时候，K×M 等于 N，在其 他情况下，K×M 比 N 要小得多。
*/
int log2N(int n)
{
	int res = -1;
	while (n)
	{
		res++;
		n >>=1;
	}
	return res;
}

int solution5(int nLevel, int kChess) 
{
	if (nLevel < 1 || kChess < 1)
		return 0;
	if (kChess == 1)
		return nLevel;
	int bsTime = log2N(nLevel) + 1;
	if (kChess >= bsTime)
		return bsTime;

	vector<int> dp(kChess, 0);
	int res = 0;
	while (true)
	{
		res++;
		int previous = 0;
		for (int i = 0; i != dp.size(); i++)
		{
			int tmp = dp[i];
			dp[i] = dp[i] + previous + 1;
			previous = tmp;
			if (dp[i] >= nLevel)
				return res;
		}
	}
}

int main()
{
	cout << solution1(10, 2) << endl;
	cout << solution2(10, 2) << endl;
	cout << solution3(10, 2) << endl;
	cout << solution4(10, 2) << endl;
	cout << solution5(105, 2) << endl;
	return 1;
}
