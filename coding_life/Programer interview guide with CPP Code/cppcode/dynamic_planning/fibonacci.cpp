#include <iostream>

/*
 【题目】
给定整数 N，返回斐波那契数列的第 N 项。
补充问题 1:给定整数 N，代表台阶数，一次可以跨 2 个或者 1 个台阶，返回有多少种走 法。
【举例】
N=3，可以三次都跨 1 个台阶;也可以先跨 2 个台阶，再跨 1 个台阶;还可以先跨 1 个台 阶，再跨 2 个台阶。所以有三种走法，返回 3。
补充问题 2:假设农场中成熟的母牛每年只会生 1 头小母牛，并且永远不会死。第一年农 场有 1 只成熟的母牛，从第二年开始，母牛开始生小母牛。每只小母牛 3 年之后成熟又可以生 小母牛。给定整数 N，求出 N 年后牛的数量。
【举例】
N=6，第 1 年 1 头成熟母牛记为 a;第 2 年 a 生了新的小母牛，记为 b，总牛数为 2;第 3 年 a 生了新的小母牛，记为 c，总牛数为 3;第 4 年 a 生了新的小母牛，记为 d，总牛数为 4。 第5年b成熟了，a和b分别生了新的小母牛，总牛数为6;第6年c也成熟了，a、b和c分 别生了新的小母牛，总牛数为 9，返回 9。
【要求】
对以上所有的问题，请实现时间复杂度为 O(logN)的解法
*/

using namespace std;

int f1(int n)
{
	if (n < 1)
		return 0;
	if (n == 1 || n == 2)
		return 1;
	return f1(n-1) + f1(n-2);
}

int f2(int n)
{
	if (n < 1)
		return 0;
	if (n == 1 || n == 2)
		return 1;

	int i_1 = 1;
	int i_2 = 1;
	int res = 0;
	
	for (int i = 3; i <= n; ++i)
	{
		res = i_1 + i_2;
		i_2 = i_1;
		i_1 = res;
	}
	return res;
}

void constexpr muliMatrix(int a[][2], int b[][2], int res[][2]) {
	int ret[2][2] = {0,0,0,0};
	for (size_t  i = 0; i < 2; ++i)
		for (size_t j = 0; j < 2; ++j)
			for (size_t k = 0; k < 2; ++k)
				ret[i][j] += a[i][k] * b[k][j];

	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 2; ++j)
			res[i][j] = ret[i][j];
}

void constexpr matrixPower(int m[][2], int p, int res[][2]) 
{
	for (size_t i = 0; i < 2; ++i)
	{
		res[i][i] = 1;
	}

	int temp[2][2];
	for (size_t i = 0; i < 2; ++i)
		for (size_t j = 0; j < 2; ++j) {
			temp[i][j] = m[i][j];
		}

	for (; p != 0; p = p >> 1)
	{
		if ((p & 0x01) != 0)
			muliMatrix(res, temp, res);
		muliMatrix(temp, temp, temp);
	}
}

int constexpr f3 (int n)
{
	if (n < 1)
		return 0;
	if (n == 1|| n == 2)
		return 1;
	int base[2][2]  = {{1, 1}, {1, 0}};
	int res[2][2] = {0,0,0,0};
	matrixPower(base, n - 2, res);
	return res[0][0] + res[1][0];
}

int constexpr s3 (int n)
{
	if (n < 1)
		return 0;
	if (n == 1||n == 2)
		return n;
	int base[2][2]  = {{1, 1}, {1, 0}};
	int res[2][2] = {0,0,0,0};
	matrixPower(base, n - 2, res);
	return res[0][0] + res[1][0];
}

int main ()
{
	cout << f1(10) << endl;
	cout << f2(5) << endl;
	cout << f3(10) << endl;
}
