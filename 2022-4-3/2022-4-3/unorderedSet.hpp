#pragma once
#include "HashBucket.hpp"
namespace bite
{
	template<class K>
	class unordered_set
	{
		typedef K ValueType;
		struct KOFD
		{
			const K& operator()(const ValueType& data)
			{
				return data;
			}
		};
	public:
		unordered_set()
			: _ht()
		{}
		//capacity
		size_t size()const
		{
			return _ht.Size();
		}
		bool empty()const
		{
			return _ht.Empty();
		}
		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		V& operator[](const K& key)
		{
			return (*(_ht.InsertEqual(make_pair(key, V())).first)).second;
		}
		pair<iterator, bool> insert(const ValueType& val)
		{
			return _ht.InsertUnique(val);
		}
		size_t erase(const K& key)
		{
			return _ht.EraseUnique(key);
		}

		iterator find(const K& key)
		{
			return _ht.Find(key);
		}
		void clear()
		{
			return _ht.Clear();
		}
		void swap(unordered_set<K>& m)
		{
			_ht.Swap(m._ht);
		}
		size_t bucket_size(size_t bucketNo)
		{
			return _ht.BucketSize(bucketNo);
		}
		size_t bucket_count()const
		{
			_ht.BucketCount();
		}
		size_t bucket(const K& key)const
		{
			return _ht.Bucket(key);
		}
	private:
		HashBucket <ValueType, KOFD> _ht;
	};
}

void Test2()
{
	bite::unordered_set<string> m;
	m.insert("apple");
	m.insert("orange");
	m.insert("banana");
	m.insert("grape");

	for (auto& e : m)
	{
		cout << e << endl;
	}
	cout << m.size() << endl;
	cout << m.bucket_count() << endl;
	cout << m.bucket_size(0) << endl;
	m.erase("orange");
	for (auto& e : m)
	{
		cout << e << endl;
	}
	m.clear();
	if (m.empty())
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
}