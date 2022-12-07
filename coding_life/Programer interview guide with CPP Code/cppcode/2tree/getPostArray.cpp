#include "printTree.h"
#include "node.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <utility>
#include <array>

/*
已知一棵二叉树所有的节点值都不同，给定这棵树正确的先序和中序数组，不要重建整棵
树，而是通过这两个数组直接生成正确的后序数组。
*/

using namespace std;

template <typename T, size_t N>
size_t setPos(const array<T, N>& pre, size_t p_start, size_t p_end,
	  const array<T, N>& in, size_t i_start, size_t i_end,
	  array<T, N>& post, size_t si) 
{
	if (p_start > p_end)
		return si;
	post[si] = pre[p_start];
	size_t i = find(in.begin(), in.end(), pre[p_start]) - in.begin();
	si = setPos(pre, p_start - i_start + i + 1, p_end, in, i + 1, i_end, post, si - 1);
	return setPos(pre, p_start + 1, p_end - i_end + i, in, i_start, i - 1, post, si); 
}

template <typename T, size_t N>
array<T, N> getPostArray(const array<T, N>& pre, const array<T, N>& in) 
{
	if (pre.empty() || in.empty())
		return {};
	array<T, N> post;
	setPos(pre, 0, N-1, in, 0, N-1, post, N-1);
	return post;
}

int main()
{
    cout << "start" << endl;
	// std::array<int, 7> arr = {2,1,3,6,5,7,4};
	std::array arr{1,2,4,5,3,6,7};
	std::array arr2{4,2,5,1,6,3,7};

	auto post = getPostArray(arr, arr2);
	for (const auto& i : post)
		cout << i << endl;
}
