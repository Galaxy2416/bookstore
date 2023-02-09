#include <iostream>
#include <vector>

/*
【题目】
给定一个长度为 N 的整型数组 arr，其中有 N 个互不相等的自然数 1~N。请实现 arr 的排 序，但是不要把下标 0~N-1 位置上的数通过直接赋值的方式替换成 1~N。
【要求】
时间复杂度为 O(N)，额外空间复杂度为 O(1)。
*/

using namespace std;
void sort1(vector<int> arr)
{
	int tmp = 0;
	int next = 0;
	for (int i = 0; i != arr.size(); i++)
	{
		tmp = i;
		while (arr[i] != i + 1)
		{
			next = arr[tmp];
			arr[tmp] = i + 1;
			tmp = next;
		}
	}
	for_each(arr.begin(), arr.end(), [](auto i) { cout << i << ", "; } );
	cout << endl;
}


void sort2(vector<int> arr)
{
	int tmp = 0;
	int next = 0;
	for (int i = 0; i != arr.size(); i++)
	{
		while (arr[i] != i + 1)
			swap(arr[i], arr[arr[i] - 1]);
	}
	for_each(arr.begin(), arr.end(), [](auto i) { cout << i << ", "; } );
	cout << endl;
}

int main()
{
	sort1({1,2,5,4,3});
	sort2({1,2,5,4,3});
	return 1;
}
