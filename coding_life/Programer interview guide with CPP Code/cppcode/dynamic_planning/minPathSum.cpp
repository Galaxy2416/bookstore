#include <iostream>
#include <algorithm>


using namespace std;
template <size_t M, size_t N>
constexpr int minPathSum1(const int (&m)[M][N])
{
	if ( m == nullptr || m[0] == nullptr)
		return 0;
	int dp[M][N] = {};
	dp[0][0] = m[0][0];
	for (size_t i = 1; i != M; ++i)
		dp[i][0] = dp[i- 1][0] + m[i][0];
	for (size_t i = 1; i != N; ++i)
		dp[0][i] = dp[0][i-1] + m[0][i];
	for (size_t i = 1; i != M; ++i)
		for (size_t j = 1; j != N; ++j)
		{
			dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + m[i][j];
			cout << "[" << i << "]" << "[" << j << "]" << dp[i][j] << endl;
		}
	return dp[M-1][N-1];
}

template <size_t M, size_t N>
constexpr int minPathSum2(const int (&m)[M][N])
{
	if ( m == nullptr || m[0] == nullptr)
		return 0;
	bool row = (M >= N);
	constexpr size_t less = min(M, N);
	constexpr size_t more = max(M, N);
	int arr[less] = {};
	arr[0] = m[0][0];
	cout << arr[0] << ", ";
	for (size_t i = 1; i < less; ++i)
	{
		arr[i] = arr[i-1] + (row ? m[0][i] : m[i][0]);
		cout << "[" << 0 << "]" << "[" << i << "]" << arr[i] << ", ";
	}
	cout << endl;
	for (size_t i = 1; i != more; ++i) 
	{
		arr[0] = arr[0] + (row ? m[i][0] : m[0][i]);
		cout << "[" << i << "]" << "[0]" << arr[0] << ", ";
		for (size_t j = 1; j != less; ++j)
		{
			arr[j] = min(arr[j-1], arr[j]) + (row ? m[i][j] : m[j][i]);
			cout << "[" << i << "]" << "[" << j << "]" << arr[j] << ", ";
		}
		cout << endl;
	}
	return arr[less - 1];
}

int main()
{
	constexpr int a[][4] = {{1,3,5,9}, {8, 1, 3 ,4}, {5, 0, 6, 1}, {8, 8, 4, 0}};
	cout << minPathSum1(a) << endl;
	cout << minPathSum2(a) << endl;

}
