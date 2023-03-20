#include <iostream>
#include <vector>

/*
假设函数 Math.random()等概率随机返回一个在[0,1)范围上的数，那么我们知道，在[0,x)区 间上的数出现的概率为 x(0<x≤1)。给定一个大于 0 的整数 k，并且可以使用 Math.random() 函数，请实现一个函数依然返回在[0,1)范围上的数，但是在[0,x)区间上的数出现的概率为 xk(0<x ≤1)。
*/



#include <cmath>

using namespace std;

double randXPower2()
{
	return max( (double) rand() / (RAND_MAX), (double) rand() / (RAND_MAX));
}

double randXPowerk(int k)
{
	if (k < 1)
		return 0;
	double res = -1;
	for (int i = 0; i != k; i++)
		res = max(res, (double) rand() / (RAND_MAX));
	return res;
}

int main()
{
	cout << randXPowerk(3) << endl;
}
