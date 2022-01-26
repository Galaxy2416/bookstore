#include "node.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>    // std::max
#include <limits>
#include <array>

/*
一棵二叉树原本是搜索二叉树，但是其中有两个节点调换了位置，使得这棵二叉树不再是 搜索二叉树，请找到这两个错误节点并返回。已知二叉树中所有节点的值都不一样，给定二叉 树的头节点 head，返回一个长度为 2 的二叉树节点类型的数组 errs，errs[0]表示一个错误节点， errs[1]表示另一个错误节点。
 
进阶问题:如果在原问题中得到了这两个错误节点，我们当然可以通过交换两个节点的节
点值的方式让整棵二叉树重新成为搜索二叉树。但现在要求你不能这么做，而是在结构上完全
交换两个节点的位置，请实现调整的函数。
*/

using namespace std;

template <typename T>
void inOrderPrint(Node<T>* root)
{
	if (nullptr == root)
		return;
	inOrderPrint(root->left);
	cout << root->value << ",";
	inOrderPrint(root->right);
}

template <typename T>
Node<T>* inOrderSwitch(Node<T>* root, Node<T>* p, vector<pair<Node<T>*,Node<T>*>>& v)
{
	if (nullptr == root)
		return nullptr;
	auto pl = inOrderSwitch(root->left, p, v);
	p = pl != nullptr ? pl : p; 
	if (p && p->value > root->value) 
		v.emplace_back(p, root);
	inOrderSwitch(root->right, root, v);
	return root;
}

template <typename T>
void inOrderSwitch1(Node<T>* root)
{
	vector<pair<Node<T>*,Node<T>*>> v;
	inOrderSwitch(root, static_cast<Node<T>*>(nullptr), v);
	assert(v.size() <= 2);
	// first is larger / second is less
	if (v.size() == 1)
	{
		cout << "1:" << endl;
		swap(v[0].first->value, v[0].second->value);
	}
	if (v.size() == 2)
	{
		cout << "2:" << endl;
		swap(v[0].first->value, v[1].second->value);
	}
	inOrderPrint(root);
	cout << endl;
	delete root;
}

template <typename T>
void inOrderSwitchStack(Node<T>* root)
{

	auto r = root;

	if (nullptr == root)
		return;
	using nt = Node<T>*;
	nt errs[2] = { static_cast<nt>(nullptr), static_cast<nt>(nullptr)};
	stack<nt> s;
	nt pre = nullptr;

	while(!s.empty() || root != nullptr)
	{
		if(root)
		{
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top();
			if (pre && pre->value > root->value)
			{
				errs[0] = errs[0] == nullptr ? pre : errs[0];
				errs[1] = root;
			}
			pre = root;
			root = root->right;
			s.pop();
		}
	}

	if (errs[0] && errs[1])
		swap(errs[0]->value, errs[1]->value);
	inOrderPrint(r);
	cout << endl;
	delete r;
}


// advance qs
template <typename T>
array<Node<T>*, 2> getTwoErrNodes(Node<T>* root)
{

	using nt = Node<T>*;
	auto r = root;

	array<nt, 2> errs = { static_cast<nt>(nullptr), static_cast<nt>(nullptr)};
	if (nullptr == root)
		return errs;
	stack<nt> s;
	nt pre = nullptr;

	while(!s.empty() || root != nullptr)
	{
		if(root)
		{
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top();
			if (pre && pre->value > root->value)
			{
				errs[0] = errs[0] == nullptr ? pre : errs[0];
				errs[1] = root;
			}
			pre = root;
			root = root->right;
			s.pop();
		}
	}
	return errs;
//	if (errs[0] && errs[1])
//		swap(errs[0]->value, errs[1]->value);
//	inOrderPrint(r);
//	cout << endl;
//	delete r;
}

template <typename T>
array<Node<T>*, 2> getTwoErrParents(Node<T>* root, Node<T>* e1, Node<T>* e2)
{
	using nt = Node<T>*;
	auto r = root;


	array<nt, 2> parents = { static_cast<nt>(nullptr), static_cast<nt>(nullptr)};
	if (nullptr == root)
		return parents;
	stack<nt> s;

	while(!s.empty() || root != nullptr)
	{
		if(root)
		{
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top(); s.pop();
			if (root->left == e1 || root->right == e1)
				parents[0] = root;
			if (root->left == e2 || root->right == e2)
				parents[1] = root;
			root = root->right;
		}
	}
	return parents;
}

/*

问题一:e1 和 e2 是否有一个是头节点?如果有，谁是头节点?
问题二:e1 和 e2 是否相邻?如果相邻，谁是谁的父节点?
问题三:e1 和 e2 分别是各自父节点的左孩子节点还是右孩子节点? 特别注意:因为是在中序遍历时先找到e1，后找到e2，所以e1一定不是e2的右孩子节点，
e2 也一定不是 e1 的左孩子节点。
1.e1 是头节点，e1 是 e2 的父节点，此时 e2 只可能是 e1 的右孩子节点。 2.e1 是头节点，e1 不是 e2 的父节点，e2 是 e2P 的左孩子节点。
3.e1 是头节点，e1 不是 e2 的父节点，e2 是 e2P 的右孩子节点。
4.e2 是头节点，e2 是 e1 的父节点，此时 e1 只可能是 e2 的左孩子节点。
5.e2 是头节点，e2 不是 e1 的父节点，e1 是 e1P 的左孩子节点。
6.e2 是头节点，e2 不是 e1 的父节点，e1 是 e1P 的右孩子节点。
7.e1 和 e2 都不是头节点，e1 是 e2 的父节点，此时 e2 只可能是 e1 的右孩子节点，e1 是
e1P 的左孩子节点
8.e1 和 e2 都不是头节点，e1 是 e2 的父节点，此时 e2 只可能是 e1 的右孩子节点，e1 是 e1P 的右孩子节点。
9.e1 和 e2 都不是头节点，e2 是 e1 的父节点，此时 e1 只可能是 e2 的左孩子节点，e2 是 e2P 的左孩子节点。
10.e1 和 e2 都不是头节点，e2 是 e1 的父节点，此时 e1 只可能是 e2 的左孩子节点，e2 是 e2P 的右孩子节点。
11.e1 和 e2 都不是头节点，谁也不是谁的父节点，e1 是 e1P 的左孩子节点，e2 是 e2P 的左 孩子节点。
12.e1 和 e2 都不是头节点，谁也不是谁的父节点，e1 是 e1P 的左孩子节点，e2 是 e2P 的右 孩子节点。
13.e1 和 e2 都不是头节点，谁也不是谁的父节点，e1 是 e1P 的右孩子节点，e2 是 e2P 的左 孩子节点。 14.e1 和 e2 都不是头节点，谁也不是谁的父节点，e1 是 e1P 的右孩子节点，e2 是 e2P 的右 孩子节点。 */

