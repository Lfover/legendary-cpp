#pragma once
#include <vector>
#include "Common.h"
#include <iostream>
using namespace std;
//哈希桶中管理的是一个一个的链表
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
//前置声明
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
	//具有指针类似的操作
	T& operator*()
	{
		return _node->data;
	}
	T* operator->()
	{
		return &(operator*());
	}
	//迭代器要能够移动
	//单链表只能单向
	Self& operator++()
	{
		Self temp(*this);
		Next();
		return temp;
	}
	//需要能够比较
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
			//node是当前链表中的最后一个结点
			//找_node所在桶的下一个非空桶
			//必须知道当前结点在哪一个桶中
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
	//构造函数
	HashBucket(size_t capacity = 10)
		:_table(GetNextPrime(capacity))
		, _size(0)
	{}
	//析构函数
	~HashBucket()
	{
		Clear();
	}
	iterator begin()
	{
		//在第一个非空桶首届点位置
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
	//只可以插入唯一的元素
	pair<iterator, bool> InsertUnique(const T& data)
	{
		CheckCapacity();
		//1.通过哈希函数计算元素所在的桶号 
		size_t bucketNo = HashFunc(_table.capacity(), data);
		//2.检测data是否在bucketNo桶中存在
		//实际上只需要在bucketNo对应的链表中查找data是否存在
		Node* cur = _table[bucketNo];
		while (cur)
		{
			if (data == cur->data)
				return make_pair(iterator(cur, this), false);
			cur = cur->next;
		}
		//3.插入新结点，头插
		cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;
		return make_pair(iterator(cur, this), true);
	}
	//可以插入重复的元素
	bool InsertEqual(const T& data)
	{
		CheckCapacity();
		//1.通过哈希函数计算元素所在的桶号 
		size_t bucketNo = HashFunc(data);
		
		//2.插入新结点，头插
		Node* cur = new Node(data);
		cur->next = _table[bucketNo];
		_table[bucketNo] = cur;
		_size++;
		return true;
	}

	//删除
	//在哈希表中删除值为data的元素，返回值类型表示删除结点值为data的结点的个数

	size_t EraseUnique(const T& data)
	{
		//1.通过哈希函数找data所在的桶号
		size_t bucketNo = HashFunc(data);
		Node* cur = _table[bucketNo];
		Node* prev = nullptr;//保存前一个结点
		while (cur)
		{
			if (data == cur->data)
			{
				//删除该结点
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
	//将链表中所有值为data的元素删除
	size_t EraseEqual(const T& data)
	{
		//1.通过哈希函数找data所在的桶号
		size_t bucketNo = HashFunc(data);
		Node* cur = _table[bucketNo];
		Node* prev = nullptr;//保存前一个结点
		int n = 0;
		while (cur)
		{
			if (data == cur->data)
			{
				//删除该结点
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

	//查找
	iterator Find(const T& data)
	{
		//1.通过哈希函数计算data所在的桶号
		size_t bucketNo = HashFunc(data);

		//2.在该桶所在对应的链表中查找值为data的结点
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
		//逐个桶删除
		for (size_t bucketNo = 0; bucketNo < _table.capacity(); ++bucketNo)
		{
			Node* cur = _table[bucketNo];
			while (cur)
			{
				//采用头删法来删除链表中的结点
				_table[bucketNo] = cur->next;
				delete cur;
				cur = _table[bucketNo];
			}
		}
	}
	//交换
	void Swap(HashBucket<T, DToI>& newHt)
	{
		_table.swap(newHt._table);
		std::swap(_size, newHt._size);
	}
	//桶数量
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
	//打印
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
			//将桶的个数翻个倍
			HashBucket<T, DToI> newHt(_table.capacity() * 2);
			//将旧哈希桶中的元素插入到新哈希桶中
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				//将第I个桶中的元素插入到新哈希桶中
				Node* cur = _table[i];
				while (cur)
				{
					newHt.InsertEqual(cur->data);
					cur = cur->next;
				}
			}
			//已经将旧哈希桶中的元素全部重新插入到新的哈希桶中了
			this->Swap(newHt);
		}
	}
#endif
	//好的扩容方式：因为结点再旧桶中已经存在了，只需要将旧桶中的结点一移动到新桶中
	void CheckCapacity()
	{
		if (_size == _table.capacity())
		{
			//乘以2倍就不一定是素数了，可以利用枚举，提前将2倍素数罗列出来
			vector<Node*> newTable(_table.capacity() * 2);
			for (size_t i = 0; i < _table.capacity(); ++i)
			{
				Node* cur = _table[i];
				while (cur)
				{
					//将旧桶中首结点拆下来
					_table[i] = cur->next;
					//将该结点插入到新桶中
					//计算该节点在新桶中的桶号
					size_t bucketNo = HashFunc(newTable.capacity(), cur->data);
					//该结点插入到新桶中
					cur->next = newTable[bucketNo];
					newTable[bucketNo] = cur;
					//取旧哈希桶中的下一个结点
					cur = _table[i];
				}			
			}
			_table.swap(newTable);
		}
	}

	//哈希函数采用除留余数法
	size_t HashFunc(size_t capacity, const T& data)
	{
		DToI dToInt;
		//dToInt.operator()(data);
		return dToInt(data) % capacity;
	}
private:
	std::vector<Node*> _table;
	size_t _size;//表示哈希桶中有效元素的个数
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