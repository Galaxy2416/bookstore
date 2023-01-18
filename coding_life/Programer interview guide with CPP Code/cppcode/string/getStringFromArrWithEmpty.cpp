#include <iostream>
#include <vector>
using namespace std;

/*
【题目】
给定一个字符串数组 strs[]，在 strs 中有些位置为 null，但在不为 null 的位置上，其字符串 是按照字典顺序由小到大依次出现的。再给定一个字符串 str，请返回 str 在 strs 中出现的最左 的位置。
【举例】
strs=[null,"a",null,"a",null,"b",null,"c"]，str="a"，返回 1。
strs=[null,"a",null,"a",null,"b",null,"c"]，str=null，只要 str 为 null，就返回-1。
strs=[null,"a",null,"a",null,"b",null,"c"]，str="d"，返回-1。
*/


int getIndex(const vector<string>& strs, string str)
{
	if (strs.empty() || str.empty())
		return -1;
	int res = -1;
	int left = 0;
	int right = strs.size() - 1;
	int mid = 0;
	int i = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (!strs[mid].empty() && strs[mid] == str) {
			res = mid;
			right = mid - 1;
		}
		else if (!strs[mid].empty()) {
			if (strs[mid].compare(str) < 0)
				left = mid + 1;
			else 
				right = mid - 1;
		}
		else {
			i = mid;
			while (strs[i].empty() && --i >= left)
				;
			if (i < left || strs[i].compare(str) < 0)
				left = mid + 1;
			else {
				res = strs[i] == str ? i : res;
				right = i - 1;
			}
		}
	}
	return res;
}

int main()
{
	vector<string> in {"123", "456", "789", "aaa", "bbb"};
	cout << getIndex(in, "aaa") << endl;
	return 1;
}

