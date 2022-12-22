#include <iostream>
#include <vector>
/*
【题目】
给定一个 N 行 2 列的二维数组，每一个小数组的两个值分别代表一个信封的长和宽。如果 信封 A 的长和宽都小于信封 B，那么信封 A 可以放在信封 B 里，请返回信封最多嵌套多少层。
时间复杂度为 O(NlogN)。
*/

using namespace std;
using Envelope = pair<int, int>;

int maxEnvelopes(vector<Envelope> v)
{
	vector<Envelope> dp(v.size());
	
	auto sortEnvelope = [](const Envelope& a, const Envelope& b) -> bool { return a.first != b.first ? a.first < b.first : b.second < a.second; };
	std::sort(v.begin(), v.end(), sortEnvelope) ;
	for (auto i : v)
		cout << i.first << ":" << i.second << ", ";
	cout << endl;
	
	vector<int> ends(v.size());
	ends[0] = v[0].second;
	int right = 0;
	int l = 0;
	int r = 0;
	int m = 0;
	for (int i = 1; i < v.size(); i++)
	{
		l = 0;
		r = right;
		while (l <= r)
		{
			m = (l+r)/2;
			if (v[i].second > ends[m])
				l = m + 1;
			else
				r = m -1;
		}
		right = max(right, l);
		ends[l] = v[i].second;
	}
	return right + 1;
}

int main()
{
	auto res = maxEnvelopes({
	{3,4},
    {2,3},
    {4,5},
    {1,3},
    {2,2},
    {3,6},
    {1,2},
    {3,2},
    {2,4}});
	cout << res << endl;
	return 1;
}
