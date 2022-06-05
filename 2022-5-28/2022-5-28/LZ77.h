#pragma once
#include "common.h"
#include "HashTable.h"
using std::string;
class LZ77
{
public:
	LZ77();
	~LZ77();
	void CompressLZ77(const string& filePath);
	void UNCompressLZ77(const string& filePath);
	ush LongestMatch(ush matchHead, ush start, ush& curMatchDist);
	void writeFlag(FILE* temp, bool isDist, uch& ch, uch& bitCount);
	void MergeFile(FILE* fOut, ulg fileSize);
private:
	uch* _pWin;
	HashTable _ht;
};
