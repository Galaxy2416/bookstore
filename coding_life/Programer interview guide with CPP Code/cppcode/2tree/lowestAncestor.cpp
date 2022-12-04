#include "printTree.h"
#include "node.h"
#include <cstdlib>
#include <iostream>
#include <mach/i386/_structs.h>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <deque>

/*
给定一棵二叉树的头节点 head，以及这棵树中的两个节点 o1 和 o2，请返回 o1 和 o2 的最 近公共祖先节点。
*/

using namespace std;
// return balanced, height

template <typename T>
Node<T>* lowestAncestor(Node<T>* node, T v1, T v2) 
{
	if (node == nullptr || node->value == v1 || node->value == v2)
		return node;
	// case 1 : has right
	
	auto ln = lowestAncestor(node->left, v1, v2);
	auto rn = lowestAncestor(node->right, v1, v2);
	if (ln && rn)
		return node;
	return ln ? ln : rn;
}

/* 进阶问题:如果查询两个节点的最近公共祖先的操作十分频繁，想法让单条查询的查询时
间减少。*/

template <typename T>
struct Record1
{
	unordered_map<Node<T>*, Node<T>*> parent;
	Record1(Node<T>* root) 
	{
		if (root)
			parent.emplace(root, nullptr);
		setMap(root);
	}
	void setMap(Node<T>* root) 
	{
		if (root == nullptr)
		{
			return;
		}
		if (root->left)
		{
			parent.emplace(root->left, root);
		}
		if (root->right)
		{
			parent.emplace(root->right, root);
		}
		setMap(root->left);
		setMap(root->right);
	}

	Node<T>* Query(Node<T>* o1, Node<T>* o2)
	{
		unordered_set<Node<T>*> path;
		while(parent.contains(o1)) {
			path.insert(o1);
			o1 = parent[o1];
		}
		while(!path.contains(o2)) {
			o2 = parent[o2];
		}
		return o2;
	}
};

/*
再进阶问题:给定二叉树的头节点 head，同时给定所有想要进行的查询。二叉树的节点数 量为 N，查询条数为 M，请在时间复杂度为 O(N+M)内返回所有查询的结果。
Tarjan 算法与并查集解决二叉树节点间最近公共祖先的批 量查询问题
*/

template<typename T>
struct Query 
{
	Node<T>* o1;
	Node<T>* o2;

	Query(Node<T> *o1, Node<T> *o2):
		o1(o1), o2(o2)
	{

	}
};

template<typename T>
class UnionFindSet 
{
	using np = Node<T>*;
	public:
		unordered_map<T, np> elementMap; // this is a value -> node poiniter. we assume unique value
		unordered_map<np, np> fatherMap;
		unordered_map<np, size_t> rankMap;

		UnionFindSet(const vector<np> values)
		{
			for (const auto n : values)
			{
				elementMap.emplace(n->value, n);
				fatherMap.emplace(n, n);
				rankMap.emplace(n, 1);
			}
		}

		np FindHead(np p)
		{
			cout << "Find " << p->value << " by " ;
			stack<np> path;
			while (p != fatherMap[p]) 
			{
				path.push(p);
				p = fatherMap[p];
			}

			while(!path.empty()) 
			{
				fatherMap[path.top()] = p;
				path.pop();
			}
			cout << p->value << endl;
			return p;
		}
		
		np FindHead(T v)
		{
			return elementMap.contains(v) ? FindHead(elementMap[v]) : nullptr;
		}

		bool isSameSet(T a, T b)
		{
			if (elementMap.contains(a) && elementMap.contains(b)) 
			{
				return FindHead(elementMap[a]) == FindHead(elementMap[b]);
			}
			return false;
		}

		void Union(T a, T b)
		{

			if (elementMap.contains(a) && elementMap.contains(b)) 
			{
				np aF = FindHead(elementMap[a]);
				np bF = FindHead(elementMap[b]);
				if (aF != bF)
				{
					np big = rankMap[aF] >= rankMap[bF] ? aF : bF;
					np small = big == aF ? bF : aF;
					fatherMap[small] =  big;
					rankMap[big] += rankMap[small];
					rankMap.erase(small);
				}
			}
		}
};


template<typename T>
void process(Node<T>* root, vector<Node<T>*>& v) 
{
	if (root == nullptr)
		return;
	v.emplace_back(root);
	process(root->left, v);
	process(root->right, v);

}
template<typename T>
vector<Node<T>*> getAllNodes(Node<T>* root) 
{
	using np = Node<T>*;
	vector<np> v;
	process(root, v);
	return v;
}

