#include <iostream>
#include <vector>
using namespace std;

/*
【题目】
给定两个字符串 str 和 match，长度分别为 N 和 M。实现一个算法，如果字符串 str 中含有 子串 match，则返回 match 在 str 中的开始位置，不含有则返回-1。
【举例】
str="acbc"，match="bc"，返回 2。 str="acbc"，match="bcc"，返回-1。
【要求】
如果 match 的长度大于 str 的长度(M>N)，str 必然不会含有 match，可直接返回-1。但如 果 N≥M，要求算法复杂度为 O(N)。
 */

vector<int> getNextArray(string ms)
{
	vector<int> next(ms.length());
	next[0] = -1;
	next[1] = 0;
	size_t pos = 2; // current position
	size_t cn =  0; // last pos of max match from head from pos 
	while (pos < ms.length())
	{
		if (ms[pos - 1] == ms[cn]) 
			next[pos++]  = ++cn;
		else if (cn > 0)
			cn = next[cn];
		else
			next[pos++] = 0; 
	}
	for ( auto i : next)
		cout << i << " ,";
	cout << endl;
	return next;
}

int getIndexOf(string s, string m)
{
	if (m.empty() || m.length() > s.length())
		return -1;
	size_t si = 0;
	size_t mi = 0;
	auto next = getNextArray(m);
	while (si < s.length() && mi < m.length())
	{
		if (s[si] == m[mi])
		{
			si++;mi++;
		}
		else if (next[mi] == -1)
		{
			si++;
		}
		else
		{
			mi = next[mi];
		}
	}
	return mi == m.length() ? si - mi : -1;
}

int main()
{
	cout << getIndexOf("acbc", "bc") << endl;
	cout << getIndexOf("acbc", "bcc") << endl;
	cout << getIndexOf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bccfsfgslfhjesdfhdsudasd") << endl;
	cout << getIndexOf("jintiandetaiyangshizaishitaiyuanle", "taiyang") << endl;
	return 1;
}
