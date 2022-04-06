#pragma once
#include <vector>
#include "Common.h"
#include <iostream>
using namespace std;
//��ϣͰ�й������һ��һ��������
template<class T>
struct HashBucketNode
{
	HashBucketNode(const T& x = T())
		:next(nullptr)
		, data(x)
	{}
	HashBucketNode<T>* next;
	T data;
};
//ǰ������
template<class T, class KOFD, class DToI = DToIntDef<T>>
class HashBucket;

template<class T, class DToI = DToIntDef<T>>
struct HashBucketIterator
{
	typedef HashBucketNode<T> Node;
	typedef HashBucketIterator<T, DToI> Self;
public:
	HashBucketIterator(Node* node = nullptr, HashBucket<T, DToI>* _ht = nullptr)
		:_node(node)
		, _ht(_ht)
	{}
	//����ָ�����ƵĲ���
	T& operator*()
	{
		return _node->data;
	}
	T* operator->()
	{
		return &(operator*());
	}
	//������Ҫ�ܹ��ƶ�
	//������ֻ�ܵ���
	Self& operator++()
	{
		Self temp(*this);
		Next();
		return temp;
	}
	//��Ҫ�ܹ��Ƚ�
	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}
	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}
private:
	void Next()
	{
		if (_node->next)
		{
			_node = _node->next;
		}
		else
		{
			//node�ǵ�ǰ�����е����һ�����
			//��_node����Ͱ����һ���ǿ�Ͱ
			//����֪����ǰ�������һ��Ͱ��
			size_t bucketNo = _ht->HashFunc(_ht->BucketCount(), _node->data) + 1;
			for (; bucketNo < _ht->BucketCount(); ++bucketNo)
			{
				_node = _ht->_table[bucketNo];
				if (_node)
				{
					return;
				}
			}
			_node = nullptr; 
		}
	}


private:
	Node* _node;
	HashBucket<T, DToI>* _ht;
};


template<class T, class DToI>
class HashBucket
{
	friend HashBucketIterator <T, DToI>;
	typedef HashBucketNode<T> Node;
public:
	typedef HashBucketIterator<T, DToI> iterator;
public:
	//���캯��
	HashBucket(size_t capacity = 10)
		:_table(GetNextPrime(capacity))
		, _size(0)
	{}
	//��������
	~HashBucket()
	{
		Clear();
	}
	iterator begin()
	{
		//�ڵ�һ���ǿ�Ͱ�׽��λ��
		for (size_t bucketNo = 0; bucketNo < BucketCount(); ++bucketNo)
		{
			if (_table[bucketNo])
			{
				return iterator(_table[bucketNo], this);
			}
		}
		return end();
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
	//ֻ���Բ���Ψһ��Ԫ��
	pair<iterator, bool> InsertUnique(const T& data)
	{
		CheckCapacity();
		//1.ͨ����ϣ��������Ԫ�����ڵ�Ͱ�� 
		size_t bucketNo = HashFunc(_table.capacity(), data);
		//2.���data�Ƿ���bucketNoͰ�д���
		//ʵ����ֻ��Ҫ��bucketNo��Ӧ�������в���data�Ƿ����
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (data == cur->data)
				return make_pair(iterator(cur, this), false);
			cur = cur->next;
		}
		//3.�����½�㣬ͷ��
		cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;
		return make_pair(iterator(cur, this), true);
	}
	//���Բ����ظ���Ԫ��
	bool InsertEqual(const T& data)
	{
		CheckCapacity();
		//1.ͨ����ϣ��������Ԫ�����ڵ�Ͱ�� 
		size_t bucketNo = HashFunc(data);
		
		//2.�����½�㣬ͷ��
		Node* cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;
		return true;
	}

	//ɾ��
	//�ڹ�ϣ����ɾ��ֵΪdata��Ԫ�أ�����ֵ���ͱ�ʾɾ�����ֵΪdata�Ľ��ĸ���

