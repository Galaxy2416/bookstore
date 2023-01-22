#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <deque>
/*
【题目】
给定一个字符串 str，str 表示一个公式，公式里可能有整数、加减乘除符号和左右括号， 返回公式的计算结果。
【举例】
str="48*((70-65)-43)+8*1"，返回-1816。 str="3+1*4"，返回 7。 str="3+(1*4)"，返回 7。
【说明】
1.可以认为给定的字符串一定是正确的公式，即不需要对 str 做公式有效性检查。
2.如果是负数，就需要用括号括起来，比如"4*(-3)"。但如果负数作为公式的开头或括号 部分的开头，则可以没有括号，比如"-3*4"和"(-3*4)"都是合法的。
3.不用考虑计算过程中会发生溢出的情况。
*/

using namespace std;

void addNum(deque<int>& deq, int num)
{
	if (!deq.empty() && (deq.back() == '*'|| deq.back() == '/')) 
	{
		char top = deq.back();
		deq.pop_back();
		deq.back() = top == '*' ? deq.back() * num : deq.back() / num;
	}
	else
	{
		deq.push_back(num);
	}
}

int getNum(deque<int>& deq)
{
	int res = 0;
	int cur;
	bool add = true;
	while (!deq.empty())
	{
		cur = deq.front();
		deq.pop_front();
		if ((char)cur == '+')
			add = true;
		else if ((char)cur == '-')
			add = false;
		else 
		{
			res += add ? cur : -cur;
		}
	}
	return res;
}

pair<int, int> value(const string& str, int i)	
{
	deque<int> deq{};
	int pre = 0;
	while (i < str.size() && str[i] != ')')
	{
		if (str[i] >= '0' && str[i] <= '9')
			pre = pre * 10 + str[i++] - '0';
		else if (str[i] != '(')
		{
			cout << str[i] << pre << endl;
			addNum(deq, pre);
			deq.push_back(str[i++]);
			pre = 0;
		}
		else 
		{
			auto ret = value(str, i+1);
			pre = ret.first;
			i = ret.second + 1;
			cout << "ret:" << pre << ", " <<  i << endl;
		}
	}
	addNum(deq, pre);
	return {getNum(deq), i};
}

int getValue(const string& str)
{
	return value(str, 0).first;
}

int main()
{
	cout << getValue("3*(4+5)+7") << endl;
	return 1;
}
