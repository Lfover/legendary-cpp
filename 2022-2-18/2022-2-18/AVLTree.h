#pragma once
template<class T>
struct AVLTreeNode
{
	//拷贝构造函数
	AVLTreeNode(const T& x = T())
		:left(nullptr)
		, right(nullptr)
		, data(x)
		, _bf(0)
	{}
	AVLTreeNode<T>* left;
	AVLTreeNode<T>* right;
	T _data;
	int _bf;///bf是平衡因子
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
		//1.按照二叉搜索树的规则插入新节点
		if (nullptr == _root)
		{
			_root = new Node(data);
			return true;
		}
		//找待插入结点在二叉搜索树中的位置--并要保存双亲
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
		//插入新节点
		cur = new Node(data);
		if (data < parent->_data)
			parent->left = cur;
		else parent->right = cur;
		//新节点插入后一定会对双亲结点的平衡性造成影响
		//需要调整parent的平衡因子
		while ()
		{
			if (cur == parent->left)//parent 右子树高度没有变， 左子树的高度增加一层
				parent->_bf--;
			else
				parent->_bf++;
			if (0 == parent->_bf)
				break;
			else if (-1 == parnet->_bf || 1 == parent->_bf)
			{
				//一parent 为根的子树的高度增加一层，需要继续往上更新
				cur == parent;
				parent = cur->parent;
			}
			else
			{
				//parent的平衡因子2 || -2
				//对parent为根的二叉树进行旋转处理
			}
		}
		return true;

	}
private: 
	//右单旋
	void RotateRright(Node* parent)
	{
		Node* subL = parent->left;
		Node* subLR = subL->right;  
		parent->left = subLR;
		//避免左单支的场景
		if (subLR)
			subLR->parent = parent;
		subL->right = parent;
		//因为parent可能是某个结点的子树，因此在更新parent的双亲钱必须将其之前的双亲结点记录
		Node* pparent = parent->parent;
		parent->parent = subL;
		subL->parent = pparent;

		//parent可能是根节点，需要修改_root
		//parent也可能是一颗子树：需要修改 pparent的左子树或是右子树
		if (nullptr == pparent)
		{
			//旋转之前parent是根节点
			_root = subL;
		}
		else
		{
			//parent是某个结点的子树
			if (parent == pparent->left)
				pparent->left = subL;
			else
				pparent->right = subL;   
		}
	}
	 //左单旋
	void RotateLeft(Node* parent)
	{

	}

private:

	AVLTreeNode<T>* _root;
};