#include <iostream>

/*
设计 LRU 缓存结构，该结构在构造时确定大小，假设大小为 K，并有如下两个功能。 
 set(key,value):将记录(key,value)插入该结构。
 get(key):返回 key 对应的 value 值。
*/

/*
1.set 和 get 方法的时间复杂度为 O(1)。
2.某个 key 的 set 或 get 操作一旦发生，认为这个 key 的记录成了最常使用的。
3.当缓存的大小超过 K 时，移除最不经常使用的记录，即 set 或 get 最久远的
*/

#include <list>
#include <unordered_map>
#include <map>
#include <memory>

using namespace std;

template<typename K, typename V>
class MyCache
{
	template<typename T>
	struct hash
	{
		std::size_t operator()(typename std::list<T>::iterator const& iter) const noexcept
		{
			return  (std::size_t)&(*iter);
		}
	};

	unordered_map<K, typename list<V>::iterator> m_k_v;
	unordered_map<typename list<V>::iterator, K, hash<V>> m_v_k;
	list<V> l;
	int capacity;

  public:
	
	MyCache(int capacity) : capacity(capacity) {}
	
	void set(K k, V v)
	{
		if(!m_k_v.contains(k))
		{
			if (l.size() == capacity)
			{
				auto it = prev(l.end());
				m_k_v.erase(m_v_k[it]);
				m_v_k.erase(it);
				l.pop_back();
			}

				l.push_back(v);
				auto it = prev(l.end());
				m_k_v[k] = it;
				m_v_k[it] = k;
		}
		else
		{
			// switch to end
			l.splice(l.end(), l, m_k_v[k]);
		}
	}

	V get(K k)
	{
		l.splice(l.end(), l, m_k_v[k]);
		return *m_k_v[k];
	}
	void print_list()
	{
		for (auto& i : l)
			cout << i << ", ";
		cout << endl;
	}
};

int main()
{
	MyCache<char, int> c(2);
	c.set('a', 1);
	cout << c.get('a') << endl;
	c.print_list();
	c.set('b', 2);
	cout << c.get('b') << endl;
	c.print_list();
	c.set('c', 3);
	c.print_list();
	c.set('b', 2);
	cout << c.get('a') << endl;
	c.print_list();
	c.set('d', 4);
	c.print_list();
	return 0;
}
