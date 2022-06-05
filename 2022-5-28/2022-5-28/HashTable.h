#pragma once
#include "common.h"
#include <string>
class HashTable
{
public:
	HashTable(ush size);
	~HashTable();
	void Insert(ush& hashAddr, uch ch, ush pos, ush& matchHead);
	ush GetNext(ush& matchHead);
private:
	void HashFunc(ush& hashAddr, uch ch);
	ush H_SHIFT();
private:
	ush* _prev;
	ush* _head;
	//哈希桶的个数2^15
public:
	const static ush HASH_BITS = 15;
	//哈希表大小
	const static ush HASH_SIZE = (1 << HASH_BITS);
	//哈希掩码：主要作用是将右窗数据搬移到左窗。用来更新哈希表的数据
	const static ush HASH_MASK = HASH_SIZE - 1;

	const static ush WSIZE = 0x8000;
};