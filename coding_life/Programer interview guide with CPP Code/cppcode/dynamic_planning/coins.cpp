#include "iostream"
#include "vector"

using namespace std;

int process1(const vector<int>& v, size_t i, int aim)
{
	int res = 0;
	if (i == v.size())
		return aim == 0 ? 1 : 0;
	else 
	{
		for (int j = 0; v[i]*j <= aim; j++)
			res += process1(v, i+1, aim - v[i]*j);
	}
	return res;
}

int conis1(vector<int> v, int aim)
{
	if (v.empty() || aim < 0)
		return 0;
	return process1(v, 0, aim);
}


int process2(const vector<int>& v, size_t i, int aim, int** map)
{
	int res = 0;
	if (i == v.size())
		res = aim == 0 ? 1 : 0;
	else
	{
		int mapValue = 0;
		for (int j = 0; v[i] * j <= aim; j++)
		{
			mapValue = map[i+1][aim - v[i]*j];
			if (mapValue != 0) 
				res += mapValue == -1 ? 0 : mapValue;
			else
				res += process2(v, i+1, aim - v[i]*j, map);
		}
	}
	map[i][aim] = res == 0 ? -1 : res;
	return res;
}

int coins2(vector<int> v, int aim)
{
	if (v.empty() || aim < 0)
		return 0;
	int **map = new int*[v.size()+1];
	for (int i = 0; i <= v.size(); i++)
		map[i] = new int[aim+1];
	return process2(v, 0, aim, map);
}

int coins3(vector<int> v, int aim)
{
	if (v.empty() || aim < 0)
		return 0;

	int **dp = new int*[v.size()];
	for (int i = 0; i < v.size(); i++)
		dp[i] = new int[aim+1];
	for (int i = 0; i < v.size(); i++)
		dp[i][0] = 1;
	for(int j = 1; v[0]*j <= aim; j++)
		dp[0][v[0]*j] = 1;
	int num = 0;
	for (int i = 1; i < v.size(); i++)
		for (int j = 1; j <= aim; j++) {
			num = 0;
			for (int k = 0; j - v[i] * k >= 0; k++)
				num += dp[i-1][j - v[i]*k];
			dp[i][j] = num;
		}
	return dp[v.size()-1][aim];
}


int coins4(vector<int> v, int aim)
{
	if (v.empty() || aim < 0)
		return 0;

	int **dp = new int*[v.size()];
	for (int i = 0; i < v.size(); i++)
		dp[i] = new int[aim+1];
	for (int i = 0; i < v.size(); i++)
		dp[i][0] = 1;
	for(int j = 1; v[0]*j <= aim; j++)
		dp[0][v[0]*j] = 1;
	int num = 0;
	for (int i = 1; i < v.size(); i++)
		for (int j = 1; j <= aim; j++) {
			dp[i][j] = dp[i-1][j];
			dp[i][j] += j-v[i] >= 0 ? dp[i][j-v[i]] : 0;  
		} 
	return dp[v.size()-1][aim];
}

int coins5(vector<int> v, int aim)
{
	if (v.empty() || aim < 0)
		return 0;

	int *dp = new int[aim+1];
	for(int j = 0; v[0]*j <= aim; j++) // j=1 -> j=0
		dp[v[0]*j] = 1;
	for (int i = 1; i < v.size(); i++)
		for (int j = 1; j <= aim; j++) {
			dp[j] += j-v[i] >= 0 ? dp[j-v[i]] : 0;  
		} 
	return dp[aim];
}

int main()
{
	cout << conis1({5, 10, 25, 1}, 10) << endl;
	cout << coins2({5, 10, 25, 1}, 10) << endl;
	cout << coins3({5, 10, 25, 1}, 10) << endl;
	cout << coins4({5, 10, 25, 1}, 10) << endl;
	cout << coins5({5, 10, 25, 1}, 10) << endl;
}


