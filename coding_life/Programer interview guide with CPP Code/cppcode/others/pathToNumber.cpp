#include <iostream>
#include <vector>

using namespace std;

/*
给定一个路径数组 paths，表示一张图。paths[i]==j 代表城市 i 连向城市 j，如果 paths[i]==i， 则表示 i 城市是首都，一张图里只会有一个首都且图中除首都指向自己之外不会有环。例如， paths=[9,1,4,9,0,4,8,9,0,1]，

由数组表示的图可以知道，城市 1 是首都，所以距离为 0，离首都距离为 1 的城市只有城 市 9，离首都距离为 2 的城市有城市 0、3 和 7，离首都距离为 3 的城市有城市 4 和 8，离首都 距离为 4 的城市有城市 2、5 和 6。所以距离为 0 的城市有 1 座，距离为 1 的城市有 1 座，距离 为 2 的城市有 3 座，距离为 3 的城市有 2 座，距离为 4 的城市有 3 座。那么统计数组为

nums=[1,1,3,2,3,0,0,0,0,0]，nums[i]==j 代表距离为 i 的城市有 j 座。要求实现一个 void 类型的函 数，输入一个路径数组 paths，直接在原数组上调整，使之变为 nums 数组，即 paths=[9,1,4,9,0,4,8,9,0,1]经过这个函数处理后变成[1,1,3,2,3,0,0,0,0,0]。

*/

/*
【要求】
如果 paths 长度为 N，请达到时间复杂度为 O(N)，额外空间复杂度为 O(1)。
*/

using namespace std;

void pathsToDistans(vector<int>& paths)
{
	int cap = 0;
	for (int i = 0; i != paths.size(); ++i)
	{
		if (paths[i] == i)
			cap = i;
		else if (paths[i] > -1) {
			int curI = paths[i];
			paths[i] = -1;
			int preI = i;
			while (paths[curI] != curI) {
				if (paths[curI] > -1) {
					int nextI = paths[curI];
					paths[curI] = preI;
					preI = curI;
					curI = nextI;
				}
				else
					break;
			}
			int value = paths[curI] == curI ? 0 : paths[curI];
			while (paths[preI] != -1) {
				curI = paths[preI]; // use curI as tmp
				paths[preI] = --value;
				preI = curI;
			}
			paths[preI] = --value;
		}
	}
	paths[cap] = 0;

	for (auto i : paths)
		cout << i << ", ";
	cout << endl;
}

void distansToNums(vector<int>& arr)
{
	for (int i = 0; i != arr.size(); ++i)
	{
		int index = arr[i];
		if (index < 0)
		{
			arr[i] = 0; // very important 
			while (true)
			{
				index = -index;
				if (arr[index] < 0)
				{
					int in = arr[index];
					arr[index] = 1;
					index = in; 
				}
				else 
				{
					arr[index]++;
					break;
				}
			}
		}
	}
	arr[0] = 1;

	for (auto i : arr)
		cout << i << ", ";
	cout << endl;
}


int main()
{
	vector<int> in {9,1,4,9,0,4,8,9,0,1};
	pathsToDistans(in);
	distansToNums(in);
	return 1;
}
