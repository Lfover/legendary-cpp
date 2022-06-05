
#pragma once
#include <queue>
#include <vector>
#include <functional>

//ʵ�ֹ�������
template<class W>
//������������Ľڵ㣬ÿ���ڵ���������������������������ڵ㣬Ȩֵ
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

//дһ���Ƚ����������ķ���
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
	//���캯��
	HuffmanTree()
		: root(nullptr)
	{}
	//��������
	~HuffmanTree()
	{
		DestoryTree(root);
	}
	//������������,��ѡ����Ȩֵ��С�Ľڵ㹹��һ��С����
	//Ȼ��С������Ȩֵ��Ϊ�µ�Ȩֵ��ȥ�����Ⱥ��
	//Ȼ����ѡ����Ȩֵ��С�Ľڵ㹹���µ�С������ֱ��û�е����ڵ�
	//��ô����С��
	void CreateHuffmanTree(const W array[], size_t size, const W& invalid)
	{
		//1.�ȴ���N��ֻ�и��ڵ�Ķ�����ɭ��
		std::priority_queue<HTNode<W>*, std::vector<HTNode<W>*>, Compare<W>> q;
		for (size_t i = 0; i < size; i++)
		{
			//�ж��ַ��Ƿ�Ϸ����Ϸ��Ż�ŵ����ȼ�������
			if (array[i] != invaid)
				q.push(new HTNode<W>(array[i]));
		}
		//2.��Ȩֵ��С�������ڵ������
		while (q.size() > 1)
		{
			//�Ӷ�����ɭ����ȡȨֵ��С�����Ŷ�����
			HTNode<W>* left = q.top();
			q.pop();
			HTNode<W>* right = q.top();
			q.pop();
			//��left��right��Ϊ�½ڵ�����Һ���
			//�½ڵ��е�Ȩֵ���������Һ��ֽڵ��е�Ȩֵ֮��
			HTNode<W>* parent = new HTNode<W>(left->weight + right->weight);
			parent->left = left;
			parent->right = right;
			left->parent = parent;
			right->parent = parent;
			//�������õ��¶�������ص����ȼ�������
			q.push(parent);
		}
		//��ɭ����ֻʣ��һ����������huffman��
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
