#include <iostream>
#include <cmath>

/*
在二维坐标系中，所有的值都是 double 类型，那么一个三角形可以由 3 个点来代表，给定3 个点代表的三角形，再给定一个点(x,y)，判断(x,y)是否在三角形中。
*/

using namespace std;

double getSideLength(double x1, double y1, double x2, double y2)
{
	double a = abs(x1 - x2);
	double b = abs(y1 - y2);
	return sqrt(a*a + b*b);
}

double getArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double l1 = getSideLength(x1, y1, x2, y2);
	double l2 = getSideLength(x1, y1, x3, y3);
	double l3 = getSideLength(x3, y3, x2, y2);
	double p = (l1 + l2 + l3) / 2.0;
	return sqrt((p - l1) * (p - l2) * (p - l3) * p);
}

bool isInside1(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y)
{
	double a1 = getArea(x1, y1, x2, y2, x, y);
	double a2 = getArea(x2, y2, x3, y3, x, y);
	double a3 = getArea(x3, y3, x1, y1, x, y);
	double all = getArea(x1, y1, x2, y2, x3, y3);
	return a1 + a2 + a3 <= all;
}

double cross(double x1, double y1, double x2, double y2)
{
	return x1*y2 - x2*y1;
}

bool isInside2(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y)
{
	if (cross(x3 - x1, y3 - y1, x2 - x1, y2 - y1) >= 0)
	{
		swap(x2, x3);
		swap(y2, y3);
	}
	if (cross(x2 - x1, y2 - y1, x - x1, y - y1) < 0)
		return false;

	if (cross(x3 - x2, y3 - y2, x - x2, y - y2) < 0)
		return false;

	if (cross(x1 - x3, y1 - y3, x - x3, y - y3) < 0)
		return false;
	
	return true;
	
}

int main()
{
	cout << isInside1(-1, 0, 0, 2, 1, 0, 0, 1) << endl;
	cout << isInside1(-1, 0, 0, 2, 1, 0, 0, 3) << endl;

	cout << isInside2(-1, 0, 0, 2, 1, 0, 0, 1) << endl;
	cout << isInside2(-1, 0, 0, 2, 1, 0, 0, 3) << endl;
	
}
