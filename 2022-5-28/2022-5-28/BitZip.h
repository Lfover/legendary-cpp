#pragma once
#include "common.h"
#include <string>
#include "HuffmanTree.hpp"
using namespace std;

struct ElemInfo
{
	ush _ch;
	ulg _appearCount;
	ush _len;
	ulg _chCode;
	ElemInfo(ulg appCount = 0)
		: _appearCount(appCount)
	{}

	ElemInfo operator+(const ElemInfo& c)
	{
		return ElemInfo(_appearCount + c._appearCount);
	}

	bool operator>(const ElemInfo& c)const
	{
		return _appearCount > c._appearCount;
	}

	bool operator==(const ElemInfo& c)const
	{
		return _appearCount == c._appearCount;
	}

	bool operator<(const ElemInfo& c)const
	{
		if ((_len < c._len) || (_len == c._len && _ch < c._ch))
			return true;
		return false;
	}
};

// �����---�ڽ����ʱ�������
struct DecodeTable
{
	int _decodeLen;   // ����λ��
	int _code;       // ���ַ�����
	ush _lenCount;    // ��ͬ���볤�ȸ���
	ush _charIndex;   // ��������
};

class BitZip
{
public:
	BitZip();
	~BitZip();
	void Deflate(const string& filePath);
	void unDeflate(const string& filePath);
//private:
//	void UNCompressLZ77(const string& filePath);
private:
	void SaveLZ77Result(ush dist, uch length, uch& flag, uch& bitCount, const ulg lookahead);
	ush LongestMatch(ush matchHead, ush start, ush& curMatchDist);
	void FillDate(FILE* fIN, ulg& lookahead, ush& start);
	////////////////////////////////////////////////////////
	void CompressBlock();
	void StartAppearCount();
	ush GetIntervalCodeIndex(uch len);
	ush GetIntervalCodeIndex(ush dist);
	void GenerateCodeLen(HuffmanTreeNode<ElemInfo>* root, vector<ElemInfo>& elemInfo);
	void GenerateCodeLen(HuffmanTreeNode<ElemInfo>* root, vector<ElemInfo>& elemInfo, ush len);
	void GenerateCode(vector<ElemInfo>& codeInfo);
	void WriteCodeLen();

	void CompressChar(ush ch, uch& bitInfo, uch& bitInfoCount);
	void CompressLengthDist(uch length, ush dist, uch& bitInfo, uch& bitInfoCount);
	void Compress(ulg chCode, ush codeLen, uch& bitInfo, uch& bitInfoCount);

	void GetDecodeLen(FILE* fIn);
	void GenerateDecodeTab(vector<ElemInfo>& codeInfo, vector<DecodeTable>& decTab);
	ush UNCompressSymbol(FILE* fIn, vector<ElemInfo>& codeInfo, vector<DecodeTable>& decTable, uch& ch, uch& bitCount);
	void GetNextBit(FILE* fIn, ush& code, uch& ch, uch& bitCount);

	void ClearPreBlockInfo();
	void GetLine(FILE* fIn, string& s);
private:
	uch* _pWin;
	HashTable _ht;

	/////////////////////////////////////
	// ��������LZ77�Ľ��
	vector<uch> _byteLenData;
	vector<ush> _distData;
	vector<uch> _flagData;

	bool _isLast;  // �Ƿ�λ���һ����
	FILE* fOut;


	///////////////////////////////////////////
	//��������huffman���ͱ���
	vector<ElemInfo> _byteLenInfo;
	vector<ElemInfo> _distInfo;

	const static ush MIN_LOOKAHEAD = MIN_MATCH + MAX_MATCH + 1;
	const static ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;
	const static ush BUFF_SIZE = 0x8000;
};