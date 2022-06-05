
#pragma once

#include <string>

#include "HuffmanTree.hpp"


typedef unsigned char uchar;


struct CharInfo
{
	uchar ch;
	size_t appearCount;   // 字符出现的次数
	std::string strCode;  // 字符的编码

	CharInfo operator+(const CharInfo& ci)const
	{
		CharInfo temp;
		temp.appearCount = this->appearCount + ci.appearCount;
		return temp;
	}

	bool operator>(const CharInfo& ci)const
	{
		return this->appearCount > ci.appearCount;
	}

	bool operator!=(const CharInfo& ci)const
	{
		return this->appearCount != ci.appearCount;
	}

	bool operator==(const CharInfo& ci)const
	{
		return this->appearCount == ci.appearCount;
	}
};

class FileCompress
{
public:
	FileCompress();
	bool CompressFile(const std::string& strFilePath);
	bool UNCompressFile(const std::string& strFilePath);

private:
	void GenerateCode(HTNode<CharInfo>* root);
	void WriteFileHead(FILE* fOut, const std::string& filePath);
	void GetLine(FILE* fIn, std::string& szContent);
private:
	CharInfo fileInfo[256];// 保存源文件中字符出现的次数信息以及编码
};

