#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>

using namespace std;

/*
【题目】
给定排序数组 arr 和整数 k，不重复打印 arr 中所有相加和为 k 的不降序二元组。 例如，arr=[-8,-4,-3,0,1,2,4,5,8,9]，k=10，打印结果为:
1,9
2,8
补充问题:给定排序数组 arr 和整数 k，不重复打印 arr 中所有相加和为 k 的不降序三元组。 例如，arr=[-8,-4,-3,0,1,2,4,5,8,9]，k=10，打印结果为:
-4,5,9
-3,4,9
-3,5,8 
0,1,9 
0,2,8 
1,4,5
*/

void printUniquePair(const vector<int>& arr, int k)
{
	if (arr.empty())
		return;
	int left = 0;
	int right = arr.size() - 1;
	while (left < right)
	{
		if (arr[left] + arr[right] < k)
			left++;
		else if (arr[left] + arr[right] > k)
			right--;
		else 
		{
			if (left == 0 || arr[left] != arr[left - 1])
				cout << arr[left] << "," << arr[right] << endl;
			left++;
			right--;
		}
	}
}


void printRest(const vector<int>& arr, int left, int right, int k)
{
	int f = left;
	while (left < right)
	{
		if (arr[left] + arr[right] < k)
			left++;
		else if (arr[left] + arr[right] > k)
			right--;
		else 
		{
			if (left == f || arr[left] != arr[left - 1])
				cout << arr[f-1] << "," << arr[left] << "," << arr[right] << endl;
			left++;
			right--;
		}
	}
}

void printUniqueTriad(const vector<int>& arr, int k)
{
	if (arr.empty() || arr.size() < 3)
		return;
	for (int i = 0; i < arr.size() - 2; i++)
		if (i == 0 || arr[i-1] != arr[i])
			printRest(arr, i + 1, arr.size() - 1, k - arr[i]);
}

int main()
{
	printUniquePair({-8,-4,-3,0,1,2,4,5,8,9}, 10);
	printUniqueTriad({-8,-4,-3,0,1,2,4,5,8,9}, 10);
	return 1;
}


