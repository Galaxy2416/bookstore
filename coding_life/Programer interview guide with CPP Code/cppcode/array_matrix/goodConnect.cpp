#include <iostream>
#include <vector>

using namespace std;

/*
 N个加油站组成一个环形，给定两个长度都是 N 的非负数组 oil 和 dis(N>1)，oil[i]代表第 i 个加油站存的油可以跑多少千米，dis[i]代表第 i 个加油站到环中下一个加油站相隔多少千米。 假设你有一辆油箱足够大的车，初始时车里没有油。如果车从第 i 个加油站出发，最终可以回 到这个加油站，那么第 i 个加油站就算良好出发点，否则就不算。请返回长度为 N 的 boolean 型数组 res，res[i]代表第 i 个加油站是不是良好出发点。
*/

/*
如果 oil 和 dis 长度为 N，时间复杂度达到 O(N)，额外空间复杂度 O(1)，返回的 boolean 类 型数组不算额外空间。
*/

int changeDisArrayGetInit(vector<int>& dis, const vector<int>& oil)
{
	int init = -1;
	for (int i = 0; i != dis.size(); ++i)
	{
		dis[i] = oil[i] - dis[i];
		if (dis[i] >= 0)
			init = i;
	}
	return init;
}

int lastIndex(int index, int size)
{
	return index == 0 ? (size - 1) : index - 1;
}

int nextIndex(int index, int size)
{
	// return (index + 1) % size; 
	return index == size - 1 ? 0 : (index + 1);
}

void connectGood(const vector<int>& dis, int start, int init, vector<bool>& res)
{
	int need = 0;
	while (start != init) 
	{
		if (dis[start] < need)
			need -= dis[start];
		else 
		{
			res[start] = true;
			need = 0;
		}
		start = lastIndex(start, dis.size());
	}
}

vector<bool> enlargeArea(const vector<int>& dis, int init)
{
	vector<bool> res(dis.size(), false);
	int start = init;
	int end = nextIndex(init, dis.size());
	int need = 0, rest = 0;
	do
	{
		// 当前来到的 start 已经在连通区域中，可以确定后续的开始点一定无法转完一圈
		if (start != init && start == lastIndex(end, dis.size()))
			break;
		// 当前来到的 start 不在连通区域中，就扩充连通区域
		if (dis[start] < need)
			need -= dis[start]; // 从当前 start 出发，无法到达 initial 点 need 增加
		else // 如果可以扩充
		{
			rest += dis[start] - need;
			need = 0;
			while (rest >= 0 && end != start)
			{
				rest += dis[end];
				end = nextIndex(end, dis.size());
			}
			if (rest >= 0) // 如果连通区域已经覆盖整个环，当前的 start 是良好出发点，进入 2 阶段
			{
				res[start] = true;
				connectGood(dis, lastIndex(start, dis.size()), init, res);
				break;
			}
		}
		start = lastIndex(start, dis.size());
	} while (start != init);

	return res;
}

vector<bool> stations(vector<int> dis, const vector<int>& oil)
{
	if (dis.empty() || oil.empty() || dis.size() < 2 || dis.size() != oil.size())
		return {};
	int init = changeDisArrayGetInit(dis, oil);
	return init == -1 ? vector<bool>(dis.size(), false) : enlargeArea(dis, init);
}

int main()
{
	auto res = stations({6, 1, 3, 1, 6, 4, 1, 1, 6}, {4, 2, 0, 4, 5, 2, 3, 6, 2});
	for (auto r : res)
		cout << r << ", ";
	cout << endl;
	res = stations({1, 9, 1, 2, 6, 0, 2, 0}, {4, 5, 3, 1, 5, 1, 1, 9});
	for (auto r : res)
		cout << r << ", ";
	cout << endl;

	return 1;
}
