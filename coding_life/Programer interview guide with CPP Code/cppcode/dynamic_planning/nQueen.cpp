#include <iostream>
/*
【题目】
N 皇后问题是指在 N×N 的棋盘上要摆 N 个皇后，要求任何两个皇后不同行、不同列，也不在同一条斜线上。给定一个整数 n，返回 n 皇后的摆法有多少种。
【举例】
n=1，返回 1。
n=2 或 3，2 皇后和 3 皇后问题无论怎么摆都不行，返回 0。 n=8，返回 92。
*/

using namespace	std;


bool isValid(int record[], int i, int j)
{
	for (int k = 0; k < i; k++)
		if ( j == record[k] || abs(record[k] - j) == abs(i - k))
			return false;
	return true;
}

int process1(int i, int record[], int n)
{
	if (i == n)
		return 1;
	int res = 0;
	for (int j = 0; j != n; ++j)
	{
		if (isValid(record, i, j)) 
		{
			record[i] = j;
			res += process1(i +1, record, n);
		}
	}
	return res;
}


int num1(int n)
{
	if (n < 1)
		return 0;
	int *record = new int[n];
	return process1(0, record, n);
}


int process2(int upperLim, int colLim, int leftDiaLim, int rightDiaLima)
{
	if (colLim == upperLim)
		return 1;
	int pos = 0;
	int mostRightOne = 0;
	pos = upperLim & (~(colLim | leftDiaLim | rightDiaLima));
	int res = 0;
	while (pos != 0) {
		mostRightOne = pos & (~pos + 1);
		pos -= mostRightOne;
		res += process2(upperLim, colLim | mostRightOne, (leftDiaLim | mostRightOne) << 1, (rightDiaLima | mostRightOne) >> 1);
	}
	return res;
}

int num2(int n)
{
	// 因为本方法中位运算的载体是 int 型变量，所以该方法只能算 1~32 皇后问题 // 如果想计算更多的皇后问题，需使用包含更多位的变量
	if (n < 1 || n > 32)
		return 0;
	int upperLim = n == 32 ? -1 : (1 << n) - 1;
	return process2(upperLim, 0, 0, 0);
}

int main()
{
	cout << num1(8) << endl;
	cout << num2(8) << endl;
}

