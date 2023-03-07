#include <iostream>

using namespace std;

/*
给定两个不等于0的整数M和N，求M和N的最大公约数。
*/

/*
一个很简单的求两个数最大公约数的算法是欧几里得在其《几何原本》中提出的欧几里得
算法，又称为辗转相除法。
具体做法为:如果 q 和 r 分别是 m 除以 n 的商及余数，即 m=nq+r，那么 m 和 n 的最大公 约数等于 n 和 r 的最大公约数。
*/

int gcd (int m, int n)
{
	// cout << m << ", " << n << endl;
	return n == 0 ? m : gcd (n, m % n);
}

int main()
{
	cout << gcd (3, 10) << endl;
	cout << gcd (10, 3) << endl;
}