template<typename T>
void setQueriesAndEasyAnswers (const vector<Query<T>>& ques, vector<Node<T>*>& ans, 
							   unordered_map<Node<T>*, deque<Node<T>*>>& queryMap,
							   unordered_map<Node<T>*, deque<size_t>>& indexMap) 
{
	using np = Node<T>*;
	np o1 = nullptr;
	np o2 = nullptr;
	for (size_t i = 0; i != ques.size(); ++i)
	{
		o1 = ques[i].o1;
		o2 = ques[i].o2;
		if (o1 == o2 || !o1 || !o2 )
		{
			ans[i] = o1 != nullptr ? o1 : o2;
		}
		else 
		{
			if (!queryMap.contains(o1)) 
			{
				queryMap.emplace(o1, deque<np>{});
				indexMap.emplace(o1, deque<size_t>{});
			}
			if (!queryMap.contains(o2)) 
			{
				queryMap.emplace(o2, deque<np>{});
				indexMap.emplace(o2, deque<size_t>{});
			}
			queryMap[o1].push_back(o2);
			queryMap[o2].push_back(o1);
			indexMap[o2].push_back(i);
			indexMap[o1].push_back(i);
		}

	}
}


template<typename T>
void setAnswers(Node<T>* root, vector<Node<T>*>& ans, 
		unordered_map<Node<T>*, deque<Node<T>*>>& queryMap,
		unordered_map<Node<T>*, deque<size_t>>& indexMap,
		unordered_map<Node<T>*, Node<T>*>& ancestorMap,
		UnionFindSet<T>& sets)
{

	using np = Node<T>*;
	if (!root)
		return ;

	setAnswers(root->left, ans, queryMap, indexMap, ancestorMap, sets);
	if (root->left)
		sets.Union(root->left->value, root->value);
	ancestorMap[sets.FindHead(root->value)] = root;
	setAnswers(root->right, ans, queryMap, indexMap, ancestorMap, sets);
	if (root->right)
		sets.Union(root->right->value, root->value);
	ancestorMap[sets.FindHead(root->value)] = root;

	auto& nlist = queryMap[root];
	auto& ilist = indexMap[root];

	np node = nullptr;
	np node_father = nullptr;
	size_t index = 0;
	while (!nlist.empty()) 
	{
		node = nlist.front();
		index = ilist.front();
		nlist.pop_front();
		ilist.pop_front();
		node_father = sets.FindHead(node->value);
		if (ancestorMap.contains(node_father))
			ans[index] = ancestorMap[node_father];

	}

	cout << "looping:" << endl;
	cout << "ancestor map:" << endl;
	for (const auto& [k, v] : ancestorMap) {
		cout << k->value << ":" << k->value << endl;
	}

	cout << "looping end" << endl;


}

template<typename T>
vector<Node<T>*> tarJanQuery(Node<T>* root, vector<Query<T>> v)
{
	using np = Node<T>*;
	unordered_map<np, deque<np>> queryMap;
	unordered_map<np, deque<size_t>> indexMap;
	unordered_map<np, np> ancestorMap;

	UnionFindSet sets(getAllNodes(root));
	vector<np> ans(v.size(), 0);
	setQueriesAndEasyAnswers(v, ans, queryMap, indexMap);
	
	cout << "query input:" << endl;
	for (const auto& i : v)
		cout << i.o1->value << ":" << i.o2->value << endl;
	
	cout << "index map:" << endl;
	for (const auto& [k, v] : indexMap) {
		cout << "key" << ":" << k->value << endl;
		for (const auto& n : v)
			cout << "nodes index" << ":" << n << endl;
	}

	cout << "query map:" << endl;
	for (const auto& [k, v] : queryMap) {
		cout << "key" << ":" << k->value << endl;
		for (const auto& n : v)
			cout << "nodes value" << ":" << n->value << endl;
	}



	setAnswers(root, ans, queryMap, indexMap, ancestorMap, sets);
	return ans;
}

int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({1,2,3,4,5,6,7,-1,-1,-1, -1, -1, -1, 8});
	printTree(root);
	auto root2 = lowestAncestor(root, 6, 8);
	printTree(root2);

	auto r = Record1(root);
	auto l6 = root->right->left;
	auto l8 = root->right->right->left;
    cout << "start2" << l6->value << l8->value << endl;
	root2 = r.Query(l6, l8);
	printTree(root2);

    cout << "start3" << l6->value << l8->value << endl;
	vector<Query<int>> ques { {l6, l8} };
	auto res = tarJanQuery(root, ques);
	for (const auto& i : res)
		printTree(i);
		// cout << i->value << endl;
}
