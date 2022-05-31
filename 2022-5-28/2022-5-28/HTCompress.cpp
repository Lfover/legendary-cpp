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
		cout << "带压缩的文件路径出错" << endl;
		return;
	}
	//1.统计文件中每个字符出现的次数
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
	//2.以ChInfo作为权值去创建huffman树
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charInfo);

	//3.再获取每个字符对应的huffman编码

	fclose(fIn);
}

//先走到叶子节点的位置，然后顺着叶子节点向上进行编码获取
void HTCompress::GeneteCode(HuffmanTreeNode<CharInfo>* root)
{
	if (nullptr == root)
		return;

}
void UNCompressFile(std::string& filePath);