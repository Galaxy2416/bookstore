#include <iostream>
#include <vector>
#include <limits>
#include <sys/errno.h>
#include <vector>

/*
“a”~“z”，请实现字典树结构，并包含以下四个主要功能。
 void insert(String word):添加 word，可重复添加。
 void delete(String word):删除 word，如果 word 添加过多次，仅删除一个。
 boolean search(String word):查询 word 是否在字典树中。
 int prefixNumber(String pre):返回以字符串 pre 为前缀的单词数量。
*/

using namespace std;
struct TireNode {
	int path;
	int end;
	vector<TireNode*> map;
	
	TireNode()
	{
		path = 0;
		end = 0;
		map.resize(26, nullptr);
	}
};

class Tire 
{
	private:
		TireNode root{};
	public:
		void insert(const string& word)
		{
			TireNode* node = &root;
			node->path++;
			int index = 0;
			for (char s : word)
			{
				index = s - 'a';
				if (node->map[index] == nullptr)
					node->map[index] = new TireNode();
				//cout << s << ", " << node->map[index] << "," << index << endl;
				node = node->map[index];
				node->path++;
			}
			node->end++;
		}

		bool search(const string& word)
		{
			if (word.empty())
				return false;
			TireNode* node = &root;
			int index = 0;
			for (char s : word)
			{
				index = s - 'a';
				//cout << s << ", " << node->map[index] << "," << index << endl;
				if (node->map[index] == nullptr)
					return false;
				node = node->map[index];
			}
			return node->end != 0;
		}

		void delete_(const string& word)
		{
			if (search(word))
			{
				TireNode* node = &root;
				int index = 0;
				for (char s : word)
				{
					index = s - 'a';
					if (node->map[index]->path-- == 1)
					{
						delete node->map[index];
						node->map[index] = nullptr;
						return;
					}
					node = node->map[index];
				}
				node->end--;
			}
		}

		int prefixNumber(const string& pre)
		{
			if (pre.empty())
				return 0;
			TireNode* node = &root;
			int index = 0;
			for (char s : pre)
			{
				index = s - 'a';
				if (node->map[index] == nullptr)
					return 0;
				node = node->map[index];
			}
			return node->path;
		}
};

int main()
{
	Tire t;
	t.insert("hello");
	t.insert("moutain");
	t.insert("month");
	t.insert("hell");

	cout << t.search("hell") << endl;
	cout << t.search("hel") << endl;

	cout << t.prefixNumber("mo") << endl;
	cout << t.prefixNumber("hell") << endl;

	t.delete_("hell");

	cout << t.prefixNumber("mo") << endl;
	cout << t.prefixNumber("hell") << endl;
}
