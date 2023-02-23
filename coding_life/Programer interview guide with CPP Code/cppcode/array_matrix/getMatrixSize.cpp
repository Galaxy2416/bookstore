#include <iostream>
#include <vector>


/*
给定一个 N×N 的矩阵 matrix，在这个矩阵中，只有 0 和 1 两种值，返回边框全是 1 的最大 正方形的边长长度。
例如:
01111
01001
01001
01111
01011
其中，边框全是 1 的最大正方形的大小为 4×4，所以返回 4。
*/

using namespace std;

using matrix = vector<vector<int>>;

void SetBorderMap(const matrix& m, matrix& right, matrix& down)
{
	std::for_each(right.begin(), right.end(),
			[](auto& sub) {
			std::fill(sub.begin(), sub.end(), 0);
			});
	std::for_each(down.begin(), down.end(),
			[](auto& sub) {
			std::fill(sub.begin(), sub.end(), 0);
			});

	int r = m.size();
	int c = m[0].size();
	if (m[r-1][c-1] == 1) {
		right[r-1][c-1] = 1;
		down[r-1][c-1] = 1;
	}
	for (int i = r - 2; i != -1; i--)
		if (m[i][c-1] == 1)
		{
			right[i][c-1] = 1;
			down[i][c-1] = down[i+1][c-1] + 1;
		}
			
	for (int i = c - 2; i != -1; i--)
		if (m[r-1][i] == 1)
		{
			down[r-1][i] = 1;
			right[r-1][i] = right[r-1][i+1] + 1;
		}

	for (int i = r - 2; i != -1; i--)
		for (int j = c - 2; j != -1; j--)
		{
			if (m[i][j] == 1)
			{
				right[i][j] = right[i][j+1] + 1;
				down[i][j] = down[i+1][j] + 1;
			}
			else 
			{
				right[i][j] = 0;
				down[i][j] = 0;
			}
		}
}


bool HasSizeOfBorder(int size, const matrix& right, const matrix& down)
{
	for (int i = 0; i != right.size() - size + 1; i++)
		for (int j = 0; j != right[0].size() - size + 1; j++)
			if (right[i][j] >= size && down[i][j] >= size && right[i+size-1][j] >= size && down[i][j+size-1] >= size)
				return true;
	return false;
}


int main()
{
	matrix m {{0, 1, 1, 1, 1}, {0, 1, 0, 0, 1}, {0, 1, 0, 0, 1}, {0, 1, 1, 1, 1}, {0, 1, 0, 1, 1}};
	matrix right = m;
	matrix down = m;
	SetBorderMap(m, right, down);
	for (int size = min(m.size(), m[0].size()); size != 0; size--)
		if (HasSizeOfBorder(size, right, down)) {
			cout << size << endl;
			break;
		}
	return 1;
}
