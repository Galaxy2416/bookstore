#include <iostream>
#include <vector>

/*
给定一个数组 arr，代表一排有分数的气球。每打爆一个气球都能获得分数，假设打爆气球 的分数为 X，获得分数的规则如下:
1)如果被打爆气球的左边有没被打爆的气球，找到离被打爆气球最近的气球，假设分数为 L;如果被打爆气球的右边有没被打爆的气球，找到离被打爆气球最近的气球，假设分数为 R。 获得分数为 L×X×R。
2)如果被打爆气球的左边有没被打爆的气球，找到离被打爆气球最近的气球，假设分数为 L;如果被打爆气球的右边所有气球都已经被打爆。获得分数为 L×X。
3)如果被打爆气球的左边所有的气球都已经被打爆;如果被打爆气球的右边有没被打爆的 气球，找到离被打爆气球最近的气球，假设分数为 R;如果被打爆气球的右边所有气球都已经 被打爆。获得分数为 X×R。
4)如果被打爆气球的左边和右边所有的气球都已经被打爆。获得分数为 X。
目标是打爆所有气球，获得每次打爆的分数。通过选择打爆气球的顺序，可以得到不同的 总分，请返回能获得的最大分数。
*/

/*
arr = {3,2,5}
如果先打爆 3，获得 3×2;再打爆 2，获得 2×5;最后打爆 5，获得 5。最后总分 21。 如果先打爆 3，获得 3×2;再打爆 5，获得 2×5;最后打爆 2，获得 2。最后总分 18。 如果先打爆 2，获得 3×2×5;再打爆 3，获得 3×5;最后打爆 5，获得 5。最后总分 50。 如果先打爆 2，获得 3×2×5;再打爆 5，获得 3×5;最后打爆 3，获得 3。最后总分 48。 如果先打爆 5，获得 2×5;再打爆 3，获得 3×2;最后打爆 2，获得 2。最后总分 18。 如果先打爆 5，获得 2×5;再打爆 2，获得 3×2;最后打爆 3，获得 3。最后总分 19。 能获得的最大分数为 50。
*/

/*
如果 arr 长度为 N，时间复杂度 O(N3)。
*/

using namespace std;
int process(const vector<int>& v, int L, int R)
{
	if (L == R)
		return v[L-1] * v[L] * v[R+1];
	int max = std::max(v[L-1]*v[L]*v[R+1]+process(v, L+1, R), v[L-1]*v[R]*v[R+1]+process(v, L, R-1));
	for (int i = L+1; i < R; i++)
		max = std::max(max, v[L-1]*v[i]*v[R+1] + process(v, i+1, R) + process(v, L, i-1));
	return max;
}

int maxCoins1(vector<int> v)
{
	if (v.empty())
		return 0;
	if (v.size() == 1)
		return v[0];
	v.insert(v.begin(), 1);
	v.push_back(1);
	return process(v, 1, v.size() - 2);
}

int maxCoins2(vector<int> v)
{
	if (v.empty())
		return 0;
	if (v.size() == 1)
		return v[0];
	int N = v.size();
	v.insert(v.begin(), 1);
	v.push_back(1);
	
	int **dp = new int*[v.size()];
	for (int i = 0; i != v.size(); i++)
		dp[i] = new int[v.size()];
	for (int i = 1; i != v.size() - 1; i++)
	{
		dp[i][i] = v[i-1]*v[i]*v[i+1];
		cout << dp[i][i] << ",";
	}
	for (int L = N; L >= 1; L--)
		for (int R = L + 1; R <= N; R++) 
		{
			int finalL = v[L-1]*v[L]*v[R+1] + dp[L+1][R];
			int finalR = v[L-1]*v[R]*v[R+1] + dp[L][R-1];
			dp[L][R] = std::max(finalL,finalR);
			for (int i = L+1; i < R; i++)
			{
				dp[L][R] = std::max(dp[L][R], v[i-1]*v[i]*v[i+1] + dp[L][i-1] + dp[i+1][R]);
			}
		}
	return dp[1][N];
}

int main()
{
	cout << maxCoins1({3,2,5}) << endl;
	cout << maxCoins2({3,2,5}) << endl;
	return 1;
}
