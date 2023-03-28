#include <iostream>
#include <limits>
#include <queue>


/*
给定两个有序数组 arr1 和 arr2，再给定一个整数 k，返回来自 arr1 和 arr2 的两个数相加和 最大的前 k 个，两个数必须分别来自两个数组。
【举例】
arr1=[1,2,3,4,5]，arr2=[3,5,7,9,11]，k=4。 返回数组[16,15,14,14]。
【要求】
时间复杂度达到 O(klogk)
*/


#include <limits>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Node 
{
	int index1;
	int index2;
	int value;

	Node(int i1, int i2, int v) : index1(i1), index2(i2), value(v)
	{
	}
};

template<>
struct less<Node>
{
	bool operator() (const Node& n1, const Node& n2) {
		return n1.value < n2.value; 
	}
};


template <>
struct hash<Node>
{
	std::size_t operator()(const Node& k) const
	{
		using std::size_t;
		using std::hash;
		return (hash<int>()(k.index1) ^ (hash<int>()(k.index2) << 1));
	}
};


vector<int> topKSum(const vector<int>& arr1, const vector<int>& arr2, int k)
{
	if (arr1.empty() || arr2.empty() || k < 1)
		return {};
	k = std::min((size_t)k, arr1.size() * arr2.size());
	vector<int> res(k, std::numeric_limits<int>::min());

	int ri = 0;
	priority_queue<Node> max_heap;
	unordered_set<string> hset;
	int i1 = arr1.size() - 1;
	int i2 = arr2.size() - 1;
	max_heap.emplace(i1, i2, arr1[i1] + arr2[i2]);
	hset.insert(to_string(i1) + "_" + to_string(i2));

	while (ri != k)
	{
		auto nd = max_heap.top();
		max_heap.pop();
		res[ri++] = nd.value;
		i1 = nd.index1;
		i2 = nd.index2;
		if (!hset.contains(to_string(i1-1) + "_" + to_string(i2)))
		{
			hset.insert(to_string(i1-1) + "_" + to_string(i2));
			max_heap.emplace(i1-1, i2, arr1[i1-1] + arr2[i2]);
		}
		if (!hset.contains(to_string(i1) + "_" + to_string(i2-1)))
		{
			hset.insert(to_string(i1) + "_" + to_string(i2-1));
			max_heap.emplace(i1, i2-1, arr1[i1] + arr2[i2-1]);
		}
	}
	
	return res;
}

int main()
{

	for (auto i : topKSum({1,2,3,4,5}, {3,5,7,9,11}, 4))
	{
		cout << i << ", ";
	}

	cout << endl;
}
