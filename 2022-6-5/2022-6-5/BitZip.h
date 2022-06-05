#pragma once
#include "HuffmanTree.hpp"
#include "Common.h"

// ͳ���ַ�Ƶ����Ϣ������huffman��ʱ��Ҫ�õ�
struct CharInfo
{
	CharInfo(ush charCount = 0)
		: _ch(0)
		, _charCount(charCount)
		, _len(0)
		, _code(0)
	{}

	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_charCount + info._charCount);
	}

	bool operator>(const CharInfo& info)
	{
		return _charCount > info._charCount;
	}

	bool operator<(const CharInfo& info)
	{
		if (_len < info._len || (_len == info._len && _ch < info._ch))
			return true;

		return false;
	}

	bool operator!=(const CharInfo& info)const
	{
		return _charCount != info._charCount;
	}

	bool operator==(const CharInfo& info)const
	{
		return _charCount == info._charCount;
	}

	ush _ch;                   // �ַ�
	ush _charCount;            // �ַ����ִ���
	ush _len;                  // ���ֳ���
	ush _code;                 // ����
};


struct DecodeTable
{
	int _decodeLen;   // ����λ��
	int _code;       // ���ַ�����
	ush _lenCount;    // ��ͬ���볤�ȸ���
	ush _charIndex;   // ��������
};

#include "HashTable.h"


class BitZip
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	BitZip();
	~BitZip();

	// ѹ�� �� ��ѹ��
	bool Deflate(const string& filePath);
	bool unDeflate(const string& filePath);

private:
	// LZ77�л�ȡ�ƥ���㷨
	uch LongMatch(ush matchHead, ush& curMatchDist);
	void FillWindow(FILE* fIn);

	// ����LZ77��ѹ�����
	void SaveLZ77Result(ush dist, uch ch, uch& flag, uch& bitCount);


	// ʹ��huffmanѹ���㷨��LZ77�Ľ�������ٴ�ѹ��
	void CompressFileHuffman();

	// ѹ�����Ⱦ����
	void CompressLengthDist(uch length, ush dist, uch& data, uch& bitCount);

	// ѹ��Դ�ַ�
	void CompressChar(ush ch, uch& data, uch& bitCount);
	void Compress(ulg code, ulg codeLen, uch& data, uch& bitCount);

	void InitCharInfoArray();

	void StatAppearCount();

	size_t GetSeconIndex(uch ch);
	size_t GetSeconIndex(ush dist);

	// д������Ϣ��ÿ���ַ��ı��볤��
	void WriteCodeInfo(FILE* fOut);

	// �ݹ��ȡ���볤�ȣ���huffman����ÿ��Ҷ�ӽڵ�ĸ߶�
	void GetCodeLen(Node* pRoot, vector<CharInfo>& codeInfo);
	void GetCodeLen(Node* pRoot, vector<CharInfo>& codeInfo, int len);

	// ���ݻ�ȡ�ı��볤�ȼ������
	void GenerateCode(vector<CharInfo>& codeInfo);

	// ���ɽ�����Ϣ��
	void GenerateDecodeTab(vector<CharInfo>& codeInfo, vector<DecodeTable>& decTable);
	void GetNextBit(FILE* fIn, ush& vCode, uch& ch, uch& bitCount);
	void GetDecodeLen(FILE* fIn);
	ush UNCompressSymbol(FILE* fIn, vector<CharInfo>& codeInfo, vector<DecodeTable>& decTable, uch& ch, uch& bitCount);
	std::string GetLine(FILE* fOut);
private:
	// ����LZ77��ѹ���������������huffman��������ѹ��
	vector<uch> _bytelenData;
	vector<ush> _distData;
	vector<uch> _flag;

	// huffmanѹ�����
	vector<CharInfo> _charlenInfo;
	vector<CharInfo> _distInfo;


	///////////////////////LZ77��س�Ա///////////////////////////////////
	uch* _pWin;         // LZ77ѹ��ʱ��������Դ�ļ����ݵģ����һ����������л��������ܹ�64k
	ush _start;         // ���л������ĵ�ǰλ�ã���ʾѹ�����ǿ�
	HashTable _ht;      // ������ϣ��˼����߲����ƥ�䴮��Ч��
	ulg _lookAhead;  // ������ʣ���ѹ���ַ��ĸ���

	FILE* fOut;

	const static ush MIN_LOOKAHEAD = MAX_MATCH + 1;
	const static ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;
	const static ush LZ77_BUFF_SIZE = 0x8000;
	bool _isLast;   // ����Ƿ�Ϊ���һ����
};