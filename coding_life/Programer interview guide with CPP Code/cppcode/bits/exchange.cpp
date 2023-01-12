#include <iostream>

using namespace std;

int main()
{
	int a=1, b=20;
	
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
	cout << a << ", " << b;
	return 1;
}
