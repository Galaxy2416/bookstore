#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

/*
【题目】
用一个整型矩阵 matrix 表示一个网络，1 代表有路，0 代表无路，每一个位置只要不越界， 都有上下左右 4 个方向，求从最左上角到最右下角的最短通路值。
例如，matrix 为:
10111
10101
11101
00001
通路只有一条，由 12 个 1 构成，所以返回 12。
*/

using matrix = vector<vector<int>>;
using point = pair<size_t, size_t>;

void walkTo(int pre, int toR, int toC, const matrix& m, matrix& tmap, queue<point>& q)
{
	if (toR < 0 || toR == m.size() || toC < 0 || toC == m[0].size() || m[toR][toC] != 1)
		return;
	tmap[toR][toC] = pre + 1;
	q.emplace(toR, toC);
}

int minPathValue(const matrix& m)
{
	if (m.empty() || m[0][0] != 1 || m.back().back() != 1)
		return 0;
	int res = 0;
	matrix tmap (m.size(), vector<int>(m[0].size(), 0));
	tmap[0][0] = 1;
	queue<point> q;
	int r = 0;
	int c = 0;
	q.emplace(r, c);
	while (!q.empty())
	{
		auto [r, c] = q.front();
		q.pop();
		if (r == m.size() - 1 && c == m[0].size() - 1)
			return tmap[r][c];
		walkTo(tmap[r][c], r - 1, c, m, tmap, q);
		walkTo(tmap[r][c], r + 1, c, m, tmap, q);
		walkTo(tmap[r][c], r, c - 1, m, tmap, q);
		walkTo(tmap[r][c], r, c + 1, m, tmap, q);
	}
	return res;
}

int main()
{
	matrix m {{1,0,1,1,1}, {1,0,1,0,1}, {1,1,1,0,1}, {0,0,0,0,1}};
	cout << minPathValue(m) << endl;
	return 1;
}
