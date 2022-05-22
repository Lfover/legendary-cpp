#include "HuffmanTreeZip.hpp"
#include "huffmanTree.hpp"
#include <iostream>
using namespace std;
HuffmanCompress::HuffmanCompress()
{
	_charinfo.resize(256);
	for (size_t i = 0; i < 256; ++i)
	{
		_charinfo[i].ch = i;
		_charinfo[i].appearCount = 0;
	}
}
void CompressFile(string& filePath)
{
	//统计文件中每个字符出现的次数
	FILE* fIn = fopen(filePath.c_str(), "r");
	if (nullptr == fIn)
	{
		cout << "该压缩文件路径出错" << endl;
		return;
	}
	char readBuff[1024];
	while (true)
	{
		size_t rdsize = fread(readBuff, 1, 1024, fIn);
		if (rdsize == 0)
		{
			break;
		}
		for (size_t i = 0; i < rdsize; ++i)
		{
			_charinfo[readBuff[i]].appearCount++;
		}
	}
	//以Chinfo作为权值去常见huffman树
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charinfo);
	//在获取每个字符对应的huffman编码
	GenetCode(ht)
	fclose(fIn);
}
//先走到叶子节点的位置，然后顺着叶子节点向上进行编码的获取
void HuffmanCompress::GeneteCode(HuffmanTreeNode<CharInfo>* root)
{
	if (nullptr == root)
		return;
	GeneteCode(root->_left);
	GeneteCode(root->_right);
	if (nullptr == root->_left && nullptr == root->_right)
	{
		//root是一个叶子节点
		HuffmanTreeNode<CharInfo>* cur = root;
		HuffmanTreeNode<CharInfo>* parent = cur->_parent;
		string strCode = _charinfo[cur->_weight._ch].strCode;
		while (parent)
		{
			if (cur == parent->_left)
				strCode += '0';
			else
				strCode += '1';

			cur = parent;
			parent = cur->_parent;
		}
		reverse(strCode.begin(), strCode.end());
	}
}