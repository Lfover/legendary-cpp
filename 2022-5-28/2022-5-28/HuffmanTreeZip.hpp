
#pragma once
#include <string>
#include <vector>
#include "huffmanTree.hpp"
using namespace std;
typedef unsigned long long ulg;
struct CharInfo
{
	char ch;
	ulg _appearCount;//ÿ���ַ����ֵĴ���
	std::string _strCode;//�ַ���Ӧ�ı���

	CharInfo(ulg appCount = 0)
		: _appearCount(appCount)
	{ }
	//��+���������
	CharInfo operator+(const CharInfo& c)
	{
		return CharInfo(_appearCount + c._appearCount);
	}
	//��>��������
	bool opeartor > (const CharInfo& c)const
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
	//�������ļ��ж������ֽڷ�ʽ�����
	vector<CharInfo> _charinfo;

};

