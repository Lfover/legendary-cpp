
#pragma once
typedef unsigned long long ulg;
typedef unsigned char uchar;
#include <string>
#include <vector>
#include "HuffmanTree.hpp"

struct CharInfo
{
	char _ch;//字符
	ulg _appearCount;//表示字符出现的次数
	std::string _strCode;//字符对应的编码
	CharInfo(ulg appCount = 0)
		: _appearCount(appCount)
	{}
	CharInfo operator+(const CharInfo& c)
	{
		return CharInfo(_appearCount + c._appearCount);
	}
	bool operator>(const CharInfo& c)const
	{
		return _appearCount > c._appearCount;
	}
};
class HTCompress
{
public:
	HTCompress();
	void CompressFile(const std::string& filePath);
	void UNCompressFile(const std::string& filePath);

	void WriteHeadInfo(FILE* fOut, const std::string& filePath);
private:
	void GeneteCode(HTNode<CharInfo>* root);
	void GetLine(FILE* fIn, std::string& s);
private:
	std::vector<CharInfo> _charInfo;

};
