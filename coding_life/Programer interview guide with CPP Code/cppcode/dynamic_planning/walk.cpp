/*
假设有排成一行的 N 个位置，记为 1~N，N 一定大于或等于 2。开始时机器人在其中的 M 位置上(M 一定是 1~N 中的一个)，机器人可以往左走或者往右走，如果机器人来到 1 位置， 那么下一步只能往右来到 2 位置;如果机器人来到 N 位置，那么下一步只能往左来到 N-1 位置。 规定机器人必须走 K 步，最终能来到 P 位置(P 也一定是 1~N 中的一个)的方法有多少种。给 定四个参数 N、M、K、P，返回方法数
时间复杂度为 O(N×K)
*/

#include "iostream"

using namespace std;
int walk(int N, int cur, int rest, int P)
{
	if (rest == 0) 
	{
		return cur == P ? 1 : 0;
	}
	if (cur == 1)
		return walk(N, 2, rest - 1, P);
	if (cur == N)
		return walk(N, N - 1, rest - 1, P);
	return walk(N, cur + 1, rest - 1, P) + walk(N, cur - 1, rest - 1, P);
}

int walk1(int N, int M, int K, int P)
{
	if (N < 2 || K < 1 || M < 1 || M > N || P < 1 || P > N)
		return 0;
	return walk(N, M, K, P);
}

int walk2(int N, int M, int K, int P)
{
	if (N < 2 || K < 1 || M < 1 || M > N || P < 1 || P > N)
		return 0;

	int **dp = new int*[N+1];
	for (int i = 0; i != N; ++i)
		dp[i] = new int[K+1];
	dp[0][P-1] = 1;

	for (int j = 0; j != N; ++j)
		cout << dp[0][j] << ",";
	cout << endl;
	
	for  (int i = 1; i <= K; ++i) {
		for (int j = 0; j != N; ++j)
		{
			dp[i][j] = (j > 0 ? dp[i-1][j-1] : 0)  + (j < N - 1 ? dp[i-1][j+1] : 0);
			cout << dp[i][j] << ",";
		}
		cout << endl;
	}
	return dp[K][M-1];
}

int main()
{
	cout << walk1(5,2,3,3) << endl;
	cout << walk2(5,2,3,3) << endl;
	return 1;
}
