#include <iostream>
#include <vector>

using namespace std;

/*

【题目】
有 N 个长度不一的数组，所有的数组都是有序的，请从大到小打印这 N 个数组整体最大的 前K个数。
例如，输入含有 N 行元素的二维数组可以代表 N 个一维数组。 219,405,538,845,971
148,558
52,99,348,691
再输入整数 k=5，则打印: Top 5: 971,845,691,558,538
`
【要求】
1.如果所有数组的元素个数小于 K，则从大到小打印所有的数。 2.要求时间复杂度为 O(KlogN)。
*/

struct HeapNode {

	int value;
	int arrNum;
	int index;

	HeapNode(int value = 0, int arrNum = 0, int index = 0) : value(value), arrNum(arrNum), index(index)
	{
	}
};

void heapInsert(vector<HeapNode>& heap, int index)
{
	while (index != 0)
	{
		int parent = (index - 1) / 2;
		if (heap[parent].value < heap[index].value)
		{
			swap(heap[index], heap[parent]);
			index = parent;
		}
		else 
			break;
	}
}

void heapify(vector<HeapNode>& heap)
{
	int index = 0;
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int largest = index;
	while (left < heap.size())
	{
		if (heap[left].value > heap[index].value)
			largest = left;
		else if (right < heap.size() && heap[right].value > heap[index].value)
			largest = right;
		if (largest != index)
			swap(heap[largest], heap[index]);
		else
			break;
		index = largest;
		left = index * 2 + 1;
		right = index * 2 + 1;
	}
}

void printTopK(const vector<vector<int>> matrix, int topK)
{
	vector<HeapNode> heap{};
	for (int i = 0; i != matrix.size(); ++i)
	{
		heap.emplace_back(matrix[i].back(), i, matrix[i].size() - 1);
		heapInsert(heap, i);
	}

	cout << "TOP " << topK << " : " << endl;
	
	for (int i = 0; i != topK; ++i)
	{
		if (heap.size() == 0)
			break;
		cout << heap[0].value << endl;
		if (heap[0].index != 0)
			heap[0].value = matrix[heap[0].arrNum][--heap[0].index];
		else {
			heap.erase(heap.end() - 1);
			swap(heap[0], heap[heap.size() - 1]);
		}
		heapify(heap);
	}
}

int main()
{
	printTopK({{219,405,538,845,971}, {148,558}, {52,99,348,691}}, 5);
	return 1;
}

