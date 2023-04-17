#include <iostream>
#include <vector>

/*
【题目】
一群孩子做游戏，现在请你根据游戏得分来发糖果，要求如下: 
1.每个孩子不管得分多少，起码分到 1 个糖果。 
2.任意两个相邻的孩子之间，得分较多的孩子必须拿多一些的糖果。 给定一个数组 arr 代表得分数组，请返回最少需要多少糖果。 
例如:arr=[1,2,2]，糖果分配为[1,2,1]，即可满足要求且数量最少，所以返回 4。 
进阶问题:原题目中的两个规则不变，再加一条规则: 
3.任意两个相邻的孩子之间如果得分一样，糖果数必须相同。
给定一个数组 arr 代表得分数组，返回最少需要多少糖果。 
例如:arr=[1,2,2]，糖果分配为[1,2,2]，即可满足要求且数量最少，所以返回 5。

【要求】
arr 长度为 N，原题与进阶题都要求时间复杂度为 O(N)，额外空间复杂度为 O(1)。
*/

using namespace std;

int nextMinIndex1(const vector<int>& arr, int start)
{
	for (int i = start; i != arr.size() - 1; ++i)
		if (arr[i] <= arr[i+1])
			return i;
	return arr.size() - 1;
}

int rightCands(const vector<int>& arr, int left, int right)
{
	int n = right - left + 1;
	return n + n * (n -1) / 2;
}

int candy1(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	int index = nextMinIndex1(arr, 0);
	int res = rightCands(arr, 0, index++); // = 1
	cout << res << ", ";
	int lbase = 1;
	int next = 0;
	int rcands = 0;
	int rbase = 0;
	while (index != arr.size())
	{
		if (arr[index] > arr[index - 1])
		{
			res += ++lbase;
			cout << res << ", ";
			index++;
		}
		else if (arr[index] < arr[index - 1])
		{
			next = nextMinIndex1(arr, index - 1);
			rcands = rightCands(arr, index - 1, next++);
			rbase = next - index + 1; // (next - 1) - (index - 1) + 1
			res += (rcands + ((rbase > lbase) ? -lbase : -rbase));
			cout << res << ", ";
			lbase = 1;
			index = next;
		}
		else 
		{
			res += 1;
			cout << res << ", ";
			lbase = 1;
			index++;
		}
	}
	cout << endl;
	return res;
}

pair<int, int> rightCandsAndBase(const vector<int>& arr, int left, int right)
{
	int base = 1;
	int cands = 1;
	for (int i = right - 1; i >= left; i--)
	{
		if (arr[i] == arr[i+1]){
			cands += base;
		}
		else {
			cands += ++base;
		}
	}
	return {cands, base};
}

int candy2(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	int index = nextMinIndex1(arr, 0);
	auto [res, _] = rightCandsAndBase(arr, 0, index++); // = 1
	int lbase = 1;
	int same = 1;
	int next = 0;
	while (index != arr.size())
	{
		if (arr[index] > arr[index - 1])
		{
			res += ++lbase;
			index++;
		}
		else if (arr[index] < arr[index - 1])
		{
			next = nextMinIndex1(arr, index - 1);
			auto [rcands, rbase] = rightCandsAndBase(arr, index - 1, next++);
			if (lbase >= rbase) {
				res += rcands - rbase;

			}
			else {
				res += rbase * (same - 1) - lbase * same + rcands;
			}
			lbase = 1;
			index = next;
			same = 1;
		}
		else 
		{
			res += lbase;
			lbase = 1;
			same++;
			index++;
		}
	}
	return res;
}

int main()
{
	cout << candy1({1,4,5,9,3,2}) << endl;
	cout << candy2({1,4,5,9,3,2}) << endl;
	cout << candy2({0,1,2,3,3,3,2,2,2,2,2,1,1}) << endl;
	return 1;
}
