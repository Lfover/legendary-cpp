#pragma once
#include <string>

template<class T>
class DToIntDef
{
public:
	size_t operator()(const T& data)
	{
		return data;
	}
};
//ר���ַ���ת��Ϊ����
class Str2Int
{
public:
	size_t operator()(const std::string& s)
	{
		return BKDRHash(s.c_str());
	}
	size_t BKDRHash(const char *str)
	{
		size_t seed = 131;
		size_t hash = 0;
		while (*str)
		{
			hash = hash * seed + (*str++);
		}
		return (hash & 0x7FFFFFFFF);
	}
}; 
const int PRIMECOUNT = 28;
const size_t primeList[PRIMECOUNT] = {
	53ul, 97ul, 193ul, 398ul, 796ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653198ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};
size_t GetNextPrime(size_t prime)
{
	size_t i = 0;
	for (; i < PRIMECOUNT; ++i)
	{
		if (primeList[i] > primeList[i])
			return primeList[i];
	}
	return primeList[i];
}