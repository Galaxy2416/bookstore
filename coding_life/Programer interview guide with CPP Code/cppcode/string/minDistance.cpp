#include <iostream>
#include <limits>
#include <type_traits>
#include <unordered_map>
#include <vector>
using namespace std;

/*
【题目】
给定一个字符串数组 strs，再给定两个字符串 str1 和 str2，返回在 strs 中 str1 与 str2 的最 小距离，如果 str1 或 str2 为 null，或不在 strs 中，返回-1。
【举例】
strs=["1","3","3","3","2","3","1"]，str1="1"，str2="2"，返回 2。 strs=["CD"]，str1="CD"，str2="AB"，返回-1。 进阶问题:如果查询发生的次数有很多，如何把每次查询的时间复杂度降为 O(1)?
*/

int minDistance(const vector<string>& str, const string& str1, const string& str2)
{	
	if (str1.empty() || str2.empty())
		return -1;
	if (str1 == str2)
		return 0;
	int last1 = -1;
	int last2 = -1;
	int min = std::numeric_limits<int>::max();
	for (int i = 0; i != str.size(); ++i)
	{
		if (str[i] == str1)
		{
			min = std::min(min, last2 == -1 ? min : i - last2);
			last1 = i;
		}
		if (str[i] == (str2))
		{
			min = std::min(min, last1 == -1 ? min : i - last1);
			last2 = i;
		}
	}
	return min == std::numeric_limits<int>::max() ? -1 : min;
}

int main()
{
	cout << minDistance({"1", "3", "3", "2", "4", "1"}, "1", "2") << endl;
	return 1;
}

