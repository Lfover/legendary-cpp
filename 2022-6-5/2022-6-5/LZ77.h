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
	// LZ77ѹ��ʱ��������Դ�ļ����ݵģ����һ����������л��������ܹ�64k
	uch* _pWin;

	// ���л������ĵ�ǰλ�ã���ʾѹ�����ǿ�
	ush _start;

	// ������ϣ��˼����߲����ƥ�䴮��Ч��
	HashTable _ht;

	// ������ʣ���ѹ���ַ��ĸ���
	size_t _lookAhead;

	const static ush MIN_LOOKAHEAD = MAX_MATCH + 1;
	const static ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;
};

