#include <iostream>
#include <limits>
#include <vector>

/*
给定一个字符串 str，返回 str 中最长回文子串的长度。
【举例】
str="123"，其中的最长回文子串为"1"、"2"或者"3"，所以返回 1。 str="abc1234321ab"，其中的最长回文子串为"1234321"，所以返回 7。 进阶问题:给定一个字符串 str，想通过添加字符的方式使得 str 整体都变成回文字符串，
但要求只能在 str 的末尾添加字符，请返回在 str 后面添加的最短字符串。
【举例】
str="12"。在末尾添加"1"之后，str 变为"121"，是回文串。在末尾添加"21"之后，str 变为"1221"， 也是回文串。但"1"是所有添加方案中最短的，所以返回"1"。
【要求】
如果 str 的长度为 N，解决原问题和进阶问题的时间复杂度都达到 O(N)。
*/


using namespace std;

string manacherString(const string& str)
{
	string ret;
	for (auto i : str)
	{
		ret += "#";
		ret += i;
	}

	if (!ret.empty())
		ret += "#";

	return ret;
}

int maxLcpsLength(const string& str)
{
	if (str.empty())
		return 0;
	string charArr = manacherString(str);
	vector<int> pArr(charArr.size(), 0);
	int index = -1;
	int pR = -1;
	int max_ = std::numeric_limits<int>::min();
	for (int i = 0; i != charArr.size(); i++) {
		// key point
		pArr[i] = pR > i ? min(pArr[2 * index - i], pR - i) : 1;
		while (i + pArr[i] < charArr.size() && i - pArr[i] > -1) {
			if (charArr[i+pArr[i]] == charArr[i-pArr[i]])
				pArr[i]++;
			else
				break;
		}
		if (i + pArr[i] > pR) {
			pR = i + pArr[i];
			index = i;
		}
		max_ = max (max_, pArr[i]);
	}
	return max_ - 1;
}


string shortestEnd(const string& str)
{
	if (str.empty())
		return 0;
	string charArr = manacherString(str);
	vector<int> pArr(charArr.size(), 0);
	int index = -1;
	int pR = -1;
	int maxContainsEnd = -1;
	for (int i = 0; i != charArr.size(); i++) {
		// key point
		pArr[i] = pR > i ? min(pArr[2 * index - i], pR - i) : 1;
		while (i + pArr[i] < charArr.size() && i - pArr[i] > -1) {
			if (charArr[i+pArr[i]] == charArr[i-pArr[i]])
				pArr[i]++;
			else
				break;
		}
		if (i + pArr[i] > pR) {
			pR = i + pArr[i];
			index = i;
		}

		if (pR == charArr.size()) {
			maxContainsEnd = pArr[i];
			break;
		}
	}

	string res(str.size()-maxContainsEnd+1, 0);
	for (int i = 0; i < res.size(); i++) {
		res[res.size() - 1 - i] = charArr[i * 2 + 1];
	}
	return res;
}

int main()
{
	cout << manacherString("abc") << endl;
	cout << maxLcpsLength("abc1234321ab") << endl;
	cout << shortestEnd("abc1234321ab") << endl;
	cout << shortestEnd("abcd123321") << endl;
	return 1;
}

