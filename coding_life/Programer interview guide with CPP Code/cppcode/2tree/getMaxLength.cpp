#include "node.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>    // std::max

/*
给定一棵二叉树的头节点 head 和一个 32 位整数 sum，二叉树节点值类型为整型，求累加
和为 sum 的最长路径长度。路径是指从某个节点往下，每次最多选择一个孩子节点或者不选所
形成的节点链。
*/

using namespace std;

size_t preOrder(Node<int> *root, int k, int pre_sum, size_t level, size_t max_lenth, std::unordered_map<int, size_t>& _map)
{
    if (!root)
    {
        return max_lenth;
    }
    int cur_sum = pre_sum + root->value;
    if (_map.find(cur_sum) == _map.end())
    {
        _map.emplace(cur_sum, level);
    }
    if (_map.find(cur_sum - k) != _map.end())
    {
        max_lenth = max(level - _map[cur_sum - k], max_lenth);
    }
    max_lenth = preOrder(root->left, k, cur_sum, level + 1, max_lenth, _map);
    max_lenth = preOrder(root->right, k, cur_sum, level + 1, max_lenth, _map);
    
    if (level == _map[cur_sum])
        _map.erase (cur_sum);    
    return max_lenth; 
}

int getMaxLength(Node<int> *root, int k)
{
    using NodeP = Node<int>*;
    std::unordered_map<int, size_t> _map;
    _map.emplace(0, 0); // for this first value
    return preOrder(root, k, 0, 1, 0, _map);
}

int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({-3,3,-9,1,0,2,1,-1,-1,1,6}); // -1 is null
    
    cout << getMaxLength(root,6) << endl;
    cout << getMaxLength(root,-9) << endl;
}