#include "node.h"
#include <iostream>

/*
二叉树被记录成文件的过程叫作二叉树的序列化，通过文件内容重建原来二叉树的过程叫
作二叉树的反序列化。给定一棵二叉树的头节点 head，已知二叉树节点值的类型为 32 位整型。
请设计一种二叉树序列化和反序列化的方案，并用代码实现。
*/

using namespace std;

/* 先序遍历二叉树 序列化 空值为 #! 其他值为value! */
string serialByPre(Node<int> *root)
{
    if(root == nullptr)
    {
        return "#!";
    }
    string res = to_string(root->value) + "!";
    res += serialByPre(root->left);
    res += serialByPre(root->right);
    return res;
}


vector<string> tokenize(string s, string delimiter = "!")
{
    size_t pos = 0;
    vector<string> tokens{};
    while ((pos = s.find(delimiter)) != std::string::npos) {
        tokens.push_back(s.substr(0, pos));
        // std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }
    return tokens;
}

void preOrderRecur(Node<int> *root)
{
    if(root == nullptr)
    {
        return;
    }
    cout << root->value << ", ";
    preOrderRecur(root->left);
    preOrderRecur(root->right);
}

int main()
{
    Node<int> *root = new Node<int>({12,3,-1,-1,-1});
    preOrderRecur(root); cout << endl;
    auto ser = serialByPre(root);
    // we try to convert it to string version
    Node<string> *roots = new Node<string>(ser);
    preOrderRecur(root);  cout << endl;
}