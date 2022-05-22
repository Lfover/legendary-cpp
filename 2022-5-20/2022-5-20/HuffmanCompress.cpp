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
	//ͳ���ļ���ÿ���ַ����ֵĴ���
	FILE* fIn = fopen(filePath.c_str(), "r");
	if (nullptr == fIn)
	{
		cout << "��ѹ���ļ�·������" << endl;
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
	//��Chinfo��ΪȨֵȥ����huffman��
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charinfo);
	//�ڻ�ȡÿ���ַ���Ӧ��huffman����
	GenetCode(ht)
	fclose(fIn);
}
//���ߵ�Ҷ�ӽڵ��λ�ã�Ȼ��˳��Ҷ�ӽڵ����Ͻ��б���Ļ�ȡ
void HuffmanCompress::GeneteCode(HuffmanTreeNode<CharInfo>* root)
{
	if (nullptr == root)
		return;
	GeneteCode(root->_left);
	GeneteCode(root->_right);
	if (nullptr == root->_left && nullptr == root->_right)
	{
		//root��һ��Ҷ�ӽڵ�
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