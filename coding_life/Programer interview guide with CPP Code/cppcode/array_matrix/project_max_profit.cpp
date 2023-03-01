#include <iostream>
#include <queue>

using namespace std;

/*
给定两个整数 W 和 K，W 代表你拥有的初始资金，K 代表你最多可以做 K 个项目。再给定 两个长度为 N 的正数数组 costs[]和 profits[]，代表一共有 N 个项目，costs[i]和 profits[i]分别表示 第 i 号项目的启动资金与做完后的利润(注意是利润，如果一个项目启动资金为 10，利润为 4， 代表该项目最终的收入为 14)。你不能并行只能串行地做项目，并且手里拥有的资金大于或等 于某个项目的启动资金时，你才能做这个项目。该如何选择做项目，能让你最终的收益最大? 返回最后能获得的最大资金。
【举例】
W=3
K=2
costs = {5, 4, 1, 2}
profits = {3, 5, 3, 2}
初始资金为 3，最多做 2 个项目，每个项目的启动资金与利润见 costs 和 profits。最优选择
为:先做 2 号项目，做完之后资金增长到 6。然后做 1 号项目，做完之后资金增长到 11。其他 的任何选择都不会比这种选择好，所以返回 11。

时间复杂度为 O(KlogN)。
*/

struct Program
{
	int cost;
	int profit;
	Program(int cost_, int profit_) : cost(cost_), profit(profit_) 
	{}
};

struct CostMinCmp
{
	bool operator () (const Program& l, const Program& r)
	{
		return l.cost > r.cost;
	}
};


struct ProfitMaxCmp
{
	bool operator () (const Program& l, const Program& r)
	{
		return l.profit <  r.profit;
	}
};

int getMaxNumber(int W, int K, const vector<int>& costs, const vector<int>& profits)
{
	if (W < 1 || K < 0 || costs.empty() || profits.empty() || costs.size() != profits.size())
		return 0;
	priority_queue<Program, vector<Program>, CostMinCmp> costMinQueue{};
	priority_queue<Program, vector<Program>, ProfitMaxCmp> profitMaxQueue{};
	for (int i = 0; i != costs.size(); ++i)
		costMinQueue.emplace(costs[i], profits[i]);
	for (int i = 1; i <= K; i++) 
	{
		while (!costMinQueue.empty() && costMinQueue.top().cost <= W) {
			profitMaxQueue.push(costMinQueue.top());
			costMinQueue.pop();
		}
		if (profitMaxQueue.empty())
			return W;
		W += profitMaxQueue.top().profit;
		profitMaxQueue.pop();
	}
	return W;
}

int main() 
{
	cout << getMaxNumber(3, 2, {5, 4, 1, 2}, {3, 5, 3, 2}) << endl;
	return 1;
}
