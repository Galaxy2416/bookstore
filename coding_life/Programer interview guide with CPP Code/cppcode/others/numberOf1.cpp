#include <iostream>
#include <vector>

using namespace std;

/*
给定一个整数 n，返回从 1 到 n 的数字中 1 出现的个数。
例如:
n=5，1~n 为 1，2，3，4，5。那么 1 出现了 1 次，所以返回 1。
n=11，1~n 为 1，2，3，4，5，6，7，8，9，10，11。那么 1 出现的次数为 1(出现 1 次)，10(出现 1 次)，11(有两个 1，所以出现了 2 次)，所以返回 4
*/

#include <cmath>
int solution1(int n)
{
	auto get1Nums = [](int n) {
		int res = 0;
		while (n != 0) {
			if (n % 10 == 1)
				res++;
			n /= 10;
		}
		return res;
	};
	int res = 0;
	while (n != 0) {
		res += get1Nums(n--);
	}
	return res;
}

int solution2(int n)
{
	auto getLenOfNum = [](int n) {
		int len = 0;
		while (n != 0) {
			len++;
			n /= 10;
		}
		return len;
	};

	if (n < 1) {
		return 0;
	}

	int len = getLenOfNum(n);
	if (len == 1)
		return 1;
	// interesting pattern
	int tmp1 = pow(10, len-1);
	int first = n / tmp1;
	int firstOneNum = first == 1 ? n % tmp1+1: tmp1;
	int otherOneNum = first * (len - 1) * (tmp1 / 10);
	return firstOneNum + otherOneNum + solution2(n%tmp1);
}

int main()
{
	cout << solution1(11) << endl;
	cout << solution2(11) << endl;
	cout << solution1(21345) << endl;
	cout << solution2(21345) << endl;
	return 1;
}
