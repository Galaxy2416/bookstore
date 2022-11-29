#include "printTree.h"
#include "node.h"
#include <cstdlib>
#include <iostream>
#include <utility>
#include <array>

/*
给定一个有序数组 sortArr，已知其中没有重复值，用这个有序数组生成一棵平衡搜索二叉 树，并且该搜索二叉树中序遍历的结果与 sortArr 一致。
*/

using namespace std;
// return balanced, height

template <typename T, size_t N>
Node<T>* generate(const array<T, N>& arr, int start, int end) 
{
	if (arr.empty() || start > end)
		return nullptr;
	int mid = ( start + end ) / 2;
	// cout << mid << ":" << arr[mid] << ", " << endl;
	Node<T>* head = new Node<T>(arr[mid]);
	head->left = generate(arr, start, mid - 1);
	head->right = generate(arr, mid + 1, end);
	return head;
}

template <typename T, size_t N>
Node<T>* generateTree(const array<T, N>& arr) 
{
	if (arr.empty())
		return nullptr;
	return generate(arr, 0, N - 1);
}


int main()
{
    cout << "start" << endl;
	// std::array<int, 7> arr = {2,1,3,6,5,7,4};
	std::array arr{2,1,3,6,5,7,4};
	std::array arr2{1,3,2,5,7,6};
	
	auto root = generateTree(arr);
	printTree(root);

	root = generateTree(arr2);
	printTree(root);
}
