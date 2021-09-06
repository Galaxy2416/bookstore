#include "node.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>    // std::max

/*
给定一棵二叉树的头节点 head，已知所有节点的值都不一样，返回其中最大的且符合搜索
二叉树条件的最大拓扑结构的大小。
*/

using namespace std;

template <typename T>
int modifyMap(Node<T> *root, int v, std::unordered_map<Node<T>*, std::pair<size_t, size_t>>& _map, bool s) {
    if (root == nullptr || (_map.find(root) == _map.end())) {
        return 0;
    }
    auto& r = _map.at(root);
    if ((s && root->value > v) || ((!s) && root->value < v)) {
        _map.erase(root);
        return r.first + r.second + 1;
    } 
    else 
    {
        // update all the right or left
        int minus = modifyMap<T>(s ? root->right : root->left, v, _map, s);
        if (s) {
            r.second = r.second - minus;
        } else {
            r.first = r.first - minus;
        }
        // _map.emplace(root, r);
        return minus;
    }
}


template <typename T>
size_t postOrder(Node<T> *root , std::unordered_map<Node<T>*, std::pair<size_t, size_t>>& _map)
{
    if (root == nullptr) {
        return 0;
    }
    size_t ls = postOrder(root->left, _map);
    size_t rs = postOrder(root->right, _map);
    modifyMap<T>(root->left, root->value, _map, true);
    modifyMap<T>(root->right, root->value, _map, false);
    auto lr = _map.find(root->left);
    auto rr = _map.find(root->right);
    size_t lbst = lr == _map.end() ? 0 : lr->second.first + lr->second.second + 1;
    size_t rbst = rr == _map.end() ? 0 : rr->second.first + rr->second.second + 1;
    _map.insert(std::make_pair(root, make_pair(lbst, rbst)));
    return max(lbst + rbst + 1, max(ls, rs));
}

template <typename T>
int bstTopoSize2(Node<T> *root)
{
    using NodeP = Node<T>*;
    std::unordered_map<Node<T>*, std::pair<size_t, size_t>> _map;
    return postOrder(root, _map);
}

int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({6,1,12,0,3,10,13,-1,-1,-1,-1,4,14,20,16,2,5,11,15,-1,-1,-1,-1});
    cout << bstTopoSize2(root) << endl;
}