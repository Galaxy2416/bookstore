#include <iostream>
#include <limits>

/*

定义回文数的概念如下:
 如果一个非负数左右完全对应，则该数是回文数，例如:121，22等。
 如果一个负数的绝对值左右完全对应，也是回文数，例如:-121，-22等。
给定一个 32 位整数 num，判断 num 是否是回文数。
*/

using namespace std;
bool isPalindrome(int i)
{
	if (i == numeric_limits<int>::min())
		return false;
	i = abs(i);
	int help = 1;
	while (i/help >= 10)
		help *= 10;
	
	while (i != 0)
	{
		if (i/help != i%10)
			return false;
		i = (i%help) / 10;
		help /= 100;
	}
	return true;
}

int main()
{
	cout << isPalindrome(123) << endl;
	cout << isPalindrome(121) << endl;
	cout << isPalindrome(-1221) << endl;
	cout << isPalindrome(1221) << endl;
	cout << isPalindrome(-2147483648) << endl;

}
