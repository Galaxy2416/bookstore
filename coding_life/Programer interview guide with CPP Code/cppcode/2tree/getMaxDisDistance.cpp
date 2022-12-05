#include "node.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>    // std::max

/*
 * 从二叉树的节点 A 出发，可以向上或者向下走，但沿途的节点只能经过一次，当到达节点 B 时，路径上的节点数叫作 A 到 B 的距离。
 * 如果二叉树的节点数为 N，时间复杂度要求为 O(N)。
 * 二叉树节点间的最大距离问题
*/

using namespace std;

template <typename T>
std::pair<T, T> process(Node<T>* root) 
{
	using ret = std::pair<T, T>;
	if (!root)
		return {0, 0};
	ret leftdata = process(root->left);
	ret rightdata = process(root->right);
	int height = max(leftdata.first, rightdata.first) + 1;
	int max_distance = max(leftdata.first + rightdata.first + 1, max(leftdata.second, rightdata.second));
	return {height, max_distance};
}


template <typename T>
int getMaxDistance(Node<T> *root)
{
	return process(root).second;
}

int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({1,2,3,4,5,6,7}); // -1 is null
    
    cout << getMaxDistance(root) << endl;
}
