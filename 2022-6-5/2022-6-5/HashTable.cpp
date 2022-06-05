#include "HashTable.h"
#include <string>

const ush HASH_BITS = 15;
const ush HASH_SIZE = (1 << HASH_BITS);
const ush HASH_MASK = HASH_SIZE - 1;

HashTable::HashTable(size_t size)
	: _prev(new ush[size * 2])
	, _head(_prev + size)
	, _hashSize(size * 2)
{
	memset(_head, 0, sizeof(ush) * size);
}

HashTable::~HashTable()
{
	if (_prev)
	{
		delete[] _prev;
		_prev = _head = nullptr;
	}
}

void HashTable::HashFunc(ush& hashAddr, uch ch)
{
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK;
}

ush HashTable::H_SHIFT()
{
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}

void HashTable::Insert(ush& hashAddr, uch ch, ush pos, ush& matchHead)
{
	HashFunc(hashAddr, ch);

	_prev[pos & HASH_MASK] = _head[hashAddr];
	matchHead = _head[hashAddr];
	_head[hashAddr] = pos;
}

ush HashTable::GetNext(ush matchPos)
{
	return _prev[matchPos];
}

void HashTable::Update()
{
	// 将右窗口的匹配位置更新到左窗
	// 更新head
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		if (_head[i] >= WSIZE)
			_head[i] -= WSIZE;
		else
			_head[i] = 0;
	}

	// 更新prev
	for (size_t i = 0; i < WSIZE; i++)
	{
		if (_prev[i] >= WSIZE)
			_prev[i] -= WSIZE;
		else
			_prev[i] = 0;
	}
}
