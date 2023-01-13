#include <iostream>

using namespace std;
int count1(int n)
{
	int res = 0;
	while (n)
	{
		res += (n & 1);
		n >>= 1;
	}
	return res;
}

int count2(int n)
{
	int res = 0;
	while (n)
	{
		n = n & (n - 1);
		res++;
	}
	return res;
}

int count3(int n)
{
	int res = 0;
	while (n)
	{
		n -= n & (~n + 1);
		res++;
	}
	return res;
}

int count4(int n) {
	n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
	n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
	n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
	n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
	return n;
}

int main()
{
	cout << count1(11)<< endl;
	cout << count2(1024)<< endl;
	cout << count3(1024)<< endl;
	cout << count4(1024)<< endl;
	return 1;
}
