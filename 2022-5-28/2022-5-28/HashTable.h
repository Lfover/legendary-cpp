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
	//��ϣͰ�ĸ���2^15
public:
	const static ush HASH_BITS = 15;
	//��ϣ���С
	const static ush HASH_SIZE = (1 << HASH_BITS);
	//��ϣ���룺��Ҫ�����ǽ��Ҵ����ݰ��Ƶ��󴰡��������¹�ϣ�������
	const static ush HASH_MASK = HASH_SIZE - 1;

	const static ush WSIZE = 0x8000;
};