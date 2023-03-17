#include <iostream>
#include <unordered_map>
#include <utility>

/*
哈希表常见的三个操作是 put、get 和 containsKey，而且这三个操作的时间复杂度为 O(1)。
现在想加一个 setAll 功能，就是把所有记录的 value 都设成统一的值。请设计并实现这种有 setAll
功能的哈希表，并且 put、get、containsKey 和 setAll 四个操作的时间复杂度都为 O(1)。
*/

using namespace std;

template<typename K, typename V>
class MyHash 
{
	using VV = std::pair<long int, V>;
	long int time = 0;
	VV all{-1, V{}};
	std::unordered_map<K, VV> base;

public:
	bool contains(K k)
	{
		return base.contains(k);
	}

	void put(K k, V v)
	{
		base[k] = make_pair(time++, v);
	}

	void setAll(V v)
	{
		all = make_pair(time++, v);
	}

	V get(K k)
	{
		if (contains(k))
		{
			if (all.first < base[k].first)
				return base[k].second;
			else
				return all.second;
		}
		return V{};
	}
};

int main()
{
	MyHash<char, int> h;
	h.put('a', 35);
	h.put('b', 36);
	cout << h.get('a') << h.get('b') << h.get('c') << endl;
	h.setAll(33);
	cout << h.get('a') << h.get('b') << h.get('c') << endl;
	h.put('b', 36);
	cout << h.get('a') << h.get('b') << h.get('c') << endl;
	
}
