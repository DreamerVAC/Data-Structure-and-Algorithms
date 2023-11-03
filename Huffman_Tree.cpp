#include <iostream>
using namespace std;
#define MAX_INT 65535 
class hfTree
{
private:
	struct Node
	{
		int data;
		int weight;
		int parent;
		int left;
		int right;
	};
	Node* elem;
	int length;
public:
	struct hfCode
	{
		int data;
		string code;
	};
	hfTree(int* v, int* w, int size);
	void getCode(hfCode* res);
	~hfTree();
};
hfTree::hfTree(int* v, int* w, int size)
	:length(2 * size)
{
	int min1,min2;
	int x, y;
	elem = new Node[length];
	for (int i = size; i < length; i++)
	{
		elem[i].weight = w[i - size];
		elem[i].data = v[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}
	for (int i = size - 1; i > 0; i--)
	{
		min1 = min2 = MAX_INT;
		x = y = 0;
		for (int j = i + 1; j < length; j++)
		{
			if (elem[j].parent == 0)
			{
				if (elem[j].weight < min1)
				{
					min2 = min1;
					min1 = elem[j].weight;
					y = x;
					x = j;
				}
				else if (elem[j].weight < min2)
				{
					min2 = elem[j].weight;
					y = j;
				}
			}
		}
		elem[i].weight = min1 + min2;
		elem[i].left = x;
		elem[i].right = y;
		elem[i].parent = 0;
		elem[x].parent = elem[y].parent = i;
	}
}
hfTree::~hfTree()
{
	delete[]elem;
}
void hfTree::getCode(hfCode* res)
{
	int size = length / 2;
	int p, s;
	for (int i = size; i < length; i++)
	{
		res[i - size].data = elem[i].data;
		res[i - size].code = "";
		p = elem[i].parent;
		s = i;
		while (p)
		{
			elem[p].left == s?
				res[i - size].code = '1' + res[i - size].code
				:res[i - size].code = '0' + res[i - size].code;
			s = p;
			p = elem[p].parent;
		}
	}
}
