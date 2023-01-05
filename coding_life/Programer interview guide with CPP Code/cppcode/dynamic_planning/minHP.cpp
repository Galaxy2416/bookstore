#include <iostream>
/*
【题目】
给定一个二维数组 map，含义是一张地图，例如，如下矩阵: 
-2 -3 3
-5 -10 1
0 30 -5
游戏的规则如下:
 骑士从左上角出发，每次只能向右或向下走，最后到达右下角见到公主。
 地图中每个位置的值代表骑士要遭遇的事情。如果是负数，说明此处有怪兽，要让骑
士损失血量。如果是非负数，代表此处有血瓶，能让骑士回血。
 骑士从左上角到右下角的过程中，走到任何一个位置时，血量都不能少于1。 为了保证骑士能见到公主，初始血量至少是多少?根据 map，返回初始血量。
*/

using namespace std;

template<int M, int N>
int minHP(const int (&m)[M][N])
{
	int row = M;
	int col = N;
	int **dp = new int*[row];
	for (int i = 0; i != col; ++i)
		dp[i] = new int[col];
	--row;
	--col;
	dp[row][col] = m[row][col] > 0 ? 1 : -m[row][col]  + 1;
	for (int j = col - 1; j >= 0; j--)
		dp[row][j] = max(dp[row][j+1]  - m[row][j], 1);
	int right = 0;
	int down = 0;
	for(int i = row - 1; i >= 0; i--)
	{
		dp[i][col] = max(dp[i+1][col] - m[i][col], 1);
		for (int j = col - 1; j >= 0; j--)
		{
			right = max(dp[i][j+1] - m[i][j], 1);
			down = max(dp[i+1][j] - m[i][j], 1);
			dp[i][j] = min(right, down);
		}
	}
	return dp[0][0];
}

int main()
{
	int game[3][3] = {-2,-3,3,-5,-10,1,0,30,-5};
	cout << minHP(game) << endl;
	return 1;
}
