#include "node.h"
#include <queue>
#include <iostream>

/*
给定二叉树的一个头节点 head，已知其中没有重复值的节点，实现两个函数分别判断这棵 二叉树是否为搜索二叉树和完全二叉树。
*/

using namespace std;


template<typename T>
bool isCBT(Node<T> *root)
{
	using NodeT = Node<T>*;
	if(root == nullptr)
	{
		return true;
	}
	queue<NodeT> q;
	bool leaf = false;
	NodeT l = nullptr; 
	NodeT r = nullptr;

	q.push(root);

	while (!q.empty())
	{
		root = q.front();
		q.pop();
		l = root->left;
		r = root->right;
		if ((leaf && (l!=nullptr || r!=nullptr)) || (l == nullptr && r != nullptr))
			return false;
		if (l != nullptr)
			q.push(l);
		if (r != nullptr)
			q.push(r);
		else
			leaf = true;
	}

	return true;
}

int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({1,2,3,4,5,6});   
    bool ret = isCBT(root); 
	cout << ret << endl;

    Node<int> *root2 = new Node<int>({1,2, -1});
    
    ret = isCBT(root2);
	cout << ret << endl;

}
