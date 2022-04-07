#pragma once
#include "HashBucket.hpp"
namespace bite
{
	template<class K, class V>
	class unordered_map
	{ 
		typedef pair<K, V> ValueType;
		struct KOFD
		{
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};
		typedef HashBucket<ValueType>::iterator iterator;

	public:
		unordered_map()
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
		void swap(unordered_map<K, V>& m)
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

void Test1()
{
	bite::unordered_map<string, string> m;
	m.insert(make_pair("apple", "Æ»¹û"));
	m.insert(make_pair("orange", "³È×Ó"));
	m.insert(make_pair("banana", "Ïã½¶"));
	m.insert(make_pair("grape", "ÆÏÌÑ"));
	cout << m["apple"] << endl;
	cout << m["pear"] << endl;
	for (auto& e : m)
	{
		cout << e->first << "   " << e.second << endl;
	}
	cout << m.size() << endl;
	cout << m.bucket_count() << endl;
	cout << m.bucket_size(0) << endl;
	m.erase("orange");
	for (auto& e : m)
	{
		cout << e->first << "   " << e.second << endl;
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