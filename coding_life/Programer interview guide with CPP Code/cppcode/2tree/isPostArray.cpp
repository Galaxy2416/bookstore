#include "printTree.h"
#include "node.h"
#include <cstdlib>
#include <iostream>
#include <utility>
#include <array>

/*
给定一个整型数组 arr，已知其中没有重复值，判断 arr 是否可能是节点值类型为整型的搜 索二叉树后序遍历的结果。
进阶问题:如果整型数组 arr 中没有重复值，且已知是一棵搜索二叉树的后序遍历结果， 通过数组 arr 重构二叉树。
*/

using namespace std;
// return balanced, height
template <typename T, size_t N>
bool isPost(const array<T, N>& arr, size_t start, size_t end) 
{
	//for (size_t i = 0; i <= end; ++i)
	//	cout << arr[i] << ", ";
	// cout << endl;
	if (start == end)
		return true;
	int less = -1;
	int more = end + 1;
	for (size_t i = start; i != end; ++i)
	{
		if (arr[end] > arr[i])
			less = i;
		else 
			more = more == end + 1 ? i : more;
	}

	//cout << less << ":" << more << endl;

	if (less == -1 || more == end) 
	{
		return isPost(arr, start, end - 1);
	}

	if (less != more - 1)
	{
		return false;
	}

	return isPost(arr, start, less) && isPost(arr, more, end - 1);
}

template <typename T, size_t N>
bool isPostArray(const array<T, N>& arr)
{
	if (arr.empty())
		return false;
	return isPost(arr, 0, arr.size() - 1);
}

template <typename T, size_t N>
Node<T>* posToBST(const array<T, N>& arr, int start, int end) 
{
	if (start > end)
		return nullptr;
	int less = -1;
	int more = end + 1;
	for (size_t i = start; i != end; ++i)
	{
		if (arr[end] > arr[i])
			less = i;
		else 
			more = more == end + 1? i : more;
	}
	Node<T> *head = new Node<T>(arr[end]);
	head->left = posToBST(arr, start, less);
	head->right = posToBST(arr, more, end - 1);
	return head;
}

template <typename T, size_t N>
Node<T>* posArrayToBST(const array<T, N>& arr) 
{
	if (arr.empty())
		return nullptr;
	return posToBST(arr, 0, arr.size() - 1);
}


int main()
{
    cout << "start" << endl;
	// std::array<int, 7> arr = {2,1,3,6,5,7,4};
	std::array arr{2,1,3,6,5,7,4};
	cout << "isPostArray arr1:" << isPostArray(arr) << endl;

	std::array arr2{1,3,2,5,7,6,4};
	cout << "isPostArray arr2:" << isPostArray(arr2) << endl;
	
	auto root = posArrayToBST(arr2);
	printTree(root);
}
