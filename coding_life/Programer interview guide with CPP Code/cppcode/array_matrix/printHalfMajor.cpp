#include <iostream>
#include <vector>
#include <unordered_map>

/*
【题目】
给定一个整型数组 arr，打印其中出现次数大于一半的数，如果没有这样的数，打印提示信息。
进阶问题:给定一个整型数组 arr，再给定一个整数 K，打印所有出现次数大于 N/K 的数，
如果没有这样的数，打印提示信息。
【要求】
原问题要求时间复杂度为 O(N)，额外空间复杂度为 O(1)。进阶问题要求时间复杂度为 O(N×K)，额外空间复杂度为 O(K)。
*/

using namespace std;
void printHalfMajor(const vector<int>& arr)
{
	int cand= 0;
	int times = 0;
	for (auto i : arr)
	{
		if (times == 0)
		{
			cand = i;
			times++;
		}
		else if (i == cand)
		{
			times++;
		}
		else 
		{
			times--;
		}
	}

	times = 0;
	for (auto i : arr)
	{
		if (i == cand)
			times++;
	}

	if (times > arr.size() / 2)
		cout << cand << endl;
	else 
		cout << "no such number" << endl;
}

/*
进阶问题解法核心也是类似的，一次在数组中删掉 K 个不同的数，不停地删除，直到剩下 的数的种类不足 K，那么，如果某些数在数组中出现次数大于 N/K，则这些数最后一定会被剩下 来。原问题中，我们解决了找到出现次数超过 N/2 的数，解决的办法是立了 1 个候选 cand，以 及这个候选的 times 统计。进阶问题具体的实现也类似，只要立 K-1 个候选，然后有 K-1 个 times 统计即可，具体过程如下。
*/

void printMajor(const vector<int>& arr, int K)
{
	if (K < 2)
	{
		cout << "The value of K is invalid" << endl;
		return;
	}

	unordered_map<int, int> cands {};
	for (auto i : arr)
	{
		if (cands.contains(i))
			cands[i]++;
		else 
		{
			if (cands.size() == K - 1)
			{
				for (auto iter = cands.begin(); iter != cands.end();)
				{
					if (--iter->second == 0)
						iter = cands.erase(iter);
					else
						iter++;
				}

			}
			else 
			{
				cands[i] = 1;
			}
		}
	}
	// check number > N/K
	for (auto iter = cands.begin(); iter != cands.end(); ++iter)
		iter->second = 0;
	for (auto i : arr)
		if (cands.contains(i))
			++cands[i];
	bool flag = true;
	for (auto iter = cands.begin(); iter != cands.end(); ++iter)
		if (iter->second > arr.size() / K) {
			cout << iter->first << ", ";
			flag = false;
		}
	if (flag)
		cout << "The value of K is invalid" << endl;
	cout << endl;
}

int main()
{
	printHalfMajor({1,3,4,5,6,7,8,9,4,3,4,5,1});
	printHalfMajor({1,3,4,5,6,7,8,9,4,3,4,5,1});
	printMajor({1,3,4,5,6,7,8,9,4,3,4,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 2);
	printMajor({1,3,4,5,6,7,8,9,4,3,3,3,1,1,1,1,1,1,1}, 5);
	return 1;
}