	size_t EraseUnique(const T& data)
	{
		//1.ͨ����ϣ������data���ڵ�Ͱ��
		size_t bucketNo = HashFunc(data);
		Node* cur = _table[bucketNo];
		Node* prev = nullptr;//����ǰһ�����
		while (cur)
		{
			if (data == cur->data)
			{
				//ɾ���ý��
				if (nullptr == prev)
					_table[bucketNo] = cur->next;
				else
					prev->next = cur->next;
				delete cur;
				--_size;
				return 1;
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}
		return 0;
	}
	//������������ֵΪdata��Ԫ��ɾ��
	size_t EraseEqual(const T& data)
	{
		//1.ͨ����ϣ������data���ڵ�Ͱ��
		size_t bucketNo = HashFunc(data);
		Node* cur = _table[bucketNo];
		Node* prev = nullptr;//����ǰһ�����
		int n = 0;
		while (cur)
		{
			if (data == cur->data)
			{
				//ɾ���ý��
				if (nullptr == prev)
					_table[bucketNo] = cur->next;
				else
					prev->next = cur->next;
				delete cur;
				--_size;
				n ++;
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}
		return n;
	}

	//����
	iterator Find(const T& data)
	{
		//1.ͨ����ϣ��������data���ڵ�Ͱ��
		size_t bucketNo = HashFunc(data);

		//2.�ڸ�Ͱ���ڶ�Ӧ�������в���ֵΪdata�Ľ��
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (data == cur->data)
				return iterator(cur, this);
			cur = cur->next;
		}
		return end();
	}
	size_t Size()const
	{

	}
	bool Empty()const
	{

	}
	void Clear()
	{
		//���Ͱɾ��
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			Node* cur = _table[bucketNo];
			while (cur)
			{
				//����ͷɾ����ɾ�������еĽ��
				_table[bucketNo] = cur->next;
				delete cur;
				cur = _table[bucketNo];
			}
		}
	}
	//����
	void Swap(HashBucket<T, DToI>& newHt)
	{
		_table.swap(newHt._table);
		std::swap(_size, newHt._size);
	}
	//Ͱ����
	size_t BucketCount()const
	{
		return _table.capacity();
	}
	size_t BucketSize(size_t bucketNo)const
	{
		size_t count = 0;
		Node* cur = _table[bucketNo];
		while (cur)
		{
			count++;
			cur = cur->next;
		}
		return count;
	}
	size_t Bucket(const K& key)const
	{
		return HashFunc(BucketCount(), key);
	}
	//��ӡ
	void Print()
	{
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			cout << "[" << bucketNo << "]:";
			Node* cur = _table[bucketNo];
			while (cur)
			{
				cout << cur->data << "--->";
				cur = cur->next;
			}
			cout << "NULL" << endl;
		}
		cout << endl;
	}
private:
#if 0
	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			//��Ͱ�ĸ���������
			HashBucket<T, DToI> newHt(_table.capacity() * 2);
			//���ɹ�ϣͰ�е�Ԫ�ز��뵽�¹�ϣͰ��
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				//����I��Ͱ�е�Ԫ�ز��뵽�¹�ϣͰ��
				Node* cur = _table[i];
				while (cur)
				{
					newHt.InsertEqual(cur->data);
					cur = cur->next;
				}
			}
			//�Ѿ����ɹ�ϣͰ�е�Ԫ��ȫ�����²��뵽�µĹ�ϣͰ����
			this->Swap(newHt);
		}
	}
#endif
	//�õ����ݷ�ʽ����Ϊ����پ�Ͱ���Ѿ������ˣ�ֻ��Ҫ����Ͱ�еĽ��һ�ƶ�����Ͱ��
	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			//����2���Ͳ�һ���������ˣ���������ö�٣���ǰ��2���������г���
			vector<Node*> newTable(_table.capacity() * 2);
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* cur = _table[i];
				while (cur)
				{
					//����Ͱ���׽�������
					_table[i] = cur->next;
					//���ý����뵽��Ͱ��
					//����ýڵ�����Ͱ�е�Ͱ��
					size_t bucketNo = HashFunc(newTable.capacity(), cur->data);
					//�ý����뵽��Ͱ��
					cur->next = newTable[bucketNo];
					newTable[bucketNo] = cur;
					//ȡ�ɹ�ϣͰ�е���һ�����
					cur = _table[i];
				}			
			}
			_table.swap(newTable);
		}
	}

	//��ϣ�������ó���������
	size_t HashFunc(size_t capacity, const T& data)
	{
		DToI dToInt;
		//dToInt.operator()(data);
		return dToInt(data) % capacity;
	}
private:
	std::vector<Node*> _table;
	size_t _size;//��ʾ��ϣͰ����ЧԪ�صĸ���
};

void Test1()
{
	int array[] = { 19, 23, 1, 68, 20, 84, 27, 55, 11};
	HashBucket<int> ht;
	for (auto e : array)
		ht.InsertUnique(e);
	ht.Print(); 
	ht.InsertUnique(10);
	ht.InsertUnique(79);
	ht.Print();
	auto it = ht.begin();
	while (it != ht.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (auto e : ht)
		cout << e << " ";
	cout << endl;
}
#include <string>
void Test2()
{
	HashBucket<string, Str2Int> ht;
	ht.InsertUnique("apple");
	ht.InsertUnique("orange");
	ht.InsertUnique("banana");
}