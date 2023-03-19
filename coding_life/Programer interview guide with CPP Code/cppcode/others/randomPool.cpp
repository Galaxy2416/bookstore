#include <iostream>

/*
设计一种结构，在该结构中有如下三个功能。
 insert(key):将某个 key 加入到该结构，做到不重复加入。
 delete(key):将原本在结构中的某个 key 移除。
 getRandom():等概率随机返回结构中的任何一个 key。
【要求】
Insert、delete 和 getRandom 方法的时间复杂度都是 O(1)。
*/

#include <list>
#include <unordered_map>
#include <map>
#include <cmath>

using namespace std;
template<typename K>
class Pool 
{
	unordered_map<K, size_t> k2i;
	unordered_map<size_t, K> i2k;
	size_t size{0};

	public:
	void Insert(K k) 
	{
		if (!k2i.contains(k))
		{
			k2i[k] = size;
			i2k[size++] = k;
		}
	}

	void Delete(K k)
	{
		if (k2i.contains(k))
		{
			int lastkey = i2k[--size];
			int deletIndex = k2i[k];
			k2i[lastkey] = deletIndex;
			i2k[deletIndex] = lastkey;
			k2i.erase(k);
			i2k.erase(size);
		}
	}

	K getRandomValue()
	{
		return i2k[rand()%size];
	}
};

int main()
{
	Pool<int> p;
	p.Insert(1);p.Insert(1);p.Insert(3);p.Insert(2);p.Insert(4);p.Insert(5);p.Insert(6);
	p.Delete(2);
	for (int i = 0; i != 100; ++i)
		cout << p.getRandomValue() << ",";
	cout << endl;
	return 1;
}
