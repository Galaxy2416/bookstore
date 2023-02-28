#include <iostream>
#include <vector>

/*
【题目】
给定一个无序整型数组 arr，找到数组中未出现的最小正整数。
【举例】
arr=[-1,2,3,4]。返回 1。 arr=[1,2,3,4]。返回 5。
*/

/*
原问题。如果 arr 长度为 N，本题的最优解可以做到时间复杂度为 O(N)，额外空间复杂度 为 O(1)。
*/
using namespace std;

int missNum(vector<int> arr) 
{
	int l = 0;
	int r = arr.size();
	while (l < r) {
		if (arr[l] == l + 1) {
			l++;
		} 
		else if (arr[l] <= l || arr[l] > r || arr[arr[l] - 1] == arr[l])
		{ 
			arr[l] = arr[--r];
		} 
		else 
		{
			swap(arr[l], arr[arr[l] - 1]); 
		}
	}
	return l + 1; 
}

int main()
{	
	cout << missNum({-1,2,3,4}) << endl;
	cout << missNum({1,2,3,4}) << endl;
	cout << missNum({1,6,8,4}) << endl;
	cout << missNum({9,10,90,7}) << endl;
	cout << missNum({-1,-2,-3,-4}) << endl;
	return 1;
}
