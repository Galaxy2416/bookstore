#include <iostream>

/*
有一个源源不断地吐出整数的数据流，假设你有足够的空间来保存吐出的数。请设计一个 名叫 MedianHolder 的结构，MedianHolder 可以随时取得之前吐出所有数的中位数。

【要求】
1.如果 MedianHolder 已经保存了吐出的 N 个数，那么将一个新数加入到 MedianHolder 的 过程，其时间复杂度是 O(logN)。
2.取得已经吐出的 N 个数整体的中位数的过程，时间复杂度为 O(1)。

*/

#include <queue>


using namespace std;
template <typename T>
class MedianHolder 
{

	std::priority_queue<T> max_heap;
	std::priority_queue<T, vector<T>, greater<T>> min_heap;

	public :
	T addNumer(T n)
	{
		if (max_heap.empty() || n <= max_heap.top()) 
			max_heap.emplace(n);
		else
			min_heap.emplace(n);
		modifyTwoHeadps();
		
		if (max_heap.size() == min_heap.size())
			return (max_heap.top() + min_heap.top()) / 2;
		else
			return max_heap.size() > min_heap.size() ? max_heap.top() : min_heap.top();
	}

	void modifyTwoHeadps()
	{
		if (max_heap.size() == min_heap.size() + 2) {
			min_heap.push(max_heap.top());
			max_heap.pop();
		}
		if (min_heap.size() == max_heap.size() + 2) {
			max_heap.push(min_heap.top());
			min_heap.pop();
		}
	}
};

int main()
{
	MedianHolder<int> md{};
	cout << md.addNumer(1) << endl;
	cout << md.addNumer(2) << endl;
	cout << md.addNumer(3) << endl;
	cout << md.addNumer(9) << endl;
	cout << md.addNumer(10) << endl;
	cout << md.addNumer(7) << endl;
	cout << md.addNumer(5) << endl;
}

