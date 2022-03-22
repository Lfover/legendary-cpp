#pragma once
template<class T>
struct AVLTreeNode
{
	//�������캯��
	AVLTreeNode(const T& x = T())
		:left(nullptr)
		, right(nullptr)
		, data(x)
		, _bf(0)
	{}
	AVLTreeNode<T>* left;
	AVLTreeNode<T>* right;
	T _data;
	int _bf;///bf��ƽ������
};

template <class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		:_root(nullptr)
	{

	}
	bool Insert(const T& data)
	{
		//1.���ն����������Ĺ�������½ڵ�
		if (nullptr == _root)
		{
			_root = new Node(data);
			return true;
		}
		//�Ҵ��������ڶ����������е�λ��--��Ҫ����˫��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (data < cur->_data)
				cur = cur->left;
			else if (data > cur->_data)
				cur = cur->right;
			else
				return false;
		}
		//�����½ڵ�
		cur = new Node(data);
		if (data < parent->_data)
			parent->left = cur;
		else parent->right = cur;
		//�½ڵ�����һ�����˫�׽���ƽ�������Ӱ��
		//��Ҫ����parent��ƽ������
		while ()
		{
			if (cur == parent->left)//parent �������߶�û�б䣬 �������ĸ߶�����һ��
				parent->_bf--;
			else
				parent->_bf++;
			if (0 == parent->_bf)
				break;
			else if (-1 == parnet->_bf || 1 == parent->_bf)
			{
				//һparent Ϊ���������ĸ߶�����һ�㣬��Ҫ�������ϸ���
				cur == parent;
				parent = cur->parent;
			}
			else
			{
				//parent��ƽ������2 || -2
				//��parentΪ���Ķ�����������ת����
			}
		}
		return true;

	}
private: 
	//�ҵ���
	void RotateRright(Node* parent)
	{
		Node* subL = parent->left;
		Node* subLR = subL->right;  
		parent->left = subLR;
		//������֧�ĳ���
		if (subLR)
			subLR->parent = parent;
		subL->right = parent;
		//��Ϊparent������ĳ����������������ڸ���parent��˫��Ǯ���뽫��֮ǰ��˫�׽���¼
		Node* pparent = parent->parent;
		parent->parent = subL;
		subL->parent = pparent;

		//parent�����Ǹ��ڵ㣬��Ҫ�޸�_root
		//parentҲ������һ����������Ҫ�޸� pparent������������������
		if (nullptr == pparent)
		{
			//��ת֮ǰparent�Ǹ��ڵ�
			_root = subL;
		}
		else
		{
			//parent��ĳ����������
			if (parent == pparent->left)
				pparent->left = subL;
			else
				pparent->right = subL;   
		}
	}
	 //����
	void RotateLeft(Node* parent)
	{

	}

private:

	AVLTreeNode<T>* _root;
};