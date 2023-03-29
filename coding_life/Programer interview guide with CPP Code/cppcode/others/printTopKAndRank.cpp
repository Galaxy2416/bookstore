#include <iostream>

/*
【题目】
给定 String 类型的数组 strArr，再给定整数 k，请严格按照排名顺序打印出现次数前 k 名的 字符串。
【举例】
strArr=["1","2","3","4"]，k=2
No.1: 1, times: 1
No.2: 2, times: 1 这种情况下，所有的字符串都出现一样多，随便打印任何两个字符串都可以。 strArr=["1","1","2","3"]，k=2
输出:
No.1: 1, times: 2
No.2: 2, times: 1
或者输出:
No.1: 1, times: 2 No.2: 3, times: 1

【要求】
如果 strArr 长度为 N，时间复杂度请达到 O(Nlogk)。
进阶问题:设计并实现 TopKRecord 结构，可以不断地向其中加入字符串，并且可以根据字 符串出现的情况随时打印加入次数最多的前 k 个字符串，具体为:
1.k在TopKRecord实例生成时指定，并且不再变化(k是构造函数的参数)。
2.含有 add(String str)方法，即向 TopKRecord 中加入字符串。
3.含有 printTopK()方法，即打印加入次数最多的前 k 个字符串，打印有哪些字符串和对应
的次数即可，不要求严格按排名顺序打印。

【举例】
TopKRecord record = new TopKRecord(2); // 打印 Top 2 的结构 record.add("A");
record.printTopK();
此时打印:
TOP:
Str: A Times: 1 record.add("B");
record.add("B"); record.printTopK(); 此时打印:
TOP:
Str: A Times: 1 Str: B Times: 2
或者打印
record.add("C"); record.add("C"); record.printTopK(); 此时打印:
TOP:
Str: B Times: 2 Str: C Times: 2
或者打印

TOP:
Str: C Times: 2
Str: B Times: 2
【要求】
1.在任何时候，add 方法的时间复杂度不超过 O(logk)。 2.在任何时候，printTopK 方法的时间复杂度不超过 O(k)。
*/


// only second qs

#include <sys/_types/_timespec.h>
#include <unordered_map>
#include <vector>

using namespace std;
struct Node 
{
	string str;
	int times;

	Node()
	{
		times = 0;
	}
	Node(string s, int t):str(s), times(t)
	{
	}
	bool operator==(const Node &other) const
	{
		return str == other.str;
	}

};

template <>
struct hash<Node>
{
	std::size_t operator()(const Node& k) const
	{
		using std::size_t;
		using std::hash;
		return (hash<string>()(k.str));
	}
};

class TopKRecord
{
	vector<Node> heap;
	int index = 0;
	unordered_map<string, Node> strNodeMap;
	unordered_map<Node, int> nodeIndexMap;


	public:
	TopKRecord(int size)
	{
		heap.resize(size);
	}

	void add (string str)
	{
		int preIndex = -1;
		Node curnode(str, 1);
		if (!strNodeMap.contains(str))
		{
			strNodeMap[str] = curnode;
			nodeIndexMap[curnode] = -1;
		}
		else
		{
			strNodeMap[str].times++;
			preIndex = nodeIndexMap[curnode];
			heap[preIndex].times++; // all copy here. better in pointer
		}

		if (preIndex == -1)
		{
			if (index == heap.size())
			{
				if (heap[0].times < curnode.times) {
					nodeIndexMap[heap[0]] = -1;
					nodeIndexMap[curnode] = 0;
					heap[0] = curnode;
					heapify(0, index);
				}
			}
			else {
				nodeIndexMap[curnode] = index;
				heap[index] = curnode;
				heapInsert(index++);
			}
		}
		else
		{
			heapify(preIndex, index);
		}
	}



	void heapify(int index, int heapSize)
	{
		int l = index * 2 + 1;
		int r = index * 2 + 2;
		int smallest = index;
		while (l < heapSize)
		{
			if (heap[l].times < heap[index].times) {
				smallest = l;
			}

			if (r < heapSize && heap[r].times < heap[smallest].times) {
				smallest = r;
			}

			if (smallest != index)
				swap(heap[smallest], heap[index]);
			else
				break;
			index = smallest;
			int l = index * 2 + 1;
			int r = index * 2 + 2;
		}
	}

	void heapInsert(int index)
	{
		while (index != 0)
		{
			int parent = (index - 1) / 2;
			if (heap[index].times < heap[parent].times)
			{
				swap(heap[index], heap[parent]);
				index = parent;
			}
			else
				break;
		}
	}

	friend ostream& operator<<(ostream &os, const TopKRecord& tp);
};

ostream& operator<<(ostream &os, const TopKRecord& tp)
{
	for (const auto& nd : tp.heap)
	{
		if (nd.times <= 0)
			break;
		os << nd.times << ", " << nd.str << endl;
	}
	cout << endl;

	return os;
}

int main()
{
	TopKRecord tp(3);
	tp.add("a");
	tp.add("b");
	tp.add("b");
	cout << tp;
	tp.add("d");
	tp.add("e");
	tp.add("f");
	cout << tp;
	tp.add("a");
	tp.add("c");
	cout << tp;
	return 1;
}
