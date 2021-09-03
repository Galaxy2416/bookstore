#include "node.h"
#include <iostream>

/*
给定一棵二叉树的头节点 head，完成二叉树的先序、中序和后序遍历。如果二叉树的节点
数为 N，则要求时间复杂度为 O(N)，额外空间复杂度为 O(1)。
Morris 遍历的实质就是避免用栈结构，而是让下层到上层有指针，具体是通过让底层节点
指向 null 的空闲指针指回上层的某个节点，从而完成下层到上层的移动。我们知道，二叉树上
的很多节点都有大量的空闲指针，比如，某些节点没有右孩子节点，那么这个节点的 right 指针
就指向 null，我们称为空闲状态，Morris 遍历正是利用了这些空闲指针。

我们先不管先序、中序、后序的概念，先看看 Morris 遍历的过程。
假设当前节点为 cur，初始时 cur 就是整棵树的头节点，根据以下标准让 cur 移动：
1．如果 cur 为 null，则过程停止，否则继续下面的过程。
2．如果 cur 没有左子树，则让 cur 向右移动，即令 cur = cur.right。
3．如果 cur 有左子树，则找到 cur 左子树上最右的节点，记为 mostRight。
1）如果 mostRight 的 right 指针指向 null，则令 mostRight.right = cur，也就是让 mostRight
的 right 指针指向当前节点，然后让 cur 向左移动，即令 cur = cur.left。
2）如果 mostRight 的 right 指针指向 cur，则令 mostRight.right = null，也就是让 mostRight
的 right 指针指向 null，然后让 cur 向右移动，即令 cur = cur.right
*/

using namespace std;

/* 只实现先序遍历二叉树 

根据 Morris 遍历，加工出先序遍历。
1．对于 cur 只能到达一次的节点（无左子树的节点），cur 到达时直接打印。
2．对于 cur 可以到达两次的节点（有左子树的节点），cur 第一次到达时打印，第二次到达
时不打印。

*/
template<typename T>
void morrisPreTree(Node<T> *root)
{
    using NodeT = Node<T>*;
    if(root == nullptr)
    {
        return;
    }
    NodeT cur = root; 
    NodeT most_right = nullptr;
    int i = 0;
    while (cur != nullptr && i != 500)
    {
        ++i;
        most_right = cur->left;

        if(most_right != nullptr)
        {
            while(most_right->right != nullptr && most_right->right != cur)
            {
                most_right = most_right->right; // find most right
            }
            if(most_right->right == nullptr) // first time 
             {
                 most_right->right = cur; 
                 cout << cur->value << ","; // print root
                 cur = cur->left; 
                 continue;
             }
             else // second time  
             {
                 most_right->right = nullptr; // reset to null
             }
        }
        else
        {
            cout << cur->value << ","; // print left or right
        }
        cur = cur->right;

    }
}

int main()
{
    cout << "start" << endl;
    Node<int> *root = new Node<int>({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
    
    morrisPreTree(root); cout << endl;
}