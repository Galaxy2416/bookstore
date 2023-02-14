#include <iostream> 
#include <vector>
#include <limits>

using namespace std;

/*
给定一个矩阵 matrix，其中的值有正、有负、有 0，返回子矩阵的最大累加和。 例如，矩阵 matrix 为:
-90 48 78
64 -40 64
-81 -7 66 其中，最大累加和的子矩阵为: 48 78
-40 64
-7 66
所以返回累加和 209。 例如，matrix 为:
-1 -1 -1
-1 2 2
-1 -1 -1 其中，最大累加和的子矩阵为: 22
所以返回累加和 4。
*/

int main()
{
	int max = numeric_limits<int>::min();
	int cur = 0;
	vector<vector<int>> m {{-90, 48, 78}, {64, -40, 64}, {-81, -7, 66}};
	vector<int> s(m[0].size());
	for (int i = 0; i != m.size(); ++i)
	{
		fill(s.begin(), s.end(), 0);
		for (int j = i; j != m.size(); j++)
		{
			cur = 0;
			for (int k = 0; k != s.size(); k++)
			{
				s[k] += m[j][k];
				cur += s[k];
				max = std::max(max, cur);
				cur = cur < 0 ? 0 : cur;
			}
		}
	}
	cout << max << endl;
}

