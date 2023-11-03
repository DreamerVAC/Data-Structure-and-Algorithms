#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#include<iostream>
#include<iomanip>

using namespace std;

class CRingQueue {
private:
	int iLen;
	int iSize;
	int iFront;
	int iRear;
	int* pArr;
public:
	CRingQueue(int size) {//创建队列
		iSize = size;
		iFront = iRear = iLen = 0;
		pArr = new int[size];
	}
	~CRingQueue() { free(pArr); pArr = NULL; }/*删除队列*///队头队尾操作
	void QueueRearInc() { iRear++; iRear = iRear % iSize; }
	void QueueFrontInc() { iFront++; iFront = iFront % iSize; }
	bool IsEmpty() { return (iLen == 0); }/*队列判空*/
	bool IsFull() { return (iLen >= iSize); }/*队列判满*/
	int Size() { return iLen; }/*返回队列现有长度*/
	//往队尾放入元素
	bool EnQueue(int element) {
		if (IsFull()) {
			cout << "Error : OverFlow !" << endl;
			return false;
		}
		pArr[iRear] = element; QueueRearInc(); iLen++;
		return true;
	}
	int Front() {
		if (IsEmpty())			return 0x80000000;
		return pArr[iFront];
	}
	int Rear() {
		if (IsEmpty())			return 0x7FFFFFFF;
		return pArr[iRear];
	}
	//删除队列第一个元素
	bool DeQueue(int& element) {
		if (IsEmpty()) {
			cout << "Error : UnderFlow" << endl;
			return false;
		}
		element = pArr[iFront];
		QueueFrontInc();
		iLen--;
		return true;
	}
	//打印队列中的全部元素
	void Disp() {
		if (!IsEmpty())	cout << "Head : " << Front() << ", Tail : " << Rear() << endl;
		int iHead = iFront;
		for (int i = 0; i < iLen; i++) {
			cout << setw(4) << pArr[iHead++ % iSize];
		}
		cout << endl;
	}
};
CRingQueue Producer(int* items, int len)
{
	CRingQueue target(len);
	for (int i = 0; i < len; i++)
	{
		target.EnQueue(items[i]);
		target.Disp();
	}
	return target;
}
void Consumer(CRingQueue target)
{
	while (!target.IsEmpty())
	{
		int ele = 1;
		target.DeQueue(ele);
		target.Disp();
	}
}
int main()
{
	int len;
	cout << "Please input the capacity" << endl;
	cin >> len;
	int* items = new int[len];
	cout << "Please input the elements" << endl;
	for (int i = 0; i < len; i++)
	{
		cin >> items[i];
	}
	CRingQueue target = Producer(items, 5);
	Consumer(target);
	return 0;
}