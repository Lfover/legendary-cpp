#pragma once
#include "HuffmanTree.hpp"
#include "Common.h"

// 统计字符频度信息，构建huffman树时需要用到
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

	ush _ch;                   // 字符
	ush _charCount;            // 字符出现次数
	ush _len;                  // 码字长度
	ush _code;                 // 编码
};


struct DecodeTable
{
	int _decodeLen;   // 编码位长
	int _code;       // 首字符编码
	ush _lenCount;    // 相同编码长度个数
	ush _charIndex;   // 符号索引
};

#include "HashTable.h"


class BitZip
{
	typedef HuffmanTreeNode<CharInfo> Node;
public:
	BitZip();
	~BitZip();

	// 压缩 与 解压缩
	bool Deflate(const string& filePath);
	bool unDeflate(const string& filePath);

private:
	// LZ77中获取最长匹配算法
	uch LongMatch(ush matchHead, ush& curMatchDist);
	void FillWindow(FILE* fIn);

	// 保存LZ77的压缩结果
	void SaveLZ77Result(ush dist, uch ch, uch& flag, uch& bitCount);


	// 使用huffman压缩算法对LZ77的结果进行再次压缩
	void CompressFileHuffman();

	// 压缩长度距离对
	void CompressLengthDist(uch length, ush dist, uch& data, uch& bitCount);

	// 压缩源字符
	void CompressChar(ush ch, uch& data, uch& bitCount);
	void Compress(ulg code, ulg codeLen, uch& data, uch& bitCount);

	void InitCharInfoArray();

	void StatAppearCount();

	size_t GetSeconIndex(uch ch);
	size_t GetSeconIndex(ush dist);

	// 写解码信息：每个字符的编码长度
	void WriteCodeInfo(FILE* fOut);

	// 递归获取编码长度：即huffman树中每个叶子节点的高度
	void GetCodeLen(Node* pRoot, vector<CharInfo>& codeInfo);
	void GetCodeLen(Node* pRoot, vector<CharInfo>& codeInfo, int len);

	// 根据获取的编码长度计算编码
	void GenerateCode(vector<CharInfo>& codeInfo);

	// 生成解码信息表
	void GenerateDecodeTab(vector<CharInfo>& codeInfo, vector<DecodeTable>& decTable);
	void GetNextBit(FILE* fIn, ush& vCode, uch& ch, uch& bitCount);
	void GetDecodeLen(FILE* fIn);
	ush UNCompressSymbol(FILE* fIn, vector<CharInfo>& codeInfo, vector<DecodeTable>& decTable, uch& ch, uch& bitCount);
	std::string GetLine(FILE* fOut);
private:
	// 保存LZ77的压缩结果，将来交给huffman树来进行压缩
	vector<uch> _bytelenData;
	vector<ush> _distData;
	vector<uch> _flag;

	// huffman压缩相关
	vector<CharInfo> _charlenInfo;
	vector<CharInfo> _distInfo;


	///////////////////////LZ77相关成员///////////////////////////////////
	uch* _pWin;         // LZ77压缩时用来保存源文件数据的：查找缓冲区和先行缓冲区，总共64k
	ush _start;         // 先行缓冲区的当前位置：表示压缩到那块
	HashTable _ht;      // 借助哈希的思想提高查找最长匹配串的效率
	ulg _lookAhead;  // 窗口中剩余待压缩字符的个数

	FILE* fOut;

	const static ush MIN_LOOKAHEAD = MAX_MATCH + 1;
	const static ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;
	const static ush LZ77_BUFF_SIZE = 0x8000;
	bool _isLast;   // 标记是否为最后一个块
};