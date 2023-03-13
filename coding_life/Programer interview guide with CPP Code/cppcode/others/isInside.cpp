#include <iostream>
#include <cmath>

/*
在二维坐标系中，所有的值都是 double 类型，那么一个矩形可以由 4 个点来代表，(x1,y1) 为最左的点、(x2,y2)为最上的点、(x3,y3)为最下的点、(x4,y4)为最右的点。给定 4 个点代 表的矩形，再给定一个点(x,y)，判断(x,y)是否在矩形中。
*/

using namespace std;
bool isInside(double x1, double y1, double x4, double y4, double x, double y)
{
	cout << x1 << ", " << y1 << ":" << x4 << ", " << y4 << ":" << x << ", " << y << endl;
	if (x <= x1 || x >= x4 || y >= y1 || y <= y4)
		return false;
	return true;
}

bool isInside(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x, double y)
{
	if (y1 == y2)
		return isInside(x1, y1, x4, y4, x, y);
	double l = abs(y4 - y3);
	double k = abs(x4 - x3);
	double r = sqrt(l*l + k*k);
	double cos = k / r;
	double sin = l / r;
	auto getx = [&cos, &sin](double x, double y) {
		return x*cos + y*sin;
	};

	auto gety = [&cos, &sin](double x, double y) {
		return y*cos - x*sin;
	};

	return isInside(getx(x1, y1), gety(x1, y1), getx(x4, y4), gety(x4, y4), getx(x, y), gety(x, y));
}

int main()
{
	cout << isInside(1,1, 0,0, 3,3) << endl;
	cout << isInside(0,5, 5,0, 3,1) << endl;
	// (-3, 1), (2, 4), (3, -2), (-2, -5·)
	cout << isInside(-3,1, 2,4, -2,-5, 3,-2, 0,0) << endl;
	return 1;
}
