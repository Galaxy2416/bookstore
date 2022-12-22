#include <iostream>
#include <vector>
/*
给定一个整数 n，代表汉诺塔游戏中从小到大放置的 n 个圆盘，假设开始时所有的圆盘都 放在左边的柱子上，想按照汉诺塔游戏的要求把所有的圆盘都移到右边的柱子上。实现函数打 印最优移动轨迹。

【举例】
n=1 时，打印:
move from left to right
n=2 时，打印:
move from left to mid
move from left to right
move from mid to right
进阶问题:给定一个整型数组 arr，其中只含有 1、2 和 3，代表所有圆盘目前的状态，1 代
表左柱，2 代表中柱，3 代表右柱，arr[i]的值代表第 i+1 个圆盘的位置。比如，arr=[3,3,2,1]，代 表第 1 个圆盘在右柱上、第 2 个圆盘在右柱上、第 3 个圆盘在中柱上、第 4 个圆盘在左柱上。 如果 arr 代表的状态是最优移动轨迹过程中出现的状态，返回 arr 这种状态是最优移动轨迹中的 第几个状态。如果 arr 代表的状态不是最优移动轨迹过程中出现的状态，则返回-1。

【举例】
arr=[1,1]。两个圆盘目前都在左柱上，也就是初始状态，所以返回 0。
arr=[2,1]。第一个圆盘在中柱上、第二个圆盘在左柱上，这个状态是 2 个圆盘的汉诺塔游戏 中最优移动轨迹的第 1 步，所以返回 1。
arr=[3,3]。第一个圆盘在右柱上、第二个圆盘在右柱上，这个状态是 2 个圆盘的汉诺塔游戏 中最优移动轨迹的第 3 步，所以返回 3。
arr=[2,2]。第一个圆盘在中柱上、第二个圆盘在中柱上，这个状态是 2 个圆盘的汉诺塔游戏 中最优移动轨迹从来不会出现的状态，所以返回-1。
进阶问题:如果 arr 长度为 N，请实现时间复杂度为 O(N)、额外空间复杂度为 O(1)的方法。

*/

using namespace std;
void func(int n, string from, string mid, string to)
{
	if (n == 1)
		cout << ("move from " + from + " to " + to) << endl;
	else 
	{
		func(n-1, from, to, mid);
		func(1, from, mid, to);
		func(n-1, mid, from, to);
	}
}

void hanoi(int n)
{
	if (n > 0)
		func(n,"left", "mid", "right");
}

int process(const vector<int>& v, int i, int from, int mid, int to)
{
	if (i == -1)
		return 0;
	if (v[i] != from && v[i] != to)
		return -1;
	if (v[i] == from)
		return process(v, i-1, from, to, mid);
	else
	{
		int rest = process(v, i-1, mid, from, to);
		if (rest == -1)
			return -1;
		return (1 << i) + rest;
	}
}

int step1(const vector<int> v)
{
	if (v.empty())
		return -1;
	return process(v, v.size() - 1, 1, 2, 3);
}

int step2(const vector<int>& v)
{
	if (v.empty())
		return -1;
	int from = 1;
	int mid = 2;
	int to = 3;
	int i = v.size() - 1;
	int res = 0;
	int tmp = 0;
	while (i >= 0) 
	{
		if (v[i] != from && v[i] != to)
			return -1;
		if (v[i] == to)
		{
			res += 1 << i;
			tmp = from;
			from = mid;
		}
		else
		{
			tmp = to;
			to = mid;
		}
		mid = tmp;
		i--;
	}
	return res;
}

int main()
{
	hanoi(10);
	cout << step1({3,3,2,1}) << endl;
	cout << step2({3,3,2,1}) << endl;
	return 1;
}
