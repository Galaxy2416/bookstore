#include <iostream>

/*
每条边不是平行于 X 轴就是平行于 Y 轴的矩形，可以用左下角点和右上角点来表示。比如 {1,2,3,4}
给定一个 N 行 4 列的二维数组 matrix，表示 N 个每条边不是平行于 X 轴就是平行于 Y 轴的 矩形。想知道所有的矩形能否组成一个大的完美矩形。完美矩形是指拼出的整体图案是矩形， 既不缺任何块儿，也没有重合的部分。

 matrix = {
      {1,1,3,3},
      {3,1,4,2},
      {1,3,2,4},
	  {3,2,4,4}
	  }
返回 false。如果画出这四个矩形，会发现拼出的图案缺少{2,3,3,4}这一块儿。

matrix = {
      {1,1,3,3},
      {3,2,4,3},
      {3,2,4,4},
      {1,3,2,4},
	  {2,3,3,4}
	  }
返回 false。拼出的图案缺少{3,1,4,2}，并且{3,2,4,3}是重合区域。

  matrix = {
      {1,1,3,3},
      {3,1,4,2},
      {3,2,4,4},
      {1,3,2,4},
	  {2,3,3,4}
	  }
返回 true。拼出的图案是一整块儿矩形，既不缺任何块儿，也没有重合的部分。
*/

#include <utility>
#include <vector>
#include <set>
#include <limits>
using namespace std;

bool isRectangleCover(const vector<vector<int>>& matrixs)
{
	if (matrixs.size() == 0 || matrixs[0].size() == 0)
		return false;
	int most_left = numeric_limits<int>::max();
	int most_right = std::numeric_limits<int>::min();
	int most_up = std::numeric_limits<int>::min();
	int most_down = std::numeric_limits<int>::max();
	set<pair<int, int>> s;
	int area = 0;
	for (auto& matrix : matrixs)
	{
		most_left = min(most_left, matrix[0]);
		most_down = min(most_down, matrix[1]);
		most_right = max(most_right, matrix[2]);
		most_up = max(most_up, matrix[3]);
		area += (matrix[2] - matrix[0]) * (matrix[3] - matrix[1]);
		auto i_r =  [&] (int x, int y) {
			auto [e, f] = s.insert(std::make_pair(matrix[x], matrix[y]));
			if (!f) {
				s.erase(e);
			}
		};
		i_r(0,1);
		i_r(0,3);
		i_r(2,1);
		i_r(2,3);
	}

	if (!s.contains(std::make_pair(most_left, most_up)) ||
		 !s.contains(std::make_pair(most_right, most_up)) ||
		 !s.contains(std::make_pair(most_right, most_down)) ||
		 !s.contains(std::make_pair(most_left, most_down)) || s.size() != 4) 
	{
		return false;
	}

	return area == (most_right - most_left) * (most_up - most_down) ;
}

int main()
{

	cout << isRectangleCover({
      {1,1,3,3},
      {3,2,4,3},
      {3,2,4,4},
      {1,3,2,4},
	  }) << endl;

 // 返回 false。拼出的图案缺少{3,1,4,2}，并且{3,2,4,3}是重合区域。
	cout << isRectangleCover({
      {1,1,3,3},
      {3,2,4,3},
      {3,2,4,4},
      {1,3,2,4},
	  {2,3,3,4}
	  }) << endl;

	cout << isRectangleCover({
      {1,1,3,3},
      {3,1,4,2},
	  {3,2,4,4},
      {1,3,2,4},
	  {2,3,3,4}
	  }) << endl;
}

