#include <iostream>

/*
一个缓存结构需要实现如下功能。
 void set(int key, int value):加入或修改 key 对应的 value。
 int get(int key):查询 key 对应的 value 值。
但是缓存中最多放 K 条记录，如果新的第 K+1 条记录要加入，就需要根据策略删掉一条记 录，然后才能把新记录加入。这个策略为:在缓存结构的 K 条记录中，哪一个 key 从进入缓存 结构的时刻开始，被调用 set 或者 get 的次数最少，就删掉这个 key 的记录;如果调用次数最少 的 key 有多个，上次调用发生最早的 key 被删除。
这就是 LFU 缓存替换算法。实现这个结构，K 作为参数给出。 【要求】
set 和 get 方法的时间复杂度为 O(1)。
*/

/*
1.set 和 get 方法的时间复杂度为 O(1)。
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

	using BUCKET = pair<int, list<V>>;

	unordered_map<K, typename list<V>::iterator> m_k_v;
	unordered_map<K, typename list<BUCKET>::iterator> m_k_v_bucket;
	unordered_map<typename list<V>::iterator, K, hash<V>> m_v_k;
	unordered_map<typename list<BUCKET>::iterator, K, hash<BUCKET>> m_v_k_bucket;
	list<BUCKET> bl;
	int capacity;
	int cc = 0;

  public:
	
	MyCache(int capacity) : capacity(capacity) {}
	
	void keyAddOne(K k)
	{
		auto it = m_k_v[k];
		auto itb = m_k_v_bucket[k];
		if (next(itb)->first != itb->first + 1) {
			list<V> l = {};
			bl.insert(next(itb), make_pair(itb->first + 1, l));
		}
		
		next(itb)->second.splice(next(itb)->second.begin(), itb->second, it);
		m_k_v_bucket[k] = next(itb);
		
		if (itb->second.empty())
			bl.erase(itb);
	}

	void set(K k, V v)
	{
		if(!m_k_v.contains(k))
		{
			assert(!m_k_v_bucket.contains(k));
			if (cc == capacity)
			{
				auto it = prev(bl.begin()->second.end());
				auto itb = prev(bl.end());
				m_k_v.erase(m_v_k[it]);
				m_k_v_bucket.erase(m_v_k_bucket[itb]);
				m_v_k.erase(it);
				m_v_k_bucket.erase(itb);
				bl.begin()->second.pop_back();
				if (bl.begin()->second.empty())
					bl.pop_front();
			}
			else
				cc++;

			if (bl.begin()->first != 1) {
				list<V> l = {};
				bl.push_front(make_pair(1, l));
			}

			bl.begin()->second.push_front(v);
			m_k_v[k] = bl.begin()->second.begin();
			m_k_v_bucket[k] = bl.begin();
			m_v_k[bl.begin()->second.begin()] = k;
			m_v_k_bucket[bl.begin()] = k;
		}
		else
		{
			keyAddOne(k);
			// switch to end
			//l.splice(l.end(), l, m_k_v[k]);
		}
	}

	V get(K k)
	{
		keyAddOne(k);
		return *m_k_v[k];
	}
	void print_list()
	{
		for (auto& l : bl) {
			cout << l.first << ":" << endl;
			for (auto& i : l.second)
				cout << i << ", ";
			cout << endl;
		}
		cout << "-----" << endl;
	}
};

int main()
{
	MyCache<char, int> c(5);
	c.set('a', 1);
	cout << "get:" << c.get('a') << endl;
	c.print_list();
	c.set('b', 2);
	cout << "get:" << c.get('b') << endl;
	c.print_list();
	c.set('c', 3);
	c.print_list();
	c.set('b', 2);
	cout << "get" << c.get('a') << endl;
	c.print_list();
	c.set('d', 4);
	c.print_list();
	c.set('e', 5);
	c.set('f', 6);
	c.get('f');
	c.set('g', 7);
	c.print_list();
	return 0;
}
