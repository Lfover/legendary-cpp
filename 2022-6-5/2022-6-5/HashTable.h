#pragma once
#include "Common.h"

class HashTable
{
public:
	HashTable(size_t size);
	~HashTable();
	void Insert(ush& hashAddr, uch ch, ush pos, ush& matchHead);
	void HashFunc(ush& hashAddr, uch ch);
	ush GetNext(ush matchPos);
	void Update();
private:
	ush H_SHIFT();
private:
	ush* _prev;
	ush* _head;
	size_t _hashSize;
};