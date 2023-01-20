#include <iostream>
using namespace std;

/*
【题目】
给定一个全是小写字母的字符串 str，删除多余字符，使得每种字符只保留一个，并让最终 结果字符串的字典序最小。
【举例】
str = "acbc"，删掉第一个'c'，得到"abc"，是所有结果字符串中字典序最小的。
str = "dbcacbca"，删掉第一个'b'、第一个'c'、第二个'c'、第二个'a'，得到"dabc"，是所有结 果字符串中字典序最小的。
*/

string removeDuplicateLetters(string str)
{
	int map[26] {0};
	for (char c : str)
		map[c - 'a']++;
	string res;
	int index = 0;
	int L = 0;
	int R = 0;
	while (R != str.size())
	{
		if (map[str[R] - 'a'] == -1 || --map[str[R] - 'a'] > 0)
			R++;
		else
		{
			int pick = -1;
			for (int i = L; i <= R; i++) {
				//cout << str[i] << map[str[i] - 'a'] << i << endl;
				if (map[str[i] - 'a'] != -1 && (pick == -1 || str[i] < str[pick]))
					pick = i;
			}
			res += str[pick];
			
			for (int i = pick + 1; i <= R; i++) {
				if (map[str[i] - 'a'] != -1) {
					map[str[i] - 'a']++;
				}
			}

			map[str[pick] - 'a'] = -1;
			L = pick + 1;
			R = L;
		}
	}
	return res;
}

int main()
{
	cout << removeDuplicateLetters("dbcacbca") << endl;
	return 1;
}
