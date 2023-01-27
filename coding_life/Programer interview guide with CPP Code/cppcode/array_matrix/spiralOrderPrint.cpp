#include <iostream>
#include <vector>

using namespace std;
void printEdge(const vector<vector<int>> m, int tR, int tC, int dR, int dC)
{
	int curR = tR;
	int curC = tC;

	auto p = [&]() {
		cout << m[curR][curC] << ",";
	};

	if (tC == dC) {
		while (tR++ <= dR)
			p();

		return;
	}


	if (tR == dR) {
		while (tC++ <= dC)
			p();
		cout << endl;
		return ;
	}

	while (curC != dC)
	{
		p();
		curC++;
	}

	while (curR != dR)
	{
		p();
		curR++;
	}

	while (curC != tC)
	{
		p();
		curC--;
	}

	while (curR != tR)
	{
		p();
		curR--;
	}
}


void spiralOrderPrint(const vector<vector<int>>& matrix)
{
	int tR = 0;
	int tC = 0;
	int dR = matrix.size() -1;
	int dC = matrix[0].size() -1;
	while (tC <= dC && tR <= dR)
		printEdge(matrix, tR++, tC++, dR--, dC--);
	cout << endl;
}

int main()
{
	vector<vector<int>> v {{1,2,3,4}, {5,6,7,8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	spiralOrderPrint(v);
	return 1;
}
