#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
/*
字符串的转换路径问题 
【题目】
给定两个字符串，记为 start 和 to，再给定一个字符串列表 list，list 中一定包含 to，list 中 没有重复字符串。所有的字符串都是小写的。规定 start 每次只能改变一个字符，最终的目标是 彻底变成 to，但是每次变成的新字符串必须在 list 中存在。请返回所有最短的变换路径。
【举例】
start="abc",end="cab",list={"cab","acc","cbc","ccc","cac","cbb","aab","abb"}
  转换路径的方法有很多种，但所有最短的转换路径如下:
    abc -> abb -> aab -> cab
    abc -> abb -> cbb -> cab
	abc -> cbc -> cac -> cab
    abc -> cbc -> cbb -> cab
*/

using namespace std;

vector<string> getNext(const string& str, const unordered_set<string>& dict)
{
	vector<string> res{};
	auto word = str;
	
	for (char cur = 'a'; cur <= 'z'; cur++) 
		for (int i = 0; i != str.size(); ++i) 
		{
			if (word[i] != cur)
			{
				char tmp = word[i];
				word[i] = cur;
				if (dict.contains(word))
					res.push_back(word);
				word[i] = tmp;
			}
		}
	return res;
}

unordered_map<string, vector<string>> getNexts(const vector<string>& words)
{
	unordered_set<string> dict(words.begin(), words.end());
	unordered_map<string, vector<string>>  nexts{};
	for (const auto str : words)
		nexts[str] = getNext(str, dict);
	return nexts;
}

unordered_map<string, int> getDistance(const string& start, const unordered_map<string, vector<string>>& nexts)
{
	unordered_map<string, int> distance{};
	distance[start] = 0;
	queue<string> q{};
	q.push(start);
	unordered_set<string> set{};
	set.insert(start);
	while (!q.empty())
	{
		auto cur = q.front();
		q.pop();
		for (const auto str : nexts.at(cur))
		{
			if (!set.contains(str)) 
			{
				distance[str] = distance[cur] + 1;
				q.push(str);
				set.insert(str);
			}
		}

	}
	return distance;
}

void getShortestPath(const string& start, const string& to, vector<string>& solution,
					const unordered_map<string, vector<string>>& nexts, 
					const unordered_map<string, int>& distance,
					vector<vector<string>>& res)
{
	solution.push_back(start);
	if (to == start)
		res.push_back(solution);
	else
	{
		for (auto str : nexts.at(start))
			if (distance.at(str) == distance.at(start) + 1)
				getShortestPath(str, to, solution, nexts, distance, res);
	}
	solution.pop_back();
}

int main()
{
	vector<string> l {"abc", "cab","acc","cbc","ccc","cac","cbb","aab","abb"};
	auto test1 = getNexts(l);
	for (auto i : test1)
	{
		cout << i.first << " :";
		for_each(i.second.begin(), i.second.end(), [](auto s){ cout << s << ", "; });
		cout << endl;
	}

	auto d = getDistance("abc", test1);
	for_each(d.begin(), d.end(), [](auto p) {cout << p.first << ":" << p.second << endl;});

	vector<vector<string>> res{};
	vector<string> solution{};
	getShortestPath("abc", "cab", solution, test1, d, res);
	for_each(res.begin(), res.end(), [](auto r) { for_each(r.begin(), r.end(), [] (auto s) { cout << s << ", ";}); cout << endl;});

	return 1;
}
