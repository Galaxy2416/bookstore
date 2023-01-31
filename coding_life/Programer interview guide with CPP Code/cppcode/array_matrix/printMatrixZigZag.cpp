#include <iostream>
#include <vector>

/*
给定一个矩阵 matrix，按照“之”字形的方式打印这个矩阵
额外空间复杂度为 O(1)。
*/
using namespace std;
void printLevel(vector<vector<int>>& m, int tR, int tC, int dR, int dC, bool f)
{
	ostream_iterator<int> o(std::cout, ", ");
	if (f)
	{
		while (tR != dR + 1)
		{
			o = m[tR++][tC--];
		}
	}
	else
	{
		while (dR != tR - 1)
		{ 
			o = m[dR--][dC++];
		}
	}
}


void printMatrixZigZag(vector<vector<int>>& matrix)
{
	int tR = 0, dR = 0;
	int tC = 0, dC = 0;
	int endR = matrix.size() -1;
	int endC = matrix[0].size() -1;
	bool fromUp = false;
	while (tR != endR + 1)
	{
		cout << tR << tC << dR << dC << endl;
		printLevel(matrix, tR, tC, dR, dC, fromUp);
		tR = tC == endC ? tR + 1 : tR;
		tC = tC == endC ? tC : tC + 1;
		dC = dR == endR ? dC + 1 : dC;
		dR = dR == endR ? dR : dR + 1;
		fromUp = !fromUp;
	}
	cout << endl;
}


int main()
{
	vector<vector<int>> v {{1,2,3,4}, {5,6,7,8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	printMatrixZigZag(v);
	return 1;
}
