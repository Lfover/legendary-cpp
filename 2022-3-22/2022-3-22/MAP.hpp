#pragma once

#include "BRTREE.hpp"

namespace bite
{
	//map是k-v模型
	template<class K, class V>
	class map
	{
		typedef pair<K, V> ValueType;
		struct KOFPair
		{
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};
		typedef RBTree<ValueType, KOFD> RBT;
	public:
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
		//acess
		V& operator[](const K& key)
		{
			return (*(_t.Insert(make_pait(key, V()))).first).second;
		}

		//modify
		pair<iterator, bool> insert(const ValueType& data)
		{
			return _t.Insert(data);
		}
		void swap(map< K, V>& m)
		{
			_t.Swap(m._t);
		}
		void clear()
		{
			_t.Clear()
		}

		iterator find(const K& key)
		{
			return _t.Find(make_pair(key, V()));
		}


	private:
		RBT _t;
	};
}
#include <string>
#include <iostream>
using namespace std;


void TestMap()
{
	bite::map<string, string> m;
	m.insert(make_pair("orange", "橙子"));
	m.insert(make_pair("banana", "香蕉"));
	m.insert(make_pair("apple", "苹果"));

	cout << m.size() << endl;
	cout << m["apple"] << endl;

	//可以通过[]进行插入
	m["peach"] = "桃子";

	auto it = m.begin();
	while (it != m.end())
	{
		cout << "[" << it->first << "," << (*it).second << "]" << endl;
		++it;
	}
	cout << endl;
	it = m.find("grepe");
	if (it != m.end())
	{
		cout << "grep is in map" << endl;
	}
	else
	{
		cout << "grep is not in map" << endl;
	}
	m.clear();
	cout << m.size() << endl;

}