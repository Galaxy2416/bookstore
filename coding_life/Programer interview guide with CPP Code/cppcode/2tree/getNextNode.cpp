#include "printTree.h"
#include "node.h"
#include <cstdlib>
#include <iostream>
#include <utility>

/*
该结构比普通二叉树节点结构多了一个指向父节点的 parent 指针。假设有一棵 Node 类型 的节点组成的二叉树，树中每个节点的 parent 指针都正确地指向自己的父节点，头节点的 parent 指向 null。只给出一个在二叉树中的某个节点 node，请实现返回 node 的后继节点的函数。在 二叉树的中序遍历的序列中，node 的下一个节点叫作 node 的后继节点。
中序遍历的结果为:1，2，3，4，5，6，7，8，9，10
所以节点 1 的后继为节点 2，节点 2 的后继为节点 3，......，节点 10 的后继为 null
*/

using namespace std;
// return balanced, height

template <typename T>
Node<T>* getLeftMost(Node<T>* node) 
{
	if (node == nullptr)
		return node;
	while (node->left != nullptr) 
	{
		node = node->left;
	}
	return node;
}

template <typename T>
Node<T>* getNextNode(Node<T>* node) 
{
	if (node == nullptr)
		return node;
	// case 1 : has right
	if (node->right != nullptr) 
		return getLeftMost(node->right);
	// case 2 : if left of parent is parent
	// case 3 : find the parent'left is 
	Node<T>* parent = node->parent;
	while (parent != nullptr && parent->left != node) 
	{
		node = parent;
		parent = node->parent;
	}
	return parent;
}



int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({6,3,9,1,4,8,10,-1,2,-1,5,7});
    cout << "start" << endl;
	printTree(root);

	cout << root->right->left->value << endl;
	root = getNextNode(root->right->left);
	printTree(root);
}
