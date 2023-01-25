#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
【题目】
给定一个长度为偶数的数组 arr，长度记为 2×N。前 N 个为左部分，后 N 个为右部分。arr 就可以表示为{L1,L2,..,Ln,R1,R2,..,Rn}，请将数组调整成{R1,L1,R2,L2,..,Rn,Ln}的样子。
【举例】
arr = {1,2,3,4,5,6}，调整之后为{4,1,5,2,6,3}。
进阶问题:给定一个数组 arr，请将数组调整为依次相邻的数字总是先<=、再>=的关系，并
交替下去。比如数组中有五个数字，调整成{a,b,c,d,e}，使之满足 a<=b>=c<=d>=e 【要求】
原问题要求时间复杂度为 O(N)，额外空间复杂度为 O(1)。 进阶问题要求时间复杂度为 O(NlogN)，额外空间复杂度为 O(1)。
*/

template<int N>
int modifyIndex1(int i, int len)
{
	if (i <= N)
		return 2 * i;
	else
		return 2 * (i - int(len/2)) -1;
}

int modifyIndex2(int i, int len)
{
	return (2 * i) % (len + 1); 
}

/*
这里直接把完美洗牌问题论文中的结论告诉读者，有兴趣的读者可以去证明。如果 数组长度为 2*N==(3^k)-1，那么出发位置有 k 个，依次为 1,3,9,..3^(k-1)，k≥1。比如数组长度为 2 时，2=31-1，所以出发位置只有 1 个，也就是 1 位置 30。比如数组长度为 8 时，8=32-1，所以 出发位置有 2 个，依次为 1,3。比如数组长度为 26 时，26=33-1，所以出发位置有 3 个，依次为 1,3,9。
*/

void rotate(vector<int>& arr, int L, int M, int R)
{
	reverse(arr.begin() + L, arr.begin() + M);
	reverse(arr.begin() + M + 1, arr.begin() + R);
	reverse(arr.begin() + L, arr.begin() + R);
}

void cycles(vector<int>& arr, int start, int len, int k)
{
	// trigger alwasy from 1
	for (int i = 0, trigger = 1; i < k; i++, trigger*=3)
	{
		int pre = arr[trigger + start - 1];
		int cur = modifyIndex2(trigger, len);
		while (cur != trigger)
		{
			int tmp = arr[cur + start - 1];
			arr[cur + start - 1] = pre;
			pre = tmp;
			cur = modifyIndex2(cur, len);
		}
		arr[cur + start - 1] = pre;
	}
}

void shuffle(vector<int>& arr, int L , int R)
{
	while (R - L + 1 > 0)
	{
		int len = R - L + 1;
		int base = 3;
		int k = 1;
		// find largest k. 3^k <= len+1
		while (base <= (len + 1) / 3) {
			base *= 3;
			k++;
		}
		// handle base - 1 block
		int half = (base - 1) / 2;
		int mid = (L + R) / 2;
		// rotate [L+half...mid] arr[mid+1...mid+half]
		rotate(arr, L + half, mid, mid + half);
		cycles(arr, L, base - 1, k);
		L = k + base - 1;
	}
}

void shuffle(vector<int>& arr)
{
	if (arr.empty() || (arr.size() & 1) != 0)
		shuffle(arr, 0, arr.size() - 1);
}

void wiggleSort(vector<int>& arr)
{
	if (arr.empty())
		return;
	sort(arr.begin(), arr.end());
	if (arr.size() & 1)
		shuffle(arr, 1, arr.size() - 1);
	else
	{
		shuffle(arr, 0, arr.size() - 1);
		for (int i = 0; i != arr.size(); i += 2)
		{
			int tmp = arr[i];
			arr[i] = arr[i+1];
			arr[i+1] = tmp;
		}
	}
}

int main()
{
	vector<int> a {1,2,3,4,5,6,7,8,9};
	shuffle(a);
	for (int i : a)
		cout << i << ", ";
	cout << endl;

	vector<int> a1{1,2,3,4,5,6,7,8,9};
	wiggleSort(a1);
	for (int i : a1)
		cout << i << ", ";
	cout << endl;

	return 1;
}
