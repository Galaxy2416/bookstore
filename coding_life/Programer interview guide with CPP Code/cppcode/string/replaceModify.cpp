#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
【题目】
给定一个字符类型的数组 chas[]，chas 右半区全是空字符，左半区不含有空字符。现在想 将左半区中所有的空格字符替换成"%20"，假设 chas 右半区足够大，可以满足替换所需要的空 间，请完成替换函数。
【举例】
如果把chas的左半区看作字符串，为"a b c"，假设chas的右半区足够大。替换后，chas 的左半区为"a%20b%20%20c"。
【要求】
替换函数的时间复杂度为 O(N)，额外空间复杂度为 O(1)。
补充问题:给定一个字符类型的数组 chas[]，其中只含有数字字符和“*”字符。现在想把 所有的“*”字符挪到 chas 的左边，数字字符挪到 chas 的右边。请完成调整函数

【举例】
如果把 chas 看作字符串，为"12**345"。调整后 chas 为"**12345"。
【要求】
1.调整函数的时间复杂度为 O(N)，额外空间复杂度为 O(1)。 2.不得改变数字字符从左到右出现的顺序。
*/


void replace(string& str)
{
	if (str.empty())
		return;
	int num = 0;
	int len = 0;
	for (len = 0; len < str.size() && str[len] != 0; len++)
		if (str[len] == ' ')
			num++;
	int j = len + num * 2 - 1;
	for (int i = len - 1; i > -1; i--)
	{
		if (str[i] != ' ') {
			str[j--] = str[i];
		} 
		else {
			str[j--] = '0';
			str[j--] = '2';
			str[j--] = '%';
		}
	}
}


void modify(string& str)
{
	if (str.empty())
		return;
	int j = str.size() - 1;
	for (int i = str.size() - 1; i > -1; i--)
	{
		if (str[i] != '*') {
			str[j--] = str[i];
		} 
	}
	while (j > -1)
		str[j--] = '*';
}

int main()
{
	string in{"a b  c"};
	in.append(50, 0);
	cout << in << endl;
	replace(in);
	cout << in << endl;
	string in2{"1*2*5**344234"};
	cout << in2 << endl;
	modify(in2);
	cout << in2 << endl;
	return 1;
}
