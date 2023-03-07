#include <iostream>
#include <vector>
#include <cstdlib>

/*
   从 5 随机到 7 随机及其扩展
   
   给定一个等概率随机产生 1~5 的随机函数 rand1To5 如下: 
   public int rand1To5() {
   	return (int) (Math.random() * 5) + 1;

   除此之外，不能使用任何额外的随机机制，请用 rand1To5 实现等概率随机产生 1~7 的随机 函数 rand1To7。
   除此之外，不能使用任何额外的随机机制，请用 rand01p 实现等概率随机产生 1~6 的随机 函数 rand1To6。
   
   进阶问题:给定一个等概率随机产生 1~m 的随机函数 rand1ToM 如下:
   
   public int rand1ToM(int m) {
   	return (int) (Math.random() * m) + 1;
   }

   除此之外，不能使用任何额外的随机机制。有两个输入参数，分别为 m 和 n，请用 rand1ToM(m)
   实现等概率随机产生 1~n 的随机函数 rand1ToN。
*/

using namespace std;

int rand1To5()
{
	return rand() % 5 + 1;
}

int rand1To7()
{
	int num = 0;
	do {
		num = (rand1To5() - 1) * 5 + (rand1To5() - 1);
	}
	while(num > 20);
	return num % 7 + 1;
}

int rand01p()
{
	double p = 0.83;
	return rand() < p ? 0 : 1;
}

int rand01()
{
	auto randTo03 = []() {
		return rand01() * 2 + rand01();
	};
	
	int num = 0;
	do 
	{
		num = randTo03() * 4 + randTo03();
	}
	while (num > 11);
	return num % 6 + 1;
}

int randToM(int m)
{
	return  (int) (rand() % m) + 1;
}

vector<int> getMSysNum(int value, int m)
{
	vector<int> res (32, 0);
	int index = res.size() - 1;
	while (value != 0)
	{
		res[index--] = value % m;
		value = value / m;
	}
	return res;
}

int getNumFromMSysNum(const vector<int>& mSysNum, int m)
{
	int res = 0;
	for (int i : mSysNum)
	{
		res = i + res * m;
	}
	return res;
}

vector<int> getRanMSysNumLessN(vector<int>& nMsys, int m)
{
	vector<int> res (nMsys.size(), 0);
	int start = 0;
	while (nMsys[start] == 0) 
	{
		start++;
	}
	int index = start;
	bool lastEqual = true;
	while (index != nMsys.size())
	{
		res[index] = randToM(m) - 1;
		if (lastEqual) {
			if (res[index] > nMsys[index])
			{
				index = start;
				lastEqual = true;
				continue;
			}
			else 
			{
				lastEqual = res[index] == nMsys[index];
			}
		}
		index++;
	}
	return res;
}

int randToN(int n, int m)
{
	vector<int> nMSys = getMSysNum(n - 1, m);
	vector<int> randNum = getRanMSysNumLessN(nMSys, m);
	return getNumFromMSysNum(randNum, m) + 1;
}

int main()
{
	
	for (int i = 0; i != 7 ; i++)
		cout << rand1To7() << ", ";
	cout << endl;
	for (int i = 0; i != 7 ; i++)
		cout << randToN(5, 7) << ", ";
	cout << endl;

	return 0;
}
