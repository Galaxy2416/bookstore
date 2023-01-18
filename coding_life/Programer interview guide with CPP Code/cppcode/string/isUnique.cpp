#include <iostream>
/*
【题目】
给定一个字符类型数组 chas[]，判断 chas 中是否所有的字符都只出现过一次，请根据以下 不同的两种要求实现两个函数。
【举例】
chas=['a','b','c']，返回 true;chas=['1','2','1']，返回 false。 
【要求】
1.实现时间复杂度为 O(N)的方法。
2.在保证额外空间复杂度为 O(1)的前提下，请实现时间复杂度尽量低的方法。
*/

using namespace std;
bool isUnique1(string str)
{
	if (str.empty())
		return true;
	bool map[256]{false}; 
	for (int i = 0; i != str.size(); ++i) {
		if (map[str[i]])
			return false;
		map[str[i]] = true;
	}
	return true;
}


void heapInsert(string& str, int i)
{
	int parent = 0;
	while (i != 0) 
	{
		parent = (i -1) / 2;
		if (str[parent] < str[i])
		{
			swap(str[parent], str[i]);
			i = parent;
		}
		else 
			break;
	}
}

void heapify(string& str, int i, int size)
{
	int left = i * 2 + 1;
	int right = i * 2 + 2;
	int largest = i;
	while (left < size) 
	{
		if (str[left] > str[i])
			largest = left;
		if (right < size && str[right] > str[largest])
			largest = right;
		if (largest != i)
			swap(str[largest], str[i]);
		else
			break;
		i = largest;
		left = i * 2 + 1;
		right = i * 2 + 2;
	}

}

void heapSort(string& str)
{
	for (int i = 0; i != str.size(); ++i)
		heapInsert(str, i);
	for (int i = str.size() - 1;i > 0; --i) 
	{
		swap(str[0], str[i]);
		heapify(str, 0, i);
	}
}
bool isUnique2(string str)
{
	if(str.empty())
		return true;
	heapSort(str);
	cout << str << endl;
	for (int i = 1; i < str.size(); i++)
		if (str[i] == str[i-1])
			return false;
	return true;
}

int main()
{
	cout << isUnique1("1234567890") << endl;
	cout << isUnique1("12345167890") << endl;
	cout << isUnique2("1234567890") << endl;
	cout << isUnique2("12345167890") << endl;
	return 1;
}

