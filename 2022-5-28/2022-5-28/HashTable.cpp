#include "HashTable.h"

HashTable::HashTable(ush size)
	: _prev(new ush[2*size])
	, _head(_prev + size)
{
	memset(_prev, 0, 2 * size * sizeof(ush));
}
HashTable:: ~HashTable()
{
	delete[] _prev;
	_prev = nullptr;
	_head = nullptr;
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
	matchHead = _head[hashAddr];
	_prev[pos&HASH_MASK] = _head[hashAddr];
	_head[hashAddr] = pos;
}
ush HashTable::GetNext(ush& matchHead)
{
	return _prev[matchHead & HASH_MASK];
}