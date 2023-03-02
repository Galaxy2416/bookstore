#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;


/*
  matrix = {
    {2,5,6},
    {1,7,4},
    {4,6,7},
    {3,6,5},
    {10,13,2},
    {9,11,3},
    {12,14,4},
    {10,12,5}
    }
*/

/* Return
  {{1,2,4},
    {2,4,6},
    {4,6,7},
    {6,7,4},
    {9,10,3},
    {10,12,5},
    {12,14,4}}
*/

/* 时间复杂度为 O(NlogN)。 */

struct Node
{
	int x; // x 
	bool isAdd; // true add, false delete
	int h;
	Node (int x, bool isAdd, int h) : x(x), isAdd(isAdd), h(h)
	{}
};

ostream& operator<<(ostream& out, const Node& n)
{
	return out << "[" << n.isAdd << ", " << n.x << ", " << n.h << "]";
}

list<list<int>> buildingOutline(const vector<vector<int>>& matrix)
{
	vector<Node> nodes;
	for (auto i : matrix)
	{
		nodes.emplace_back(i[0], true, i[2]);
		nodes.emplace_back(i[1], false, i[2]);
	}

	// cout << nodes[0].h << endl;

	// for (const auto& n : nodes)
	//	cout << n << endl;
	std::sort(nodes.begin(), nodes.end(), [](const Node& l, const Node& r) 
			{
				if (l.x != r.x)
					return l.x < r.x;
				else if (l.isAdd != r.isAdd)
					return l.isAdd ? true : false;
				return false;
			});

	for (const auto& n : nodes)
		cout << n << endl;

	map<int, int> mapHeightTimes;
	map<int, int> mapXvalueHeight;

	for (const Node& n : nodes)
	{
		if (n.isAdd) {
			if (mapHeightTimes.contains(n.h))
				mapHeightTimes[n.h] = 1;
			else
				mapHeightTimes[n.h]++;
		}
		else {
			if (mapHeightTimes[n.h] == 1)
				mapHeightTimes.erase(n.h);
			else
				mapHeightTimes[n.h]--;
		}

		if (mapHeightTimes.empty())
			mapXvalueHeight[n.x] = 0;
		else
			mapXvalueHeight[n.x] = std::prev(mapHeightTimes.end())->first;
	}

	// list<int> : start, end, height
	list<list<int>> res;
	int start = 0;
	int preHeight = 0;
	for (auto [curX, curMaxHeight] : mapXvalueHeight)
	{
		if (preHeight != curMaxHeight) // draw
		{
			if (preHeight != 0) {
				list i {start, curX, preHeight} ;
				res.emplace_back(i);
			}
			start = curX;
			preHeight = curMaxHeight;
		}
	}
	return res;
}

int main()
{
	auto res = buildingOutline({{2,5,6},
    {1,7,4},
    {4,6,7},
    {3,6,5},
    {10,13,2},
    {9,11,3},
    {12,14,4},
    {10,12,5}});

	for (auto l : res)
	{
		for (auto i : l)
			cout << i << ",";
		cout << endl;
	}
	return 1;
}
