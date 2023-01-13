#include <iostream>
#include <vector>
using namespace std;

/*
【题目】
给定一个整型数组 arr 和一个大于 1 的整数 k。已知 arr 中只有 1 个数出现了 1 次，其他的 数都出现了 k 次，请返回只出现了 1 次的数。
【要求】
时间复杂度为 O(N)，额外空间复杂度为 O(1)。
*/

vector<int> getKSysNumfromNum(int value, int k)
{
	vector<int> res(32, 0);
	int index = 0;
	while (value != 0)
	{
		res[index++] = value % k;
		value = value / k;
	}
	return res;
}

void setExclusiveOr(vector<int>& in, int value, int k)
{
	auto curKSysNum = getKSysNumfromNum(value, k);
	for (int i = 0; i != in.size(); ++i)
	{
		in[i] = (in[i] + curKSysNum[i]) % k;
	}
}

int getNumberFromKSysNum(const vector<int>& in, int k)
{
	int res = 0;
	for (int i = in.size() - 1; i != -1; --i)
		res = res * k + in[i];
	return res;
}



int onceNum(const vector<int>& in, int k)
{
	vector<int> e0(32, 0);
	for (int i : e0)
		setExclusiveOr(e0, in[i], k);
	int res = getNumberFromKSysNum(e0, k);
	return res;
}

int main()
{
	cout << onceNum({3,4,5,7,3,5,4,8,8,8}, 3) << endl;
	return 1;
}

