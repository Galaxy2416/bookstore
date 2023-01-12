#include <iostream>
#include <vector>

using namespace std;
using ARR = vector<vector<int>>;

void infect(ARR& m, int i, int j)
{
	if (i < 0 || j < 0 || i >= m.size() || j >= m[0].size() || m[i][j] != 1)
		return;
	m[i][j] = 2;
	infect(m, i-1, j);
	infect(m, i+1, j);
	infect(m, i, j-1);
	infect(m, i, j+1);
}

int countIsIands(ARR m)
{
	if (m.empty() || m[0].empty())
		return 0;
	int res = 0;
	for (int i = 0; i < m.size(); i++)
		for (int j = 0; j < m[0].size(); j++)
			if (m[i][j] == 1) {
				res++;
				infect(m, i, j);
			}
	return res;
}

int main()
{
	ARR a {{1,0,1,1}, {1,0,1,1}, {0,0,0,0},{1,0,1,0}};
	cout << countIsIands(a) << endl;
	return 1;
}
