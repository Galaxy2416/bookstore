#include "node.h"
#include <cstdlib>
#include <iostream>
#include <utility>

/*
 * 平衡二叉树的性质为:要么是一棵空树，要么任何一个节点的左右子树高度差的绝对值不 超过 1。给定一棵二叉树的头节点 head，判断这棵二叉树是否为平衡二叉树。
 * 如果二叉树的节点数为 N，则要求时间复杂度为 O(N)。
*/


using namespace std;

// return balanced, height
template <typename T>
std::pair<bool, int> process(Node<T>* root) 
{
	if (nullptr == root)
		return {true, 0};
	auto left = process(root->left);
	auto right = process(root->right);
	int height = max(get<1>(left), get<1>(right)) + 1;
	bool is_balance = get<0>(left) && get<1>(right) && abs(get<1>(left) - get<1>(right)) < 2;
	return std::make_pair(is_balance, height);
}

template <typename T>
bool isBalanced(Node<T>* root)
{
	return get<0>(process(root));
}

int main()
{
    cout << "start" << endl;
    Node<int> *t1 = new Node<int>({1,2,3,4,5,6,7,-1,8,9,-1});
    Node<int> *t2 = new Node<int>({2,4,5,-1,8,9,-1});
    Node<int> *t3 = new Node<int>({2,-1,5,9,8,-1});
	cout << isBalanced(t1) << "\t" << isBalanced(t2) << "\t" << isBalanced(t3) << endl;
}
