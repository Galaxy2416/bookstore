#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

/*
给定一个长度为 N(N>1)的整型数组 arr，可以划分成左右两个部分，左部分为 arr[0..K]， 右部分为 arr[K+1..N-1]，K 可以取值的范围是[0,N-2]。求这么多划分方案中，左部分中的最大值 减去右部分最大值的绝对值中，最大是多少?
例如:[2,7,3,1,1]，当左部分为[2,7]，右部分为[3,1,1]时，左部分中的最大值减去右部分的 最大值的绝对值为 4。当左部分为[2,7,3]，右部分为[1,1]时，左部分中的最大值减去右部分最大 值的绝对值为 6。还有很多划分方案，但最终返回 6。
*/
/*
时间复杂度为 O(N)，额外空间复杂度为 O(1)
*/

using namespace std;
int maxABS(const vector<int>& arr)
{
	if (arr.size() < 2)
		return 0;
	int max_number = *std::max_element(arr.begin(), arr.end());
	return (max_number - std::min(arr[0], arr.back()));
}

int main()
{
	cout << maxABS({2,7,3,1,1}) << endl;
}
