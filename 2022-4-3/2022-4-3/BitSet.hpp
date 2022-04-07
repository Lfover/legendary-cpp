#pragma once

#include <vector>
#include <assert.h>
namespace bite
{
	template<size_t N>
	class bitset
	{
	public:
		bitset()
			: _bst((N >> 3) + 1)
			, _size(0)
		{}
		//将which的bit位置为1
		void set(size_t which)
		{
			assert(which < N);
			size_t i = which / 8;
			size_t j = which % 8;

			_bst[i] |= (1 << j);
			++_size;
		}
		//将which的bit位置为0
		void reset(size_t which)
		{
			assert(which < N);
			size_t i = which / 8;
			size_t j = which % 8;

			_bst[i] &= ~(1 << j);
			--_size;
		}

		bool test(size_t which)
		{
			assert(which < N);
			size_t i = which / 8;
			size_t j = which % 8;

			return 0 != _bst[i] & (1 << j);
		}
		size_t size()const
		{
			return N;
		}
		size_t count()const
		{
			return _size;
		}

	private:
		std::vector<unsigned char> _bst;
		size_t _size;
	};
}
#include <iostream>
using namespace std;
void TestMyBitSet()
{
	int array[] = { 1, 3, 7, 4, 12, 16, 19, 13, 22, 18 };
	bite::bitset<23> bs;
	for (auto e : array)
		bs.set(e);
	cout << bs.size() << endl;
	cout << bs.count() << endl;
	bs.set(15);
	cout << bs.count() << endl;
	if (bs.test(15))
	{
		cout << "1" << endl;
	}
	else
	{
		cout << "0" << endl;
	}


	bs.reset(15);
	cout << bs.count() << endl;
	if (bs.test(15))
	{
		cout << "1" << endl;
	}
	else
	{
		cout << "0" << endl;
	}
}