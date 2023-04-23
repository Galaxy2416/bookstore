#include <iostream>
#include <limits>
#include <vector>
#include <numeric>

/*
【题目】
给定一个整型数组 arr，数组中的每个值都为正数，表示完成一幅画作需要的时间，再给定 一个整数 num，表示画匠的数量，每个画匠只能画连在一起的画作。所有的画家并行工作，请 返回完成所有的画作需要的最少时间。
【举例】
arr=[3,1,4]，num=2。
最好的分配方式为第一个画匠画 3 和 1，所需时间为 4。第二个画匠画 4，所需时间为 4。 因为并行工作，所以最少时间为 4。如果分配方式为第一个画匠画 3，所需时间为 3。第二个画 匠画 1 和 4，所需的时间为 5。那么最少时间为 5，显然没有第一种分配方式好。所以返回 4。
arr=[1,1,1,4,3]，num=3。
最好的分配方式为第一个画匠画前三个 1，所需时间为 3。第二个画匠画 4，所需时间为 4。 第三个画匠画 3，所需时间为 3。返回 4。
*/

// dp[i][j] = min { max { dp[i-1][k] , sum[k+1..j] } (0<=k<j) }
//  O(N2×num)

using namespace std;
int solution1(const vector<int>& arr, int num)
{
	assert(!arr.empty() && num > 0);
	vector<int> map(arr.size(), 0);
	vector<int> sumArr(arr.size(), 0);

	for (int i = 1; i != arr.size(); ++i)
	{
		sumArr[i] = sumArr[i-1] + arr[i];
		map[i] = sumArr[i];
	}

	for (int i = 0; i < num; i++)
	{
		for (int j = map.size() - 1; j > i - 1; j--) {
			int min_ = std::numeric_limits<int>::max();
			for (int k = i - 1; k < j; k++) {
				min_ = min(min_, max(map[k], sumArr[j] - sumArr[k]));
			}
			map[j] = min_;
		}
	}
	return map.back();
}

/*
动态规划用四边形不等式优化后的解法
时间复杂度从 O(N2×num)降至 O(N2)
*/

int solution2(const vector<int>& arr, int num)
{
	assert(!arr.empty() && num > 0);
	vector<int> map(arr.size(), 0);
	vector<int> sumArr(arr.size(), 0);
	sumArr[0] = arr[0];
	map[0] = arr[0];
	for (int i = 1; i != arr.size(); i++)
	{
		sumArr[i] = sumArr[i-1] + arr[i];
		map[i] = sumArr[i];
	}

	vector<int> cands(arr.size(), 0);
	for (int i = 0; i < num; i++)
	{
		for (int j = map.size() - 1; j > i - 1; j--) {
			int minPar = cands[j];
			int maxPar = j == map.size() - 1 ? j : cands[j + 1];  
			int min_ = std::numeric_limits<int>::max();
			for (int k = minPar; k <= maxPar; k++)
			{
				int cur = max(map[k], sumArr[j] - sumArr[k]);
				if (cur <= min_) {
					min_ = cur;
					cands[j] = k;
				}
			}
			map[j] = min_;
		}
	}
	return map.back();
}

/* solution 3 */
int getNeedNum(const vector<int>& arr, int lim) 
{
	int res = 1;
	int stepSum = 0;
	for (int i = 0; i != arr.size(); i++) 
	{
		if (arr[i] > lim) 
		{
			return std::numeric_limits<int>::max();
		}
		stepSum += arr[i];
		if (stepSum > lim) {
			res++;
			stepSum = arr[i];
		}
	}
	return res; 
}


/*
假设 arr 所有值的累加和为 S，那么二分的次数为 logS，每次调用 getNeedNum 方法，然后 进行二分，getNeedNum 方法的时间复杂度为 O(N)。所以 solution3 的时间复杂度为 O(NlogS)。
*/
int solution3(const vector<int>& arr, int num)
{
	assert(!arr.empty() && num > 0);
	if (arr.size() < num) {
		return *std::max_element(arr.begin(), arr.end());
	}
	else {
		int minSum = 0;
		int maxSum = std::reduce(arr.begin(), arr.end());
		while (minSum != maxSum - 1) {
			int mid = (minSum + maxSum) / 2;
			if (getNeedNum(arr, mid) > num)
			{
				minSum = mid;
			}
			else 
			{
				maxSum = mid;
			}
		}
		return maxSum;
	}
}

int main()
{
	cout << solution1({1,1,1,4,3}, 3) << endl;
	cout << solution2({1,1,1,4,3}, 3) << endl;
	cout << solution3({1,1,1,4,3}, 3) << endl;
	return 1;
}
