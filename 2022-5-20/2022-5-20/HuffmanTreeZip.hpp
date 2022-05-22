#pragma once
#include <string>
#include <vector>
#include "huffmanTree.hpp"
using namespace std;
typedef unsigned long long ulg;
struct CharInfo
{
	char ch;
	ulg _appearCount;//每个字符出现的次数
	std::string _strCode;//字符对应的编码
	
	CharInfo(ulg appCount = 0)
		: _appearCount(appCount)
	{ }
	//对+运算符重载
	CharInfo operator+(const CharInfo& c)
	{
		return CharInfo(_appearCount + c._appearCount);
	}
	//对>进行重载
	bool opeartor>(const CharInfo& c)const
	{
		return _appearCount > c._appearCount;
	}
};
class HuffmanCompress
{
public:
	HuffmanCompress();
	void CompressFile(const std::string& filePath);
	void UNCompressFile(const std::string& filePath);
private:
	void GeneteCode(HuffmanTree<CharInfo>* root);
private:
	//数据在文件中都是以字节方式保存的
	vector<CharInfo> _charinfo;

};
