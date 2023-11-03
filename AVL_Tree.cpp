#include <iostream>
using namespace std;
template <typename T>
struct AVLTreeNode
{
	AVLTreeNode<T>* parent;
	AVLTreeNode<T>* left;
	AVLTreeNode<T>* right;
	T value;
	int bf;
	AVLTreeNode(const T&aimvalue=T())
		:left(nullptr)
		,right(nullptr)
		,parent(nullptr)
		,value(aimvalue)
		,bf(0)
	{}
};
template <typename T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	Node* root;

	AVLTree() :root(nullptr) {}
	~AVLTree() { Destroy(root); };
	void Destroy(Node* &root);


	void RotateLeft(Node* par);
	void RotateRight(Node* par);
	void RotateLR(Node* par);
	void RotateRL(Node* par);
	bool Insert(const T& aimvalue);
	void Inorder(Node* root);
	int Height(Node* root);
	bool IsAVLTree(Node* root);
};
template<typename T>
void AVLTree<T>::Destroy(Node* &root)
{
	if (root)
	{
		Destroy(root->left);
		Destroy(root->right);
		delete root;
		root = nullptr;
	}
}
template<typename T>
void AVLTree<T>::RotateLeft(Node* par)
{
	Node* subR = par->right;
	Node* subRL = subR->left;
	Node* ppar = par->parent;
	par->right = subRL;
	if (subRL)
	{
		subRL->parent = par;
	}
	subR->left = par;
	par->parent = subR;
	subR->parent = ppar;
	if (ppar == nullptr)
	{
		root = subR;
	}
	else
	{
		if (ppar->left == par)
		{
			ppar->left = subR;
		}
		else
		{
			ppar->right = subR;
		}
	}
	par->bf = 0;
	subR->bf = 0;
}
template<typename T>
void AVLTree<T>::RotateRight(Node* par)
{
	Node* subL = par->left;
	Node* subLR = par->right;
	Node* ppar = par->parent;
	par->left = subLR;
	if (subLR)
	{
		subLR->parent = par;
	}
	subL->right = par;
	par->parent = subL;
	subL->parent = ppar;
	if (ppar == nullptr)
	{
		root = subL;
	}
	else
	{
		if (ppar->left == par)
		{
			ppar->left = subL;
		}
		else
		{
			ppar->right = subL;
		}
	}
	par->bf = 0;
	subL->bf = 0;
}
template<typename T>
void AVLTree<T>::RotateLR(Node* par)
{
	Node* subL = par->left;
	Node* subLR = subL->right;
	int BF = subLR->bf;//subLR的平衡因子
	RotateLeft(subL);
	RotateRight(par);
	if (BF == -1)
	{
		par->bf = 1;
	}
	else
	{
		par->bf = -1;
	}
}
template<typename T>
void AVLTree<T>::RotateRL(Node* par)
{
	Node* subR = par->right;
	Node* subRL = par->left;
	int BF = subRL->bf;
	RotateRight(subR);
	RotateLeft(par);
	if (BF == -1)
	{
		subR->bf = 1;
	}
	else
	{
		subR->bf = -1;
	}
}
template <typename T>
bool AVLTree<T>::Insert(const T& aimvalue)
{
	if (root == nullptr)
	{
		root = new Node(aimvalue);
		return true;
	}
	Node* cur = root;
	Node* par = nullptr;
	while (cur)
	{
		par = cur;
		if (aimvalue < cur->value)
		{
			cur = cur->left;
		}
		else if (aimvalue > cur->value)
		{
			cur = cur->right;
		}
		else
		{
			return false;
		}
	}
	cur = new Node(aimvalue);
	if (aimvalue < par->value)
	{
		par->left = cur;
	}
	else
	{
		par->right = cur;
	}
	cur->parent = par;
	while (par)
	{
		if (cur == par->left)
		{
			par->bf--;
		}
		else
		{
			par->bf++;
		}
		if (par->bf == 0)
		{
			break;
		}
		else if (par->bf == 1 || par->bf == -1)
		{
			cur = par;
			par = cur->parent;
		}
		else//可能需要双旋调整
		{
			if (par->bf == 2)
			{
				cur->bf == 1 ? RotateLeft(par) : RotateRL(par);
			}
			else
			{
				cur->bf == -1 ? RotateRight(par) : RotateLR(par);
			}
			break;
		}
	}
	return true;
}
template <typename T>
void AVLTree<T>::Inorder(Node* root)
{
	if (root)
	{
		Inorder(root->left);
		cout << root->value<<" ";
		Inorder(root->right);
	}
}
template<typename T>
int AVLTree<T>::Height(Node *root)
{
	if (root == nullptr)
	{
		return 0;
	}
	int leftHeight = Height(root->left);
	int rightHeight = Height(root->right);
	return leftHeight > rightHeight ? (leftHeight + 1) : (rightHeight + 1);
}
template <typename T>
bool AVLTree<T>::IsAVLTree(Node *root)
{
	if (root == nullptr)
	{
		return true;
	}
	int leftHeight = Height(root->left);
	int rightHeight = Height(root->right);
	if (abs(rightHeight - leftHeight) > 1 || rightHeight - leftHeight != root->bf)
	{
		cout << "Wrong!" << endl << "结点值：" << root->value << "结点平衡因子：" << root->bf << endl;
		return false;
	}
	return IsAVLTree(root->left) && IsAVLTree(root->right);
}

int main()
{
	int n;
	cout << "请输入元素个数" << endl;
	cin >> n;
	int* arr = new int[n];
	cout << "请输入元素" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	cout << "Constructing..."<<endl;
	AVLTree<int> avl;
	for (int i = 0; i < n; i++)
	{
		avl.Insert(arr[i]);
		avl.Inorder(avl.root);
		cout << endl;
	}
	if (avl.IsAVLTree(avl.root))
	{
		cout << "AVL Construction Success" << endl;
	}
	else
	{
		cout << "AVL Construction Failed" << endl;
	}
	return 0;
}