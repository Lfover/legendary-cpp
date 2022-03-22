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
		//按照二叉搜索树的规则插入新节点
		Node*& root = GetRoot();//root就是head->parent的别名
		//空树
		if (nullptr == root)
		{
			root = new Node(data, BLACK);
		}

	}
};