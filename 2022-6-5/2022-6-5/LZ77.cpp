#include "LZ77.h"
#include <assert.h>
#include <iostream>
using namespace std;


LZ77::LZ77()
	: _pWin(new uch[WSIZE * 2])
	, _ht(WSIZE)
	, _start(0)
	, _lookAhead(0)
{}


LZ77::~LZ77()
{
	if (_pWin)
	{
		delete[] _pWin;
	}
}

bool LZ77::CompressFile(const string& filePath)
{
	return true;
}

// matchHead--->哈希匹配链起始位置
uch LZ77::LongMatch(ush matchHead, ush& curMatchDist)
{
	uch curMatchLen = 0;
	uch maxLen = 0;
	ush pos = 0;
	uch Matchchainlen = 255;
	// 因此只搜索_start左边MAX_DIST范围内的串
	ush limit = _start > MAX_DIST ? _start - MAX_DIST : 0;
	do
	{
		uch* pStart = _pWin + _start;
		uch* pEnd = pStart + MAX_MATCH;

		// 在查找缓冲区中找到匹配串的起始位置
		uch* pCurStart = _pWin + matchHead;
		curMatchLen = 0;

		// 找单条链的匹配长度
		while (pStart < pEnd && *pStart == *pCurStart)
		{
			pStart++;
			pCurStart++;
			curMatchLen++;
		}

		if (curMatchLen > maxLen)
		{
			maxLen = curMatchLen;
			pos = matchHead;
		}

	} while (((matchHead = _ht.GetNext(matchHead)) > limit) &&
		Matchchainlen--);

	curMatchDist = _start - pos;

	return maxLen;
}

void LZ77::FillWindow(FILE* fIn)
{
	// 将右窗口中数据搬移到左窗口
	if (_start >= WSIZE + MAX_DIST)
	{
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		memset(_pWin + WSIZE, 0, WSIZE);
		_start -= WSIZE;

		// 更新哈希表
		_ht.Update();
	}

	// 向右窗口中填充数据
	if (!feof(fIn))
	{
		_lookAhead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
	}
}