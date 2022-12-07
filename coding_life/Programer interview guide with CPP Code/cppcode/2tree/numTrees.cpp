#include "printTree.h"
#include "node.h"
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
#include <array>
#include <list>

/*
 * 给定一个整数 N，如果 N<1，代表空树结构，否则代表中序遍历的结果为{1,2,3,...，N}。请 返回可能的二叉树结构有多少。
第 3 章 二叉树问题
进阶:N 的含义不变，假设可能的二叉树结构有 M 种，请返回 M 个二叉树的头节点，每一 棵二叉树代表一种可能的结构。
*/

using namespace std;
// return balanced, height

template <typename T, size_t N>
size_t numTrees() 
{
	if (N < 2)
		return 1;
	array<size_t, N+1> num{};
	num[0] = 1;
	for (size_t i = 1; i < N + 1; ++i)
	{
		for (size_t j = 1; j < i + 1; ++j)
			num[i] += num[j - 1] * num [i - j];
	}
	return num[N];
	
}


template <typename T>
Node<T>* cloneTree(Node<T>* head)
{
	using np = Node<T>*;
	if (!head)
		return head;
	np res = new Node<T>(head->value);
	res->left = cloneTree(head->left);
	res->right = cloneTree(head->right);
	return res;
}

template <typename T>
list<Node<T>*> generate(size_t start, size_t end) 
{
	using np = Node<T>*;
	list<np> res{};
	if (start > end)
	{
		res.emplace_back(nullptr);
	}

	np head = nullptr;
	for (size_t i = start; i < end + 1; ++i)
	{
		head = new Node<T>(i);
		list<np> lsub = generate<T>(start, i - 1);
		list<np> rsub = generate<T>(i + 1, end);
		for (auto i : lsub) 
		{
			for (auto j : rsub)
			{
				head->left = i;
				head->right = j;
				// cout << head->value << endl;
				// printTree(head);
				res.push_back(cloneTree(head));
			}
		}
	}
	return res;
}

	

int main()
{
    cout << "start" << endl;
	cout << numTrees<int, 3>() << endl;
	cout << "start2" << endl;
	auto l = generate<int>(1, 5);
	for (auto i : l)
	{
		printTree(i);
	}
}
