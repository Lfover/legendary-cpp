#include <iostream>
using namespace std;
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	RBTree()
	{
		head = new Node();
		head->left = head;
		head->right = head;
		head->parent = nullptr;
	}
	bool Insert(const T& data)
	{
		//���ն����������Ĺ�������½ڵ�
		Node*& root = GetRoot();//root����head->parent�ı���
		//����
		if (nullptr == root)
		{
			root = new Node(data, BLACK);
		}

	}
};