#include <iostream>
#include <unordered_map>
#include <vector>
/*
【题目】
给定无序数组 arr，返回其中最长的连续序列的长度。
【举例】
arr=[100,4,200,1,3,2]，最长的连续序列为[1,2,3,4]，所以返回 4。
哈希表可以实现时间复杂度为 O(N)、额外空间复杂度为 O(N)的方法
*/

using namespace std;
using M = unordered_map<int, int>;

int merge(M& m, int less, int more)
{
	int left = less - m[less] + 1;
	int right = more + m[more] - 1;
	int len = right - left + 1;
	m[left] = len;
	m[right] = len;
	return len;
}

int longestConsecutive(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	int max = 1;
	M m;
	for (auto i : arr)
	{
		if (!m.contains(i)) 
		{
			m[i] = 1;
			if (m.contains(i - 1))
				max = std::max(max, merge(m, i - 1, i));
			if (m.contains(i + 1))
				max = std::max(max, merge(m, i, i + 1));
		}

	}
	return max;
}

int main()
{
	cout << longestConsecutive({100,4,200,1,3,2}) << endl;
	return 1;
}
