#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
【题目】
给定一个正数数组 arr，arr 的累加和代表金条的总长度，arr 的每个数代表金条要分成的长 度。规定长度为 K 的金条只需分成两块，费用为 K 个铜板。返回把金条分出 arr 中的每个数字 需要的最小代价。
【举例】
arr={10,30,20}，金条总长度为 60。
如果先分成 40 和 20 两块，将花费 60 个铜板，再把长度为 40 的金条分成 10 和 30 两块， 将花费 40 个铜板，总花费为 100 个铜板;如果先分成 10 和 50 两块，将花费 60 个铜板，再把 长度为 50 的金条分成 20 和 30 两块，将花费 50 个铜板，总花费为 110 个铜板;如果先分成 30 和 30 两块，将花费 60 个铜板，再把其中一根长度为 30 的金条分成 10 和 20 两块，将花费 30 个铜板，总花费为 90 个铜板。所以返回最低花费为 90。
【要求】
如果 arr 长度为 N，时间复杂度为 O(NlogN)。
*/

int getMinSplitCost(const vector<int>& arr)
{
	if (arr.empty() || arr.size() < 1)
		return 0;
	priority_queue<int, vector<int>, greater<int>> q (arr.begin(), arr.end());
	int ans = 0;
	while (q.size() != 1)
	{
		int t = q.top(); q.pop();
		t += q.top(); q.pop();
		ans += t;
		q.emplace(ans);
	}
	return ans;
}

int main()
{
	cout << getMinSplitCost({3,9,5,2,4,4}) << endl;
	cout << getMinSplitCost({{10,30,20}}) << endl;
	return 1;
}

