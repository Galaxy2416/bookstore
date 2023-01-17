#include <iostream>
#include <vector>
using namespace std;

/*
【题目】
如果一个字符串为 str，把字符串 str 前面任意的部分挪到后面形成的字符串叫作 str 的旋转 词。比如 str="12345"，str 的旋转词有"12345"、"23451"、"34512"、"45123"和"51234"。给定两 个字符串 a 和 b，请判断 a 和 b 是否互为旋转词。
【举例】
a="cdab"，b="abcd"，返回 true。 a="1ab2"，b="ab12"，返回 false。 a="2ab1"，b="ab12"，返回 true。
【要求】
如果 a 和 b 长度不一样，那么 a 和 b 必然不互为旋转词，可以直接返回 false。当 a 和 b 长 度一样，都为 N 时，要求解法的时间复杂度为 O(N)。
*/

bool isRotate(string a, string b)
{
	string c(b+b);
	return c.find(a) != string::npos;

}

int main()
{
	cout << isRotate("cdab", "abcd") << endl;
	cout << isRotate("1ab2", "ab12") << endl;
	cout << isRotate("2ab1", "ab12") << endl;
	return 1;
}
