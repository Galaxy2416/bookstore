#include <iostream>
#include <memory>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <assert.h>
#include <unordered_set>

#include <math.h>

/*
对二叉树的节点来说，有本身的值域，有指向左孩子节点和右孩子节点的两个指针；对双
向链表的节点来说，有本身的值域，有指向上一个节点和下一个节点的指针。在结构上，两种
结构有相似性，现在有一棵搜索二叉树，请将其转换为一个有序的双向链表。
例如，节点定义为：
public class Node {
    public int value;
    public Node left;
    public Node right;
    public Node(int data) {
    this.value = data;
}
}
这棵搜索二叉树转换后的双向链表从头到尾依次是 1～9。对每一个节点来说，原来的 right
指针等价于转换后的 next 指针，原来的 left 指针等价于转换后的 last 指针，最后返回转换后的
双向链表头节点。
*/

using namespace std;

template<typename T>
struct Node 
{
    Node(int i)
    :value(i), next(nullptr)
    {
    }
    T value;
    Node<T> *last;
    Node<T> *next;
};

template<typename T>
struct TNode
{
    TNode(int i)
    :value(i), left(nullptr), right(nullptr)
    {
    }
    T value;
    TNode<T> *left;
    TNode<T> *right;

};

template<typename T>
void printList(Node<T> *head)
{
    for(auto c = head; c != nullptr; c = c->next)
    {
        std::cout << c->value << "->";
    }
     std::cout << "\b\b  " << std::endl;
}

template<typename T>
std::pair<Node<T>*, Node<T>*> convertRecrusive(TNode<T> *root)
{
    if(root == nullptr)
    {
        return make_pair(nullptr, nullptr);
    }
    auto lnode = convertRecrusive(root->left);
    auto node = new Node<T>(root->value);
    if(lnode.second)
    {
        node->last = lnode.second;
        lnode.second->next = node;
    }
    auto rnode =  convertRecrusive(root->right);
    if(rnode.first)
    {
        node->next = rnode.first;
        rnode.first->last = node;
    }
    return make_pair(lnode.first == nullptr ? node : lnode.first, rnode.second == nullptr ? node : rnode.second);
}

template<typename T>
Node<T>* convert(TNode<T> *root)
{   if(root == nullptr)
        return nullptr;
    return convertRecrusive(root).first;
}


int main()
{   
    TNode<int> *root = new TNode<int>(6); 
    root->left = new TNode<int>(4);
    root->right = new TNode<int>(7);
    root->left->left = new TNode<int>(2); 
    root->left->right = new TNode<int>(5);                        
    root->right->right = new TNode<int>(9);
    root->left->left->left = new TNode<int>(1);
    root->left->left->right = new TNode<int>(3);
    root->right->right->left = new TNode<int>(8);


    auto l = convert(root);
    printList(l);
    return 0;
}

