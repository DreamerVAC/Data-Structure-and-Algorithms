#include <iostream>
#include <algorithm>
using namespace std;

class MinHeap
{
private:
	int* data;
	int sz;
	int capacity;
protected:
	void swim(int index);
	void sink(int index);
public:
	MinHeap(int _cap);
	~MinHeap();

	void push(const int val);
	void pop();
	int top() const;
	int size() const;
	void printHeap() const;
};
void MinHeap::swim(int index)
{
	while (data[index] < data[(index - 1) / 2] && index>0)
	{
		swap(data[index], data[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}
void MinHeap::sink(int index)
{
	int par = index;
	while (2 * par + 1 < sz)
	{
		int son = 2 * par + 1;//index的左子节点
		if (son < sz - 1 && data[son + 1] < data[son])
		{
			++son;
		}
		if (data[par] < data[son])
		{
			break;
		}
		swap(data[par], data[son]);
		par = son;
	}
}
MinHeap::MinHeap(int _cap) :
	sz(0),
	capacity(_cap)
{
	data = new int[capacity];
}
MinHeap::~MinHeap()
{
	delete[]data;
}

void MinHeap::push(const int val)
{
	if (sz == capacity)
	{
		cout << "Full!" << endl;
		return;
	}
	data[sz] = val;
	swim(sz);
	sz++;
	cout << "Push success. Heap size: " << sz << endl;
}
void MinHeap::pop()
{
	if (sz == 0)
	{
		cout << "Empty!" << endl;
		return;
	}
	swap(data[0], data[sz - 1]);
	--sz;
	sink(0);
	cout << "Pop success. Heap size: " << sz << endl;
}
int MinHeap::top() const
{
	if (sz == 0)
	{
		cout << "Empty!" << endl;
		return -1;
	}
	return data[0];
}
int MinHeap::size() const
{
	return sz;
}
void MinHeap::printHeap() const
{
	if (sz == 0)
	{
		cout << "Empty!" << endl;
		return;
	}
	cout << "Heap: ";
	for (int i = 0; i < sz; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}
int main()
{
	int _cap;
	cout << "请输入所需小顶堆大小" << endl;
	cin >> _cap;
	MinHeap heap = MinHeap(_cap);
	cout << "请输入数据" << endl;
	int val;
	cout << "Pushing" << endl;
	while (scanf("%d", &val) != EOF)
	{
		heap.push(val);
		heap.printHeap();
	}
	cout << "Popping..." << endl;
	while (heap.top() > 0)
	{
		heap.pop();
		heap.printHeap();
	}
	return 0;
}