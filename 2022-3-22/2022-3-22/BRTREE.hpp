#pragma once
#include <iostream>
using namespace std;
//创建联合体，代表结点颜色
enum Color
{
	RED,
	BLACK
};

//红黑树定义
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
//创建红黑树的迭代器
template <class T>
struct RBTreeItreator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;
public:
	RBTreeItreator(Node* n = nullptr)
		:node(n)
	{}
	//具有指针类似的方法
	T& operator*()
	{
		return node->data;
	}
	T* operator->()
	{
		return &(operator*());
	}
	//要能够移动
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
	//找当前迭代器的下一个位置
	void Increment()
	{
		if (node->right)
		{
			//到node的右子树中找最左侧的结点
			node = node->right;
			while (node->left)
			{
				node = node->left;
			}
		}
		else
		{
			//node的右子树不存在---应该到node的双亲中查找
			Node* parent = node->parent;
			while (node == parent->right)
			{
				node = parent;
				parent = node->parent;
			}
			//当node是parent的左孩子时，循环终止
			//注意：根节点没有右子树的情况--而迭代器刚好处在根的位置
			if (node->right != parent)
			{
				node = parent;
			}
		}
	}
		//找当前迭代器的前一个位置
		void Decrement()
		{
			//找比当前迭代器小的左右结点中最大的
			if (node == node->parent->parent && RED == node->color)
			{
				//node在end位置
				node = node->right;
			}
			else if (node->left)
			{
				//到node的左子树中找最右侧的结点
				node = node->left;
				while (node->right)
				{
					node = node->right;
				}
			}
			else
			{
				//右子树不存在---应该到node的双亲中找比node小的结点
				Node* parent = node->parent;
				while (node == parent->left)
				{
					//说明node比其双亲还要小，需要继续往上查找
					node = parent;
					parent = node->parent;
				}
				node = parent;
			}
		}
		//能够比较
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
//假设：红黑树中值是唯一的
//T：表示红黑树中放置元素的类型
//KOFD:表示如何从T中提取key
template<class T, class KOFD>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T> iterator;
public:
	//构造函数
	RBTree()
		:_size(0)
	{
		head = new Node();
		head->left = head;
		head->right = head;
		head->parent = nullptr;//红黑树中没有任何结点
	}
	//析构函数
	~RBTree()
	{
		Destroy(GetRoot());
		delete head;
		head = nullpter;
		_size = 0;
	}
	////////////////////////////////////////////////////////////////////////////
	//迭代器
	iterator begin()
	{
		return iterator(head->left);
	}
	iterator end()
	{
		return iterator(head);
	}
	/////////////////////////////////////////////////////////////////////////////////////////
	//容量相关的操作
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
		//1.按照二叉搜索树的规则插入结点
		Node*& root = GetRoot();//roor就是head->parent的别名

		//空树
		if (nullptr == root)
		{
			root = new Node(data, BLACK);
			root->parent = head;
			head->left = root;
			head->right = root;
			_size = 1;
			return make_pair(iterator(root), true);
		}

		//找待插入结点在红黑树当中的位置
		Node* cur = root;
		Node* parent = head;
		KOFD key;
		while (cur)
		{
			parent = cur;
			//注意：需要使用data的Key来进行比较
			if (key(data) < key(cur->data))
				cur = cur->left;
			else if (key(data) > key(cur->data))
				cur = cur->right;
			else
				return make_pair(iterator(cur), false);
		}

		//插入新节点
		Node* newnode = new Node(data);
		cur = newnode;
		if (key(data) < key(parent->data))
			parent->left = cur;
		else
			parent->right = cur;
		cur->parent = parent;

		//新系欸但那默认是红色的
		//2.检查是否违反性质3：检测新插入结点与其双亲结点的颜色是否都为红色
		while (parent != head && RED == parent->color)
		{
			//违反性质3：cur和parent两个结点的颜色都是红色
			//..
			//为什么此处的祖父节点不需要判空？
			//parent!=head说明parent一定是树中的有效结点
			//RED == parent = color 说明parent一定不是根节点，说明parent的双亲一定是存在的
			//grandFather一定不为空
			Node* grandFather = parent->parent;
			if (parent == grandFather->left)
			{
				Node* uncle = grandFather->right;
				if (uncle && RED == uncle->color)
				{
					//情况一：叔叔结点存在且为红
					parent->color = BLACK;
					uncle->color = BLACK;
					grandFather->color = RED;
					cur = grandFather;
					parent = cur->parent;
				}
				else
				{
					//叔叔结点不存在|| 叔叔结点存在且为黑色---情况二，情况三
					if (cur == parent->right)
					{
						//情况三
						RotateLeft(parent);
						std::swap(parent, cur);
					}
					//情况二
					grandFather->color = RED;
					parent->color = BLACK;
					RotateRight(grandFather);
				}
			}
			else
			{
				//课件中情况一二三的反情况：双亲在祖父的右侧
				Node* uncle = grandFather->left;
				if (uncle && RED == uncle->color)
				{
					//课件中情况一的反情况
					parent->color = BLACK;
					uncle->color = BLACK;
					grandFather->color = RED;
					cur = grandFather;
					parent = cur->parent;
				}
				else
				{
					//情况二和情况三的反情况
					if (cur == parent->left)
					{
						//情况三的反情况
						RotateRight(parent);
						std::swap(parent, cur);
					}
					//情况二的反情况
					parent->color = BLACK;
					grandFather->color = RED;
					RotateLeft(grandFather);
				}
			}
		}

		//新节点插入之后，红色树中的最大或者最小结点发生变化
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
		//空树也是红黑树
		Node* root = GetRoot();
		if (nullptr == root)
			return true;
		//树非空---主要用红黑树的性质
		if (BLACK != root->color)
		{
			cout << "违反性质2：根节点不是黑色的" << endl;
			return false;
		}
		//性质3：没有连在一起的红色结点
		//性质4：每条路径中黑色结点的个数相同
		//可以放进来一起进行检验
		//在验证性质4时，要求红黑树每条路径中黑色结点的个数，然后验证黑色结点的个数是否相等
		//在该过程中，会拿到所有的结点，而红黑树采用孩子双亲表示法来表示的，因此也可以拿到该结点的双亲，顺便就将将性质3检测了
		//性质4检测原理
		//1.任意求出一条路径中黑色结点的个数----简单起见：求最左侧路径中黑色的个数blackCout
		//2.在求出其他路径中黑色节点的个数，检验其是否相同
		size_t blackCount = 0;
		Node* cur = root;
		while (cur)
		{
			if (BLACK == cur->color)
				blackCount++;
			cur = cur->left;
		}

		size_t = pathBlackCout = 0;//用来保障单条路径中黑色结点的个数
		return _IsValidRBTree(root, pathBlackCount, blackCount);
	}
private:
	bool _IsValidRBTree(Node* root, size_t pathBlackCount, const size_t blackCount)
	{
		if (nullptr == root)
			return true;

	//说明在一条路径中找到一个黑色节点
		if (BLACK == root->color)
		{
			pathBlackCount++;
		}
		Node* parent = root->parent;
		//parent != head:说明root一定不是红黑树的根节点，parent一定是红黑树中有效节点
		if (parent != head && RED == parent->color && RED == root->color)
		{
			cout << "违反性质3：存在连在一起的红色节点" << endl;
			return false;
		}

		//root是一个叶子节点，一条路已经走到头了
		if (nullptr == root->left && nullpter == root->right)
		{
			if (pathBlackCount != blackCount)
			{
				cout << "违反性质4：路径中黑色结点的个数不同的" << endl;
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
		//按照二叉搜索树的规则插入新节点
		Node*& root = GetRoot();//root就是head->parent的别名
		//空树
		if (nullptr == root)
		{
			root = new Node(data, BLACK);
		}

	}
};