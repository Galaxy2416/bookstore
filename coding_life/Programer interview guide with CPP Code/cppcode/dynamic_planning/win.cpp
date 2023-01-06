#include <iostream>
#include <vector>
using namespace std;

/*
【题目】
给定一个整型数组 arr，代表数值不同的纸牌排成一条线。玩家 A 和玩家 B 依次拿走每张纸 牌，规定玩家 A 先拿，玩家 B 后拿，但是每个玩家每次只能拿走最左或最右的纸牌，玩家 A 和 玩家 B 都绝顶聪明。请返回最后获胜者的分数。
【举例】
arr=[1,2,100,4]。
开始时，玩家 A 只能拿走 1 或 4。如果玩家 A 拿走 1，则排列变为[2,100,4]，接下来玩家 B 可以拿走 2 或 4，然后继续轮到玩家 A。如果开始时玩家 A 拿走 4，则排列变为[1,2,100]，接下 来玩家 B 可以拿走 1 或 100，然后继续轮到玩家 A。玩家 A 作为绝顶聪明的人不会先拿 4，因为 拿 4 之后，玩家 B 将拿走 100。所以玩家 A 会先拿 1，让排列变为[2,100,4]，接下来玩家 B 不管 怎么选，100 都会被玩家 A 拿走。玩家 A 会获胜，分数为 101。所以返回 101。
arr=[1,100,2]。
开始时，玩家 A 不管拿 1 还是 2，玩家 B 作为绝顶聪明的人，都会把 100 拿走。玩家 B 会 获胜，分数为 100。所以返回 100。
*/


int s(const vector<int>& arr, int i, int j);
int f(const vector<int>& arr, int i, int j)
{
	if (i == j)
		return arr[i];
	return max(arr[i] + s(arr, i+1, j), arr[j] + s(arr, i, j-1));
}

int s(const vector<int>& arr, int i, int j)
{
	if (i == j)
		return 0;
	return min(f(arr, i+1, j), f(arr, i, j-1));
}

int win1(const vector<int>& arr) 
{
	if (arr.empty())
		return 0;
	return max(f(arr, 0 ,arr.size()-1), s(arr, 0, arr.size()-1));
}

int win2(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	int **s = new int*[arr.size()];
	int **f = new int*[arr.size()];
	for (int i = 0; i != arr.size(); i++)
	{
		s[i] = new int[arr.size()];
		f[i] = new int[arr.size()];
	}
	for (int j = 0; j < arr.size(); j++)
	{
		f[j][j] = arr[j];
		for (int i = j - 1; i >= 0; i--)
		{
			f[i][j] = max(arr[i] + s[i+1][j], arr[j] + s[i][j-1]);
			s[i][j] = min(f[i][j-1], f[i+1][j]);
		}
	}
	return max(f[0][arr.size()-1], s[0][arr.size()-1]);
}

int main()
{
	cout << win1({1,2,100,4}) << endl;
	cout << win2({1,2,100,4}) << endl;
}
