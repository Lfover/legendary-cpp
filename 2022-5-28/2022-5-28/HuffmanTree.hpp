
#pragma once
#include <queue>
#include <vector>
#include <functional>

//实现哈夫曼树
template<class W>
//定义哈夫曼树的节点，每个节点的属性有左子树，右子树，父节点，权值
struct HTNode
{
	HTNode(const W& w)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _weight(w)
	{}
	HTNode<W>* _left;
	HTNode<W>* _right;
	HTNode<W>* _parent;
	HTNode<W>* _weight;

};

//写一个比较左右子树的方法
template<class W>
struct Compare
{
	bool operator()(const HTNode<W>* left, const HTNode<W>* right)
	{
		return left->weight > right->weight;
	}
};

template <class W>
class HuffmanTree
{
public:
	//构造函数
	HuffmanTree()
		: root(nullptr)
	{}
	//析构函数
	~HuffmanTree()
	{
		DestoryTree(root);
	}
	//创建哈夫曼树,先选两个权值最小的节点构成一个小子树
	//然后将小子树的权值作为新的权值家去到这个群里
	//然后再选两个权值最小的节点构成新的小子树，直到没有单个节点
	//怎么创建小堆
	void CreateHuffmanTree(const W array[], size_t size, const W& invalid)
	{
		//1.先创建N个只有根节点的二叉树森林
		std::priority_queue<HTNode<W>*, std::vector<HTNode<W>*>, Compare<W>> q;
		for (size_t i = 0; i < size; i++)
		{
			//判断字符是否合法，合法才会放到优先级队列中
			if (array[i] != invaid)
				q.push(new HTNode<W>(array[i]));
		}
		//2.将权值较小的两个节点组成树
		while (q.size() > 1)
		{
			//从二叉树森林中取权值较小的两颗二叉树
			HTNode<W>* left = q.top();
			q.pop();
			HTNode<W>* right = q.top();
			q.pop();
			//以left和right作为新节点的左右汉字
			//新节点中的权值就是其左右汉字节点中的权值之和
			HTNode<W>* parent = new HTNode<W>(left->weight + right->weight);
			parent->left = left;
			parent->right = right;
			left->parent = parent;
			right->parent = parent;
			//将创建好的新二叉树插回到优先级队列中
			q.push(parent);
		}
		//当森林中只剩余一棵树，就是huffman树
		root = q.top();
	}
	void DestroyTree(HTNode<W>*& pRoot)
	{
		if (pRoot)
		{
			DestroyTree(pRoot->left);
			DestroyTree(pRoot->right);
			delete pRoot;
			pRoot = nullptr;
		}
	}
	HTNode<W>* GetRoot()
	{
		return root;
	}
private:
	HTNode<W>* root;
};
