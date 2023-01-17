#include <iostream>

/*
【题目】
给定一个字符串 str，返回 str 的统计字符串。例如，"aaabbadddffc"的统计字符串为 "a_3_b_2_a_1_d_3_f_2_c_1"。
补充问题:给定一个字符串的统计字符串 cstr，再给定一个整数 index，返回 cstr 所代表的 原始字符串上的第 index 个字符。例如，"a_1_b_100"所代表的原始字符串上第 0 个字符是'a'， 第 50 个字符是'b'。
*/

using namespace std;
string getCountString(const string& str)
{
	if (str.empty())
		return "";
	int num = 1;
	string res; res.push_back(str[0]);
	for (int i = 1; i < str.size(); i++)
	{
		if (str[i] != str[i-1])
		{
			res = res + "_" + to_string(num) + "_" + str[i];
			num = 1;
		}
		else
		{
			num++;
		}
	}
	return res + "_" + to_string(num); 
}

char getCharAt(const string& str, int index)
{
	if (str.empty())
		return 0;
	bool stage = true;
	char cur = 0;
	int num = 0;
	int sum = 0;
	for (char i : str)
	{
		if (i == '_')
			stage = !stage;
		else if (stage) 
		{
			sum += num;
			if (sum > index)
				return cur;
			num = 0;
			cur = i;
		}
		else 
		{
			num = num * 10 + (i - '0');
		}
	}
	return sum + num > index ? cur : 0;
}

int main()
{
	cout << getCountString("aaabbadddffc") << endl;
	cout << getCharAt(getCountString("aaabbadddffc"), 8) << endl;
	return 1;
}

