#include <iostream>
/*
【题目】
给定一个只由 0(假)、1(真)、&(逻辑与)、|(逻辑或)和^(异或)五种字符组成的字 符串 express，再给定一个布尔值 desired。返回 express 能有多少种组合方式，可以达到 desired 的结果。
【举例】
express="1^0|0|1"，desired=false。
只有 1^((0|0)|1)和 1^(0|(0|1))的组合可以得到 false，返回 2。 express="1"，desired=false。
无组合则可以得到 false，返回 0。
*/


using namespace std;
bool isValid(string exp) 
{
	if ((exp.size() & 1) == 0)
		return false;
	for (int i = 0; i < exp.size(); i += 2)
	{
		if (exp[i] != '1' && exp[i] != '0')
			return false;
	}

	for (int i = 1; i < exp.size(); i += 2)
	{
		
		if (exp[i] != '&' && exp[i] != '|' && exp[i] != '^')
			return false;
	}
	return true;
}

int num2(string exp, bool desired)
{
	if (exp.empty())
		return 0;

	if (!isValid(exp))
		return 0;

	int **t = new int*[exp.size()];
	int **f = new int*[exp.size()];
	for (int i = 0; i != exp.size(); i++)
	{
		t[i] = new int[exp.size()];
		f[i] = new int[exp.size()];
	}

	t[0][0] = exp[0] == '0' ? 0 : 1;
	f[0][0] = exp[0] == '1' ? 0 : 1;

	for (int i = 2; i < exp.size(); i += 2) 
	{
		t[i][i] = exp[i] == '0' ? 0 : 1;
		f[i][i] = exp[i] == '1' ? 0 : 1;
		for (int j = i-2; j >= 0; j -= 2)
			for (int k = j; k < i; k += 2)
		{
			if (exp[k + 1] == '&') {
				t[j][i] += t[j][k] * t[k+2][i];
				f[j][i] += (f[j][k] * f[k+2][i]) + f[k+2][i] * t[k+2][i];
			} else if (exp[k+1] == '|') {
				t[j][i] += (f[j][k] + t[j][k]) * t[k+2][i] + t[j][k] * f[k+2][i];
				f[j][i] += f[j][k] * f[k+2][i];
			} else {
				t[j][i] += f[j][k] * t[k+2][i] + t[j][k] * f[k+2][i] ; 
				f[j][i] += f[j][k] * f[k+2][i] + t[j][k] * t[k+2][i] ;
			}
		}
	}
	return desired ? t[0][exp.size() - 1] : f[0][exp.size() - 1];
}

int main()
{
	cout << isValid("1|0^1&1") << endl;
	cout << isValid("10^1&1") << endl;
	cout << num2("1^0|0|1", false) << endl;
	return 1;
}
