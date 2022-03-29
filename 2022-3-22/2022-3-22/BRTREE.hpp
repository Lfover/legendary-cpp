#pragma once
#include <iostream>
using namespace std;
//���������壬��������ɫ
enum Color
{
	RED,
	BLACK
};

//���������
template <class T>
struct RBTreeNode
{
	RBTreeNode(const T& x = T(), Color c = RED)
		:left(nullptr)
		, right(nullptr)
		, parent(nullptr)
		, data(x)
		, color(c)
	{}
	RBTreeNode<T>* left;
	RBTreeNode<T>* right;
	RBTreeNode<T>* parent;
	T data;
	Color color;
};
//����������ĵ�����
template <class T>
struct RBTreeItreator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;
public:
	RBTreeItreator(Node* n = nullptr)
		:node(n)
	{}
	//����ָ�����Ƶķ���
	T& operator*()
	{
		return node->data;
	}
	T* operator->()
	{
		return &(operator*());
	}
	//Ҫ�ܹ��ƶ�
	Self& operator++()
	{
		Increment();
		return *this;
	}
	Self operator++(int)
	{
		Self temp(*this);
		Increment();
		return temp;
	}
	Self& operator--()
	{
		Decrement();
		return *this;
	}
	Self operator--(int)
	{
		Self temp(*this);
		Decrement();
		return temp;
	}
	//�ҵ�ǰ����������һ��λ��
	void Increment()
	{
		if (node->right)
		{
			//��node�����������������Ľ��
			node = node->right;
			while (node->left)
			{
				node = node->left;
			}
		}
		else
		{
			//node��������������---Ӧ�õ�node��˫���в���
			Node* parent = node->parent;
			while (node == parent->right)
			{
				node = parent;
				parent = node->parent;
			}
			//��node��parent������ʱ��ѭ����ֹ
			//ע�⣺���ڵ�û�������������--���������պô��ڸ���λ��
			if (node->right != parent)
			{
				node = parent;
			}
		}
	}
		//�ҵ�ǰ��������ǰһ��λ��
		void Decrement()
		{
			//�ұȵ�ǰ������С�����ҽ��������
			if (node == node->parent->parent && RED == node->color)
			{
				//node��endλ��
				node = node->right;
			}
			else if (node->left)
			{
				//��node���������������Ҳ�Ľ��
				node = node->left;
				while (node->right)
				{
					node = node->right;
				}
			}
			else
			{
				//������������---Ӧ�õ�node��˫�����ұ�nodeС�Ľ��
				Node* parent = node->parent;
				while (node == parent->left)
				{
					//˵��node����˫�׻�ҪС����Ҫ�������ϲ���
					node = parent;
					parent = node->parent;
				}
				node = parent;
			}
		}
		//�ܹ��Ƚ�
		bool operator!=(const Self& s)const
		{
			return node != s.node;
		}
		bool operator==(const Self& s)const
		{
			return node == s.node;
		}
	private:
		Node* node;
};
//���裺�������ֵ��Ψһ��
//T����ʾ������з���Ԫ�ص�����
//KOFD:��ʾ��δ�T����ȡkey
template<class T, class KOFD>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T> iterator;
public:
	//���캯��
	RBTree()
		:_size(0)
	{
		head = new Node();
		head->left = head;
		head->right = head;
		head->parent = nullptr;//�������û���κν��
	}
	//��������
	~RBTree()
	{
		Destroy(GetRoot());
		delete head;
		head = nullpter;
		_size = 0;
	}
	////////////////////////////////////////////////////////////////////////////
	//������
	iterator begin()
	{
		return iterator(head->left);
	}
	iterator end()
	{
		return iterator(head);
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//������صĲ���
	size_t size()const
	{
		return _size;
	}

	bool empty()const
	{
		return nullptr == head->parent;
	}

	pair<iterator, bool> Insert(const T& data)
	{
		//1.���ն����������Ĺ��������
		Node*& root = GetRoot();//roor����head->parent�ı���

		//����
		if (nullptr == root)
		{
			root = new Node(data, BLACK);
			root->parent = head;
			head->left = root;
			head->right = root;
			_size = 1;
			return make_pair(iterator(root), true);
		}

		//�Ҵ��������ں�������е�λ��
		Node* cur = root;
		Node* parent = head;
		KOFD key;
		while (cur)
		{
			parent = cur;
			//ע�⣺��Ҫʹ��data��Key�����бȽ�
			if (key(data) < key(cur->data))
				cur = cur->left;
			else if (key(data) > key(cur->data))
				cur = cur->right;
			else
				return make_pair(iterator(cur), false);
		}

		//�����½ڵ�
		Node* newnode = new Node(data);
		cur = newnode;
		if (key(data) < key(parent->data))
			parent->left = cur;
		else
			parent->right = cur;
		cur->parent = parent;

		//��ϵ�G����Ĭ���Ǻ�ɫ��
		//2.����Ƿ�Υ������3������²���������˫�׽�����ɫ�Ƿ�Ϊ��ɫ
		while (parent != head && RED == parent->color)
		{
			//Υ������3��cur��parent����������ɫ���Ǻ�ɫ
			//..
			//Ϊʲô�˴����游�ڵ㲻��Ҫ�пգ�
			//parent!=head˵��parentһ�������е���Ч���
			//RED == parent = color ˵��parentһ�����Ǹ��ڵ㣬˵��parent��˫��һ���Ǵ��ڵ�
			//grandFatherһ����Ϊ��
			Node* grandFather = parent->parent;
			if (parent == grandFather->left)
			{
				Node* uncle = grandFather->right;
				if (uncle && RED == uncle->color)
				{
					//���һ�������������Ϊ��
					parent->color = BLACK;
					uncle->color = BLACK;
					grandFather->color = RED;
					cur = grandFather;
					parent = cur->parent;
				}
				else
				{
					//�����㲻����|| �����������Ϊ��ɫ---������������
					if (cur == parent->right)
					{
						//�����
						RotateLeft(parent);
						std::swap(parent, cur);
					}
					//�����
					grandFather->color = RED;
					parent->color = BLACK;
					RotateRight(grandFather);
				}
			}
			else
			{
				//�μ������һ�����ķ������˫�����游���Ҳ�
				Node* uncle = grandFather->left;
				if (uncle && RED == uncle->color)
				{
					//�μ������һ�ķ����
					parent->color = BLACK;
					uncle->color = BLACK;
					grandFather->color = RED;
					cur = grandFather;
					parent = cur->parent;
				}
				else
				{
					//�������������ķ����
					if (cur == parent->left)
					{
						//������ķ����
						RotateRight(parent);
						std::swap(parent, cur);
					}
					//������ķ����
					parent->color = BLACK;
					grandFather->color = RED;
					RotateLeft(grandFather);
				}
			}
		}

		//�½ڵ����֮�󣬺�ɫ���е���������С��㷢���仯
		root->color = BLACK;
		head->left = LeftMost();
		head->right = RightMost();
		_size++;
		return make_pair(iterator(newnode), true);
	}

	void Swap(RBTree<T, KOFD>& t)
	{
		std::swap(head, t.head);
		std::swap(_size, t._size);
	}

	void Clear()
	{
		Destroy(GetRoot());
		_size = 0;
	}

	iterator Find(const T& data)
	{
		Node* cur = GetRoot();
		KOFD key;
		while (cur)
		{
			if (key(data) == key(cur->data))
				return iterator(cur);
			else if (key(data) < key(cur->data))
				cur = cur->left;
			else
				cur = cur->right;
		}
		return end();
	}

	void InOrder()
	{
		InOrder(GetRoot());
	}

	bool IsValidRBTree()
	{
		//����Ҳ�Ǻ����
		Node* root = GetRoot();
		if (nullptr == root)
			return true;
		//���ǿ�---��Ҫ�ú����������
		if (BLACK != root->color)
		{
			cout << "Υ������2�����ڵ㲻�Ǻ�ɫ��" << endl;
			return false;
		}
		//����3��û������һ��ĺ�ɫ���
		//����4��ÿ��·���к�ɫ���ĸ�����ͬ
		//���ԷŽ���һ����м���
		//����֤����4ʱ��Ҫ������ÿ��·���к�ɫ���ĸ�����Ȼ����֤��ɫ���ĸ����Ƿ����
		//�ڸù����У����õ����еĽ�㣬����������ú���˫�ױ�ʾ������ʾ�ģ����Ҳ�����õ��ý���˫�ף�˳��ͽ�������3�����
		//����4���ԭ��
		//1.�������һ��·���к�ɫ���ĸ���----��������������·���к�ɫ�ĸ���blackCout
		//2.���������·���к�ɫ�ڵ�ĸ������������Ƿ���ͬ
		size_t blackCount = 0;
		Node* cur = root;
		while (cur)
		{
			if (BLACK == cur->color)
				blackCount++;
			cur = cur->left;
		}

		size_t = pathBlackCout = 0;//�������ϵ���·���к�ɫ���ĸ���
		return _IsValidRBTree(root, pathBlackCount, blackCount);
	}
private:
	bool _IsValidRBTree(Node* root, size_t pathBlackCount, const size_t blackCount)
	{
		if (nullptr == root)
			return true;

	//˵����һ��·�����ҵ�һ����ɫ�ڵ�
		if (BLACK == root->color)
		{
			pathBlackCount++;
		}
		Node* parent = root->parent;
		//parent != head:˵��rootһ�����Ǻ�����ĸ��ڵ㣬parentһ���Ǻ��������Ч�ڵ�
		if (parent != head && RED == parent->color && RED == root->color)
		{
			cout << "Υ������3����������һ��ĺ�ɫ�ڵ�" << endl;
			return false;
		}

		//root��һ��Ҷ�ӽڵ㣬һ��·�Ѿ��ߵ�ͷ��
		if (nullptr == root->left && nullpter == root->right)
		{
			if (pathBlackCount != blackCount)
			{
				cout << "Υ������4��·���к�ɫ���ĸ�����ͬ��" << endl;
				return false;
			}
		}
		return _IsValidRBTree(root->left, pathBlackCount, blackCount) && _IsValidRBTree(root->right, pathBlackCount, blackCount);
	}
	void RotateLeft(Node* parent)
	{
		Node
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