#include <iostream>
#include <vector>

/*
【题目】
给定字符串 str1 和 str2，求 str1 的子串中含有 str2 所有字符的最小子串长度。
【举例】
str1="abcde"，str2="ac"。因为"abc"包含 str2 所有的字符，并且在满足这一条件的 str1 的所 有子串中，"abc"是最短的，返回 3。
str1="12345"，str2="344"。最小包含子串不存在，返回 0。
*/

using namespace std;
int minLength(const string& str1, const string& str2)
{
	if (str1.empty() || str2.empty() || str1.size() < str2.size())
		return 0;
	vector<int> map(256, 0);
	for (auto i : str2)
		map[i]++;

	int left = 0, right = 0;
	int match = str2.size();
	int minLength = str1.size() + 1;
	while (right != str1.size())
	{
		map[str1[right]]--;
		if (map[str1[right]] >= 0) {
			match--;
		}
		if (match == 0)
		{
			while (map[str1[left]] < 0)
				map[str1[left++]]++;
			minLength = min(minLength, right - left + 1);
			match++;
			map[str1[left++]]++;
		}
		right++;
	}
	return minLength == str1.size() + 1 ? 0 : minLength;
}

int main()
{
	cout << minLength("abcde", "ac") << endl;
	cout << minLength("12345", "344") << endl;
}
