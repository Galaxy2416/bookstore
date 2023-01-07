#include <iostream>
#include <vector>
/*
【题目】
给定数组 arr，arr[i]==k 代表可以从位置 i 向右跳 1~k 个距离。比如，arr[2]==3，代表可以 从位置 2 跳到位置 3、位置 4 或位置 5。如果从位置 0 出发，返回最少跳几次能跳到 arr 最后的 位置上。
【举例】
arr=[3,2,3,1,1,4]。
arr[0]==3，选择跳到位置 2;arr[2]==3，可以跳到最后的位置。所以返回 2。
【要求】
如果 arr 长度为 N，要求实现时间复杂度为 O(N)、额外空间复杂度为 O(1)的方法。
*/

using namespace std;

int jump(const vector<int>& arr)
{
	int jump = 0, cur = 0, next = 0;
	for (const int i : arr)
	{
		if (cur < i)
		{
			jump++;
			cur = next;
		}
		next = max(next, i+arr[i]);
	}
	return jump;
}


int main()
{
	cout << jump({3,2,3,1,1,4}) << endl;
	return 1;
}
