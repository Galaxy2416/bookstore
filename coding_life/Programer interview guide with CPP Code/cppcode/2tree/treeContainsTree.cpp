#include "node.h"
#include <iostream>

/*
   给定彼此独立的两棵树头节点分别为 t1 和 t2，判断 t1 树是否包含 t2 树全部的拓扑结构。
*/

using namespace std;

template <typename T>
bool check(Node<T>* h, Node<T>* t2)
{
	if (nullptr == t2)
	{
		return true;
	}
	if (nullptr == h || h->value != t2->value)
	{
		return false;
	}

	return check(h->left, t2->left) && check(h->right, t2->right);
}

template <typename T>
bool contains(Node<T>* t1, Node<T>* t2)
{
	if (nullptr == t2)
	{
		return true;
	}
	if (nullptr == t1)
	{
		return false;
	}
	return check(t1, t2) || check(t1->left, t2) || check(t1->right, t2);
}


int main()
{
    cout << "start" << endl;
    Node<int> *t1 = new Node<int>({1,2,3,4,5,6,7,-1,8,9,-1});
    Node<int> *t2 = new Node<int>({2,4,5,-1,8,9,-1});
    Node<int> *t3 = new Node<int>({2,4,5,-1,9,8,-1});
	assert(contains(t1, t2));
	assert(contains(t1, t3) == false);
}
