#include <iostream>
#include <algorithm>
#include <vector>
/*
 * 给定数组 arr，arr 中所有的值都为正数且不重复。每个值代表一种面值的货币，每种面值 的货币可以使用任意张，再给定一个整数 aim，代表要找的钱数，求组成 aim 的最少货币数。
 */

using namespace std;

vector<int> process(const vector<size_t>& v, size_t i, size_t rest) 
{
	if (i == v.size()) {
		if (rest == 0) {
			return {0} ; }
		else {
			return {-1};
		}
	}
	vector<int> res {-1};
	for (int k = 0; k*v[i] <= rest; ++k)
	{
		auto next = process(v, i+1, rest-k*v[i]);
		if (next[0] != -1) 
		{
			//valid
			if (res[0] == -1) 
			{
				res[0] =  next[0] + k;
				res.push_back(v[i]);
			}
			else 
			{
				if (res[0] > next[0] + k)
				{
					res[0] =  next[0] + k;
					res.push_back(v[i]);
				}
			}
			// res[0] = res[0] == -1 ? next[0] + k : min(res[0], next[0]+k);
			// std::move(next.begin(), next.end(), std::back_inserter(res));
		}
	}
	return res;
}


vector<int> minCoin1(const vector<size_t>& v, size_t aim)
{
	if (v.empty())
		return {-1};
	return process(v, 0, aim);
}

int minCoin2(const vector<size_t>& v, size_t aim)
{
	if (v.empty())
		return -1;
	int** dp = new int*[v.size()+1];
	for (int i = 0; i < v.size()+1; ++i)
		dp[i] = new int[aim + 1];
	for (int col = 1; col <= aim; col++)
	{
		dp[v.size()][col] = -1;
	}
	for (int i = v.size() -1; i >= 0; i--)
	{
		for (int rest = 0; rest <= aim; rest++) 
		{
			dp[i][rest] = -1;
			if (dp[i+1][rest] != -1) 
			{
				dp[i][rest] = dp[i+1][rest];
			}
			if (rest - v[i] >= 0 && dp[i][rest - v[i]] != -1)
			{
				if (dp[i][rest] == -1) 
					dp[i][rest] = dp[i][rest - v[i]] + 1;
				else
					dp[i][rest] = min(dp[i][rest], dp[i][rest - v[i]] + 1);
			}
		}
	}

	return dp[0][aim];
}

int main()
{
	auto res = minCoin1({5,2,3}, 20);
	for (auto i : res)
		cout << i << endl;
	cout << "dp:" << minCoin2({5,2,3}, 20) << endl;
	return 0;
}

