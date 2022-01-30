#include "node.h"
#include <iostream>

/*
   给定彼此独立的两棵树头节点分别为 t1 和 t2，判断 t1 中是否有与 t2 树拓扑结构完全相同 的子树。
*/


// pre-order -> substr -> KMP
using namespace std;

int getIndexOf(string, string);
int* getNextArray(string);

template <typename T>
bool isSubTree(Node<T>* t1, Node<T>* t2)
{
	string t1Str = serialByPre(t1);
	string t2Str = serialByPre(t2);
	return getIndexOf(t1Str, t2Str) != -1;
}

template <typename T>
string serialByPre(Node<T>* root)
{
	if (nullptr == root)
		return "#!";
	string res = to_string(root->value) + "!";
	res += serialByPre<T>(root->left);
	res += serialByPre<T>(root->right);
	return res;
}

// KMP
int getIndexOf(string s, string m)
{
	if (s.empty() || m.empty() || s.length() < m.length())
		return -1;
	int si = 0;
	int mi = 0;
	int *next = getNextArray(m);
	while (si < s.length() && mi < m.length())
	{
		if (s[si] == m[mi])
		{
			si++;
			mi++;
		}
		else if (next[mi] == -1)
		{
			si++;
		}
		else
		{
			mi = next[mi];
		}
	}
	return mi == m.length() ? si - mi : -1;
}

int* getNextArray(string ms)
{
	if (ms.length() == 1) 
	{
		return new int[1] {-1};
	}
	int *next = new int[ms.length()];
	next[0] = -1;
	next[1] = 0;
	int pos = 2;
	int cn = 0;
	while (pos < ms.length())
	{
		if (ms[pos - 1] == ms[cn])
			next[pos++] = ++cn;
		else if (cn > 0)
			cn = next[cn];
		else
			next[pos++] = 0;
	}
	return next;
}


int main()
{
    cout << "start" << endl;
    Node<int> *t1 = new Node<int>({1,2,3,4,5,6,7,-1,8,9,-1});
    Node<int> *t2 = new Node<int>({2,4,5,-1,8,9,-1});
    Node<int> *t3 = new Node<int>({2,4,5,-1,9,8,-1});
	assert(isSubTree(t1, t2));
	assert(isSubTree(t1, t3) == false);
}
