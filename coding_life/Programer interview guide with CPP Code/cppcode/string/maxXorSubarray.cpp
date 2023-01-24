#include <iostream>
#include <vector>
#include <limits>
#include <vector>

/*
【题目】
数组异或和的定义:把数组中所有的数异或起来得到的值。
给定一个整型数组 arr，其中可能有正、有负、有零，求其中子数组的最大异或和。
【举例】
arr = {3}
数组只有 1 个数，所以只有一个子数组，就是这个数组本身，最大异或和为 3。 arr = {3, -28, -29, 2}
子数组有很多，但是{-28, -29}这个子数组的异或和为 7，是所有子数组中最大的。
【要求】
如果 arr 长度为 N，时间复杂度 O(N)。
*/

using namespace std;
int maxXorSubarray1(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	
	vector<int> eor(arr.size(), 0);
	eor[0] = arr[0];
	
	for (int i = 1; i != arr.size(); ++i)
	{
		eor[i] = eor[i-1] ^ arr[i];
	}

	int max = numeric_limits<int>::min();
	for (int j = 0; j != arr.size(); ++j)
	{
		for (int i = 0; i <= j ; ++i)
			max = std::max(max, i == 0 ? eor[j] : eor[j] ^ eor[i-1]);
	}

	return max;
}

struct Node
{
	vector<Node*> nexts{nullptr, nullptr};
};

class NumTire 
{
	Node head;

	public:
	
	void add(int newNum)
	{
		Node* cur = &head;
		for (int move = 31; move >= 0; move--)
		{
			int path = ((newNum >> move) & 0x01);
			cur->nexts[path] = cur->nexts[path] == nullptr ? new Node() : cur->nexts[path];
			cur = cur->nexts[path];
		}
	}

	int maxXor(int eorj)
	{
		Node* cur = &head;
		int res = 0;
		for (int move = 31; move >= 0; move--)
		{
			int path = (eorj >> move) & 0x01;
			int best = move == 31 ? path : path ^ 1;
			if (!cur->nexts[best])
				best ^= 1;
			res |= (path ^ best) << move;
			cur = cur->nexts[best];
		}
		return res;
	}
};

int maxXorSubarray2(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	
	NumTire tire;
	tire.add(0);
	
	int eor = 0;
	int rmax = numeric_limits<int>::min();
	for (int i = 1; i != arr.size(); ++i)
	{
		eor ^= arr[i];
		rmax = max(rmax, tire.maxXor(eor));
		tire.add(i);
	}
	return rmax;
}

int main()
{
	cout << maxXorSubarray1({3, -28, -29, 2}) << endl;
	cout << maxXorSubarray2({3, -28, -29, 2}) << endl;
}