template <typename T>
void recoverTree(Node<T>* root)
{
	using nt = Node<T>*;
	auto errs = getTwoErrNodes(root);
	auto parents = getTwoErrParents(root, errs[0], errs[1]);
	nt e1 = errs[0];
	nt e1P = parents[0];
	nt e1L = e1->left;
	nt e1R = e1->right;
	nt e2 = errs[1];
	nt e2P = parents[1];
	nt e2L = e2->left;
	nt e2R = e2->right;

	cout << e1->value << e2->value << endl;
	// cout << e1P->value << e2P->value << endl;


	if (e1 == root)
	{
		if (e1 == e2P) // case 1
		{
			e1->left = e2L;
			e1->right = e2R;
			e2->right = e1;
			e2->left = e1L;
		}
		else if (e2P->left == e2) // case 2
		{
			e2P->left = e1;
			e2->left = e1L;
			e2->right = e1R;
			e1->left = e2L;
			e1->right = e2R;

		}
		else // case 3 
		{
			e2P->right = e1;
			e2->left = e1L;
			e2->right = e1R;
			e1->left = e2L; 
			e1->right = e2R;
		}
		root = e2;
	}
	else if (e2 == root)
	{
		if (e2 == e1P) // case 4
		{
			e2->left = e1L;
			e2->right = e1R;
			e1->left = e2;
			e1->right = e2R;
		}
		else if (e1P->left == e1) // case 5
		{
			e1P->left = e2;
			e1->left = e2L;
			e1->right = e2R;
			e2->left = e1L;
			e2->right = e1R;
		}
		else // case 6
		{
			e1P->right = e2;
			e1->left = e2L;
			e1->right = e2R;
			e2->left = e1L;
			e2->right = e1R;
		}
		root = e1;
	}
	else
	{
		if (e1 == e2P)
		{
			if (e1P->left == e1) // case 7
			{
				e1P->left = e2;
				e1->left = e2L;
				e1->right = e2R;
				e2->left = e1L;
				e2->right = e1;
			}
			else // case 8
			{
				e1P->right = e2;
				e1->left = e2L;
				e1->right = e2R;
				e2->left = e1L;
				e2->right = e1;
			}
		}
		else if (e2 == e1P)
		{
			if (e2P->left == e2) // case 9
			{
				e2P->left = e1;
				e2->left = e1L;
				e2->right = e1R;
				e1->left = e2;
				e1->right = e2R;
			}
			else // case 10
			{
				e2P->right = e1;
				e2->left = e1L;
				e2->right = e1R;
				e1->left = e2;
				e1->right = e2R;
			}
		}
		else
		{
			if (e1P->left == e1) 
			{
				if (e2P->left == e2) // case 11
				{
					e1->left = e2L;
					e1->right = e2R;
					e2->left = e1L;
					e2->right = e1R;
					e1P->left = e2;
					e2P->left = e1;
				} 
				else  // case 12 
				{
					e1->left = e2L;
					e1->right = e2R;
					e2->left = e1L;
					e2->right = e1R;
					e1P->left = e2;
					e2P->right = e1;
				}
			}
			else
			{
				if (e2P->left == e2) // case 13
				{
					e1->left = e2L;
					e1->right = e2R;
					e2->left = e1L;
					e2->right = e1R;
					e1P->right = e2;
					e2P->left = e1;
				}
				else // case 14
				{
					e1->left = e2L;
					e1->right = e2R;
					e2->left = e1L;
					e2->right = e1R;
					e1P->right = e2;
					e2P->right = e1;
				}
			}
		}
	}

	inOrderPrint(root); cout << endl;
}


int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({2,1,4,-1,-1,3,5}); // normal 12345
	inOrderPrint(root);
	cout << endl;

    inOrderSwitch1(new Node<int>({2,5,4,-1,-1,3,1}));
    inOrderSwitch1(new Node<int>({4,1,2,-1,-1,3,5}));
    inOrderSwitch1(new Node<int>({1,2,4,-1,-1,3,5}));
    inOrderSwitch1(new Node<int>({2,3,4,-1,-1,1,5}));

    cout << "start stack" << endl;
    recoverTree(new Node<int>({2,5,4,-1,-1,3,1}));
    recoverTree(new Node<int>({4,1,2,-1,-1,3,5}));
    recoverTree(new Node<int>({1,2,4,-1,-1,3,5}));
    recoverTree(new Node<int>({2,3,4,-1,-1,1,5}));
}
