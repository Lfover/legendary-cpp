#pragma once

#include "BRTREE.hpp"

namespace bite
{
	//set是k模型
	template<class K>
	class set
	{
		typedef pair<K, V> ValueType;
		struct KOFD
		{
			const K& operator()(const ValueType& data)
			{
				return data;
			}
		};
		typedef RBTree<ValueType, KOFD> RBT;
	public:
		set() 
			:_t()
		{}

	public:
		typedef RBT::iterator iterator;
		typedef typename RBT::iterator iterator;
	public:
		map()
			:_t()
		{}
		//迭代器
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();
		}
		//容量
		size_t size()const
		{
			return _t.size();
		}

		bool empty()const
		{
			return _t.empty();
		}


		//modify
		pair<iterator, bool> insert(const ValueType& data)
		{
			return _t.Insert(data);
		}
		void swap(set<K>& m)
		{
			_t.Swap(m._t);
		}
		void clear()
		{ 
			_t.Clear()
		}

		iterator find(const K& key)
		{
			return _t.Find(make_pair(key));
		}

	private:
		RBT _t;
	};
}
#include <string>
#include <iostream>
using namespace std;


void TestSet()
{
	bite::set<string> s;
	s.insert("orange");
	s.insert("apple");
	s.insert("banana");
	cout << s.size() << endl;
	for (auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;
	auto ret = s.insert("apple");
	if (ret.second)
	{
		cout << "apple is in set";
	}
	else
	{
		cout << "apple is not in set";
	}
	s.clear();
	cout << s.size() << endl;
} 