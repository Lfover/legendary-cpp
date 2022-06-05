#pragma once

#include "HashTable.h"





class LZ77
{
public:
	LZ77();
	~LZ77();
	bool CompressFile(const string& filePath);

private:
	uch LongMatch(ush matchHead, ush& curMatchDist);
	void FillWindow(FILE* fIn);

private:
	// LZ77压缩时用来保存源文件数据的：查找缓冲区和先行缓冲区，总共64k
	uch* _pWin;

	// 先行缓冲区的当前位置：表示压缩到那块
	ush _start;

	// 借助哈希的思想提高查找最长匹配串的效率
	HashTable _ht;

	// 窗口中剩余待压缩字符的个数
	size_t _lookAhead;

	const static ush MIN_LOOKAHEAD = MAX_MATCH + 1;
	const static ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;
};

