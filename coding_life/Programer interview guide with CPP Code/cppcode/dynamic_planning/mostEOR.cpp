#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int mostEOR(const vector<int>& arr)
{
	if (arr.empty())
		return 0;
	int eor = 0;
	vector<int> dp(arr.size());
	unordered_map<remove_reference_t<decltype(arr)>::value_type, size_t> map_;
	map_[0] = -1;
	dp[0] = arr[0] ? 1 : 0;
	for(int i = 0; i != arr.size(); ++i)
	{
		eor ^= arr[i];
		if (map_.contains(eor))
		{
			int preEorIndex = map_[eor];
			dp[i] = preEorIndex == -1 ? 1 : (dp[preEorIndex] + 1);
		}
		dp[i] = max(dp[i-1], dp[i]);
		map_[eor] = i;
	}
	return dp[arr.size() - 1];
}

int main()
{
	cout << mostEOR({6, 3, 2, 1}) << endl;
	cout << mostEOR({{3,2,1,9,0,7,0,2,1,3}}) << endl;
}
