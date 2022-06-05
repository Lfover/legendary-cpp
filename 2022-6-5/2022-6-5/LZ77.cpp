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

// matchHead--->��ϣƥ������ʼλ��
uch LZ77::LongMatch(ush matchHead, ush& curMatchDist)
{
	uch curMatchLen = 0;
	uch maxLen = 0;
	ush pos = 0;
	uch Matchchainlen = 255;
	// ���ֻ����_start���MAX_DIST��Χ�ڵĴ�
	ush limit = _start > MAX_DIST ? _start - MAX_DIST : 0;
	do
	{
		uch* pStart = _pWin + _start;
		uch* pEnd = pStart + MAX_MATCH;

		// �ڲ��һ��������ҵ�ƥ�䴮����ʼλ��
		uch* pCurStart = _pWin + matchHead;
		curMatchLen = 0;

		// �ҵ�������ƥ�䳤��
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
	// ���Ҵ��������ݰ��Ƶ��󴰿�
	if (_start >= WSIZE + MAX_DIST)
	{
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		memset(_pWin + WSIZE, 0, WSIZE);
		_start -= WSIZE;

		// ���¹�ϣ��
		_ht.Update();
	}

	// ���Ҵ������������
	if (!feof(fIn))
	{
		_lookAhead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
	}
}