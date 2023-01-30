#include <iostream>
#include <vector>

/*
给定一个 N×N 的矩阵 matrix，把这个矩阵调整成顺时针转动 90°后的形式。
额外空间复杂度为 O(1)。
*/
using namespace std;
void rotateEdge(vector<vector<int>>& m, int tR, int tC, int dR, int dC)
{
	int times = dC- tC;
	int tmp = 0;
	for (int i = 0; i != times; i++)
	{
		tmp = m[tR][tC+i];
		m[tR][tC+i] = m[dR-i][tC];
		m[dR-i][tC] = m[dR][dC-i];
		m[dR][dC-i] = m[tR+i][dC];
		m[tR+i][dC] = tmp;
	}
}

void rotate(vector<vector<int>>& matrix)
{
	int tR = 0;
	int tC = 0;
	int dR = matrix.size() -1;
	int dC = matrix[0].size() -1;
	while (tC <= dC && tR <= dR)
		rotateEdge(matrix, tR++, tC++, dR--, dC--);
}


int main()
{
	vector<vector<int>> v {{1,2,3,4}, {5,6,7,8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	rotate(v);

	for (auto i : v)
	{
		for (auto j : i)
			cout << j << ",";
		cout << endl;
	}
	return 1;
}
