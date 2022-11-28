#include "node.h"
#include <iostream>

/*
给定二叉树的一个头节点 head，已知其中没有重复值的节点，实现两个函数分别判断这棵 二叉树是否为搜索二叉树和完全二叉树。
*/

using namespace std;


template<typename T>
bool isBST(Node<T> *root)
{
	using NodeT = Node<T>*;
	if(root == nullptr)
	{
		return true;
	}
	NodeT cur = root; 
	NodeT most_right = nullptr;
	NodeT pre = nullptr;
	int i = 0;
	bool res = true;
	while (cur != nullptr && i != 500)
	{
		++i;
		most_right = cur->left;

		if(cur != nullptr)
		{
			most_right = cur->left;
			if (most_right != nullptr) 
			{
				while(most_right->right != nullptr && most_right->right != cur)
				{
					most_right = most_right->right; // find most right
				}
				if(most_right->right == nullptr) // first time 
				{
					most_right->right = cur; 
					cur = cur->left; 
					continue;
				}
				else // second time  
				{
					most_right->right = nullptr; // reset to null
				}
			}
			if (pre != nullptr && pre->value > cur->value) 
			{
				res = false;
			}
			pre = cur;
			cout << cur->value << ","; // print root
			cur = cur->right;
		}
		cout << endl;
	}
	return res;
}

int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});   
    bool ret = isBST(root); 
	cout << ret << endl;

    Node<int> *root2 = new Node<int>({5,3,7,2,-1,6,8});
    
    ret = isBST(root2); 
	cout << ret << endl;

}
