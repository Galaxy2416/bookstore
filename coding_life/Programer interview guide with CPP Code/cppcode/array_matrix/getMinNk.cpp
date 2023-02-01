#include <iostream>
#include <vector>


/*
找到无序数组中最小的 k 个数
【题目】
给定一个无序的整型数组 arr，找到其中最小的 k 个数。
【要求】
如果数组 arr 的长度为 N，排序之后自然可以得到最小的 k 个数，此时时间复杂度与排序的 时间复杂度相同，均为 O(NlogN)。本题要求实现时间复杂度为 O(Nlogk)和 O(N)的方法。
【难度】
O(Nlogk)的方法 尉 ★★☆☆ O(N)的方法 将 ★★★★
*/

/* O(Nlogk) */

using namespace std;
void heapInsert(vector<int>& arr, int value, int index)
{
	arr[index] = value;
	while (index != 0)
	{
		int parent = (index - 1) / 2 ;
		if (arr[parent] < arr[index])
		{
			swap(arr[parent], arr[index]);
			index = parent;
		}
		else
			break;
	}
}

void heapify(vector<int>& arr, int index, int heapSize)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int largest = index;
	while (left < heapSize)
	{
		if (arr[left] > arr[index])
			largest = left;
		if (right < heapSize && arr[right] > arr[largest])
			largest = right;
		if (largest != index )
			swap(arr[largest], arr[index]);
		else
			break;
		index = largest; 
		left = index * 2 + 1;
		right = index * 2 + 2;
	}
}

vector<int> getMinKnumByHeap(const vector<int>& arr, int k)
{
	if (k < 1 || k > arr.size())
		return arr;
	vector<int> kheap(k, 0);
	for (int i = 0; i != k; i++)
		heapInsert(kheap, arr[i], i);
	for (int i = k; i != arr.size(); i++)
	{
		if (arr[i] < kheap[0])
		{
			kheap[0] = arr[i];
			heapify(kheap, 0, k);
		}
	}
	return kheap;
}


/*
O(N)的解法。需要用到一个经典的算法——BFPRT 算法，该算法于 1973 年由 Blum、Floyd、 Pratt、Rivest 和 Tarjan 联合发明，其中蕴含的深刻思想改变了世界。BFPRT 算法解决了这样一个 问题，在时间复杂度 O(N)内，从无序的数组中找到第 k 小的数。显而易见的是，如果我们找到 了第 k 小的数，那么想求 arr 中最小的 k 个数，就是再遍历一次数组的工作量而已，所以关键问 题就变成了如何理解并实现 BFPRT 算法。
*/


int select(vector<int>& arr, int begin, int end, int i);
int getMedian(vector<int>& arr, int begin, int end);
pair<int, int> partition(vector<int>& arr, int begin, int end, int pivotValue);

int medianOfMedians(vector<int>& arr, int begin, int end)
{
	
	cout << begin << "," << end << endl;
	int num = end - begin + 1;
	int offset = num % 5 == 0 ? 0 : 1;
	vector<int> mArr(num/5 + offset, 0);
	for (int i = 0; i < mArr.size(); i++)
	{
		int beginI = begin + i * 5;
		int endI = beginI + 4;
		mArr[i] = getMedian(arr, beginI, min(end, endI));

	}

	return select(mArr, 0, mArr.size() - 1, mArr.size() / 2);
}

int select(vector<int>& arr, int begin, int end, int i)
{
	if (begin == end)
		return arr[begin];
	int pivot = medianOfMedians(arr, begin, end);
	auto pivotRange = partition(arr, begin, end, pivot);
	if (i >= pivotRange.first && i <= pivotRange.second)
		return arr[i];
	else if (i < pivotRange.first)
		return select(arr, begin, pivotRange.first - 1, i);
	else
		return select(arr, pivotRange.second + 1, end, i - pivotRange.second);
}

pair<int, int> partition(vector<int>& arr, int begin, int end, int pivotValue)
{
	int small = begin - 1;
	int cur = begin;
	int big = end + 1;
	while (cur != big) 
	{
		if (arr[cur] < pivotValue)
			swap(arr[++small], arr[cur++]);
		else if (arr[cur] > pivotValue)
			swap(arr[--big], arr[cur]);
		else
			cur++;
	}
	return {small + 1, big - 1};
}


void insertionSort(vector<int>& arr, int begin, int end)
{
	for (int i = begin + 1; i != end + 1; i++)
		for (int j = i; j != begin; j--) {
			if (arr[j - 1] > arr[j])
				swap(arr[j-1], arr[j]);
			else
				break;
		}
			
}

int getMedian(vector<int>& arr, int begin, int end) 
{


	insertionSort(arr, begin, end);
	int sum = end + begin;
	int mid = (sum/2) + (sum%2);
	return arr[mid];
}

int getMinKthByBFPRT(const vector<int>& arr, int K)
{
	auto arr2 = arr;
	return select(arr2, 0, arr2.size() - 1, K - 1);
}

vector<int> getMinKnumByBFPRT(const vector<int>& arr, int k)
{
	if (k < 1 || k > arr.size())
		return arr;
	int minKth = getMinKthByBFPRT(arr, k);
	vector<int> res;
	for (int i : arr)
		if (i < minKth)
			res.push_back(i);
	while(res.size() < k)
		res.push_back(minKth);
	return res;
}

int main()
{
	ostream_iterator<int> out(cout, ", ");
	vector<int> v {2,5,1,7,8,4,9,3,6,0};
	for (int i : getMinKnumByHeap(v, 4))
		out = i;
	cout << endl;
	for (int i : getMinKnumByBFPRT(v, 4))
		out = i;
	cout << endl;

	return 1;
}


