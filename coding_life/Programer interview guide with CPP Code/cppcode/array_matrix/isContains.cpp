#include <iostream>
#include <vector>
using namespace std;

/*
【题目】
给定一个 N×M 的整型矩阵 matrix 和一个整数 K，matrix 的每一行和每一列都是排好序的。 实现一个函数，判断 K 是否在 matrix 中。
【要求】
时间复杂度为 O(N+M)，额外空间复杂度为 O(1)。
*/
bool iscontains(const vector<vector<int>>& matrix, int K)
{
	int row = 0;
	int col = matrix[0].size() - 1;
	while (row < matrix.size() && col >= 0)
	{
		if (K == matrix[row][col])
			return true;
		if (K > matrix[row][col])
			row++;
		else 
			col--;
	}
	return false;
}

int main()
{
	cout << iscontains({{0, 1, 2, 5}, {2, 3, 4, 7}, {4, 4, 4 , 8}, {5, 7, 7, 9}}, 7) << endl;
	cout << iscontains({{0, 1, 2, 5}, {2, 3, 4, 7}, {4, 4, 4 , 8}, {5, 7, 7, 9}}, 6) << endl;
}
