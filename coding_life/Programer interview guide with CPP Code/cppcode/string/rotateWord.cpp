#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
【题目】
给定一个字符类型的数组 chas，请在单词间做逆序调整。只要做到单词的顺序逆序即可， 对空格的位置没有特别要求。
【举例】
如果把 chas 看作字符串为"dog loves pig"，调整成"pig Loves dog"。
如果把 chas 看作字符串为"I’m a student."，调整成"student. a I'm"。 补充问题:给定一个字符类型的数组 chas 和一个整数 size，请把大小为 size 的左半区整体
移到右半区，右半区整体移到左边。
【举例】
如果把 chas 看作字符串为"ABCDE"，size=3，调整成"DEABC"。 【要求】
如果 chas 长度为 N，两道题都要求时间复杂度为 O(N)，额外空间复杂度为 O(1)。
*/

void reverse(string& str, int start, int end)
{
	char tmp = 0;
	while (start < end)
	{
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;
		start++;
		end--;
	}
}

void rotateWord(string& str)
{
	if (str.empty())
		return;
	reverse(str, 0, str.size() - 1);
	cout << str << endl;
	int l = -1;
	int r = -1;
	for (int i = 0; i != str.size(); ++i)
	{
		if (str[i] != ' ') {
			l = i == 0 || str[i-1] == ' ' ? i : l;
			r = i == str.size() - 1 || str[i+1] == ' ' ? i : r;
			//cout << i << l << r << endl;
		}
		if (l != -1 && r != -1)
		{
			reverse(str, l, r);
			l = -1;
			r = -1;
		}
	}
}

void rotate1(string& str, int size)
{
	if (str.empty() || size <= 0 || size >= str.size())
		return ;
	reverse(str, 0, size - 1);
	reverse(str, size, str.size() - 1);
	reverse(str, 0, str.size() - 1);
}


int main()
{
	string in {"dog loves pig"};
	rotateWord(in) ;
	cout << in << endl;
	string in2 {"ABCDE"};
	rotate1(in2, 3);
	cout << in2 << endl;
}
