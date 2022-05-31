#pragma once
typedef unsigned long long ulg;
#include <string>
#include <vector>

struct CharInfo
{
	char _ch;
	ulg _appearCount;//表示字符出现的次数
	std::string _strCode;//字符对应的编码
	CharInfo(ulg appCount)
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
private:
	void GeneteCode(HuffmanTreeNode <CharInfo>* root
; private:
	std::vector<CharInfo> _charInfo;

};