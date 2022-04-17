#pragma once
#include "Common.h"
#include "BitSet.hpp"
template<class K, size_t N = 20,
				  class HF1 = Str2Int1, 
                  class HF2 = Str2Int2,
				  class HF3 = Str2Int3, 
				  class HF4 = Str2Int4, 
				  class HF5 = Str2Int5>
class BloomFilter
{
public:
	BloomFirter()
		: _bst()
		, _size(0)
	{}
	//≤Â»Î
	void Insert(const K& key)
	{
		size_t bitCount = _bst.size();
		HF1 hf;
		_bst.set(hf(key) % bitCount);
		_bst.set(HF2()(key) % bitCount);
		_bst.set(HF3()(key) % bitCount);
		_bst.set(HF4()(key) % bitCount);
		_bst.set(HF5()(key) % bitCount);
		_size++;
	}
	//≤È’“
	bool IsIn(const K& key)
	{
		size_t bitCount = _bst.size();
		size_t index = HF1()(key) % bitCount;
		if (!_bst.test(index))
			return false;

		index = HF1()(key) % bitCount;
		if (!_bst.test(index))
			return false;

		index = HF2()(key) % bitCount;
		if (!_bst.test(index))
			return false; 

		index = HF3()(key) % bitCount;
		if (!_bst.test(index))
			return false;

		index = HF4()(key) % bitCount;
		if (!_bst.test(index))
			return false;

		index = HF5()(key) % bitCount;
		if (!_bst.test(index))
			return false;

		return true;
	}
	size_t size()const
	{
		return _size;
	}
private:
	bite::bitset<N * 5> _bst; 
	size_t _size;
};

void testBloomFilter()
{
	BloomFilter<string> bst;
	bst.Insert("≥¬ƒ¨");
	cout << bst.size() << endl;

}