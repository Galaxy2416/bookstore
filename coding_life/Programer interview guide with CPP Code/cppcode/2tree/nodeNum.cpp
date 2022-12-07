#include "node.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>    // std::max

/*
 * 给定一棵完全二叉树的头节点 head，返回这棵树的节点个数。
 * 如果完全二叉树的节点数为 N，请实现时间复杂度低于 O(N)的解法。
*/

using namespace std;

template <typename T>
size_t mostLeftLevel(Node<T>* root, size_t l = 1)
{
	while (root != nullptr) 
	{
		root = root->left;
		l++;
	}
	return l-1;
}


template <typename T>
int bs(Node<T> *root, size_t h)
{
	if (1 == h)
		return 1;
	if (mostLeftLevel(root->right, 2) == h)
	{
		return (1 << (h - 1)) + bs(root->right, h - 1);
	}
	else
	{
		return (1 << (h - 2)) + bs(root->left, h - 1);
	}
	
}


template <typename T>
int bs_book_wrong(Node<T> *root, size_t l, size_t h)
{
	if (l == h)
		return 1;
	if (mostLeftLevel(root->right, l + 1) == h)
	{
		return (1 << (h - 1)) + bs(root->right, l + 1, h);
	}
	else
	{
		return (1 << (h - l -1)) + bs(root->left, l + 1, h);
	}
}

template <typename T>
size_t nodeNum(Node<T>* root)
{
	if (!root)
		return 0;
	return bs(root, mostLeftLevel(root, 1));
	// return bs_book_wrong(root, 1, mostLeftLevel(root, 1));
}

int main()
{
    Node<int> *root = new Node<int>({1,2,3,4,5,6,7,8,9,10}); // -1 is null
    
    cout << nodeNum(root) << endl;

    Node<int> *root2 = new Node<int>({1,2,3,4,5,6,7,8,9,10, 11, 12}); // -1 is null
    cout << nodeNum(root2) << endl;

}
