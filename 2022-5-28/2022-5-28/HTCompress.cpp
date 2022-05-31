#include "HTCompress.h"
#include "HuffmanTree.hpp"
#include <iostream>
using namespace std;
HTCompress::HTCompress()
{
	_charInfo.resize(256);
	for (size_t i = 0; i < 256; i++)
	{
		_charInfo[i]._ch = i;
	}
}
void HTCompress::CompressFile(const std::string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "r");
	if (nullptr == fIn)
	{
		cout << "��ѹ�����ļ�·������" << endl;
		return;
	}
	//1.ͳ���ļ���ÿ���ַ����ֵĴ���
	char readBuff[1024];
	while (true)
	{
		size_t rdSize = fread(readBuff, 1, 1024, fIn);
		if (rdSize == 0)
			break;
		for (size_t i = 0; i < rdSize; i++)
		{
			_charInfo[readBuff[i]]._appearCount;
		}
	}
	//2.��ChInfo��ΪȨֵȥ����huffman��
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charInfo);

	//3.�ٻ�ȡÿ���ַ���Ӧ��huffman����

	fclose(fIn);
}

//���ߵ�Ҷ�ӽڵ��λ�ã�Ȼ��˳��Ҷ�ӽڵ����Ͻ��б����ȡ
void HTCompress::GeneteCode(HuffmanTreeNode<CharInfo>* root)
{
	if (nullptr == root)
		return;

}
void UNCompressFile(std::string& filePath);