#include <iostream>
#include <cmath>

/*
有一台机器按自然数序列的方式吐出球(1 号球，2 号球，3 号球，......)，你有一个袋子， 袋子最多只能装下 K 个球，并且除袋子以外，你没有更多的空间。设计一种选择方式，使得当 机器吐出第 N 号球的时候(N>K)，袋子中的球数是 K 个，同时可以保证从 1 号球到 N 号球中的 每一个被选进袋子的概率都是 K/N。举一个更具体的例子，有一个只能装下 10 个球的袋子，当 吐出 100 个球时，袋子里有 10 个球，并且 1~100 号中的每一个球被选中的概率都是 10/100。 然后继续吐球，当吐出 1000 个球时，袋子里有 10 个球，并且 1~1000 号中的每一个球被选中 的概率都是 10/1000。继续吐球，当吐出 i 个球时，袋子里有 10 个球，并且 1~i 号中的每一个 球被选中的概率都是 10/i，即吐球的同时，已经吐出的球被选中的概率也动态地变化。
*/

#include <vector>

using namespace std;

vector<int> getNumsRand(int k, int n)
{
	
	vector<int> r;
	if (k < 1 || n < 1)
		return r;
	for (int i = 0; i != k; i++)
		r.push_back(i);
	for (int i = k; i != n; i++)
	{
		if (k >= rand()%i + 1)
			r[rand()%k] = i;
	}
	return r;
}
int main()
{
	auto res = getNumsRand(3, 10);
	for (int i : res)
		cout << i << ", ";
	cout << endl;
	return 0;
}
