#include <iostream>

/*
【题目】
给定一个没有重复值的整型数组 arr，初始时认为 arr 中每一个数各自都是一个单独的集合。 请设计一种叫 UnionFind 的结构，并提供以下两个操作。
1)boolean isSameSet(int a, int b):查询 a 和 b 这两个数是否属于一个集合。
2)void union(int a, int b):把 a 所在的集合与 b 所在的集合合并在一起，原本两个集合各自 的元素以后都算作同一个集合。
【要求】
如果调用 isSameSet 和 union 的总次数逼近或超过 O(N)，请做到单次调用 isSameSet 或 union 方法的平均时间复杂度为 O(1)。
*/

/*
符合题目功能和要求的结构就是并查集结构。并查集结构由Bernard A. Galler和Michael J. Fischer 在 1964 年发明，但证明时间复杂度的工作却持续了数年之久，直到 1989 才彻底证明完 毕。有兴趣的读者请阅读《算法导论》一书了解整个证明过程
*/

#include <unordered_map>
#include <vector>
#include<stack>

using namespace std;

template <typename T>
struct Element
{
	T value;
	Element(T v) : value(v) {}
};

template <typename T>
class UnionFindSet
{
	unordered_map<T, Element<T>*> elementMap;
	unordered_map<Element<T>*, Element<T>*> fatherMap;
	unordered_map<Element<T>*, int> rankMap;

	public :
	UnionFindSet(const vector<T>& arr)
	{
		for (auto i : arr)
		{
			Element<T>* et = new Element<T>(i);
			elementMap[i] = et;
			fatherMap[et] = et;
			rankMap[et] = 1;
			
		}
	}

	Element<T>* findHead(Element<T>* v)
	{
		stack<Element<T>*> path;
		while (v != fatherMap[v]) {
			path.push(v);
			v = fatherMap[v];
		}

		while (!path.empty()) {
			fatherMap[path.top()] = v;
			path.pop();
		}

		return v;
	}

	bool isSameSet(T a, T b)
	{
		if (elementMap.contains(a) && elementMap.contains(b)) {
			return findHead(elementMap[a]) == findHead(elementMap[b]);
		}
		return false;
	}

	void union_(T a, T b)
	{
		if (elementMap.contains(a) && elementMap.contains(b)) {
			auto aF = findHead(elementMap[a]);
			auto bF = findHead(elementMap[b]);
			if (aF != bF)
			{
				auto big = rankMap[aF] >= rankMap[bF] ? aF : bF;
				auto small = big == aF ? bF : aF;
				fatherMap[small] = big;
				rankMap[big] = rankMap[big] + rankMap[small];
				rankMap.erase(small);
			}
		}
	}
};

int main()
{
	UnionFindSet<char> us({'a', 'b', 'c', 'd', 'e'});
	cout << us.isSameSet('a', 'b') << endl;
	us.union_('a', 'b');
	cout << us.isSameSet('a', 'b') << endl;
	return 1;
}
