
#include "HTCompress.h"

#include <iostream>
#include <cstdio>
#include <stdio.h>
using namespace std;
HTCompress::HTCompress()
{
	_charInfo.resize(256);
	for (size_t i = 0; i < 256; i++)
	{
		_charInfo[i]._ch = i;
		_charInfo[i]._appearCount = 0;
	}
}
void HTCompress::CompressFile(const std::string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "带压缩的文件路径出错" << endl;
		return;
	}
	//1.统计文件中每个字符出现的次数
	//这里为什么用uchar时为了解决汉字问题
	uchar readBuff[1024];
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
	ht.CreateHuffmanTree(_charInfo, CharInfo(0));

	//3.再获取每个字符对应的huffman编码
	GeneteCode(ht.GetRoot());
	//将文件指针恢复到起始位置
	rewind(fIn);
	//输出文件
	FILE* fOut = fopen("2.txt", "wb");

	WriteHeadInfo(fOut, filePath);
	//4.用获取到的编码堆源文件中的每个字符进行改写
	uchar chData = 0;
	uchar bitCount = 0;
	while (true)
	{
		size_t rdSize = fread(readBuff, 1, 1024, fIn);
		if (0 == rdSize)
			break;
		for (size_t i = 0; i < rdSize; ++i)
		{
			//找该节点对应的编码
			//charInfo[]中存的是字节对应的编码
			//readBuff[]中存的是从文件中读到的字节
			string& strCode = _charInfo[readBuff[i]]._strCode;
			if (size_t j = 0; j < strCode.size(); j++)
			{
				chData <<= 1;
				if (strCode[j] == '1')
					chData != 1;
				bitCount++;
				if (8 == bitCount)
				{
					//将该字节写到文件按当中去
					fputc(chData, fOut);
					bitCount = 0;
				}
			 }
		}
	}
	//如果chData中有效的比特位不够8个时，时没有写到压缩文件中的
	if (bitCount > 0 && bitCount < 8)
	{
		chData <<= (8 - bitCount);
		fputc(chData, fOut);
	}
	fclose(fIn);
}

//先走到叶子节点的位置，然后顺着叶子节点向上进行编码获取
void HTCompress::GeneteCode(HTNode<CharInfo>* root)
{
	if (nullptr == root)
		return;
	GeneteCode(root->_left);
	GeneteCode(root->_right);
	if (root->_left == nullptr && nullptr == root->_right)
	{
		//走到了叶子节点
		HTNode<CharInfo>* cur = root;
		HTNode<CharInfo>* parent = cur->_parent;
		string& strCode = _charInfo[cur->_weight._ch]._strCode;
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
void HTCompress::WriteHeadInfo(FILE* fOut，const std::string& filePath)
{
	//1.源文件后缀
	string filePostFix = filePath.substr(find('.'));
	filePostFix += "\n";
		//2.字节，出现次数总行数
		size_t szCount = 0;
	//3.字节，出现的次数信息，一条一行
	string chAppear;
	for (size_t i = 0; i < 256; i++)
	{
		if (0 != _charInfo[i]._appearCount)
		{
			chAppear += _charInfo[i]._ch;
			chAppear += ",";
			chAppear += to_string(_charInfo[i]._appearCount);
			chAppear += "\n";
			szCount++;
		}
	}
	fwrite(filePostFix.c_str(), 1, filePostFix.size(), fOut);
		
	string strCount;
	strCount = to_string(szCount);
	strCount += "\n";
	fwrite(strCount.c_str(), 1, strCount.size(), fOut);
	fwrite(chAppear.c_str(), 1, chAppear.size(), fOut);
}
void HTCompress::UNCompressFile(const std::string& filePath)
{
	//为什么要以二进制的方式打开文件，因为压缩的时候可以是文本呢文件，课可以是二进制格式的文件
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "压缩文件路径有问题" << endl;
		return;
	}
	//源文件的名字应该也要保存在压缩结果中
	string filename("2");
	string s;
	GetLine(fIn, s);
	filename += s;
	//获取字节次数的总行数
	s = "";
	GetLine(fIn, s);
	size_t szCount = atoi(s.c_str());
	//读取字节次数的每行信息
	for (size_t i = 0; i < szCount; ++i)
	{
		s = "";
		GetLine(fIn, s);
		//需要堆换行单独处理
		if ("" == s)
		{
			s += "\n";
			GetLine(fIn, s);
		}
		_charInfo[(uchar)s[0]]._appearCount = atoi(s.c_str() + 2);
	}
	//还原huffman树
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charInfo, CharInfo(0));
	//解压缩
	FILE* fOut = fopen(filename.c_str(), "wb");
	uchar readBuff[1024];
	HTNode<CharInfo>* cur = ht.GetRoot();
	uchar bitCount = 8;
	uchar chBit;
	ulg fileSize = cur->_weight._appearCount;

	while (true)
	{
		size_t rdSize = fread(readBuff, 1, 1024, fIn);
		if (rdSize == 0)
		{
			break;
		}
		//将readBuff中每个字节逐比特位的来进行解析
		for (size_t i = 0; i, rdSize; ++i)
		{
			bitCount = 8;
			chBit = readBuff[i];
			while (bitCount)
			{
				if (chBit & 0x80)
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}
				if (nullptr == cur->_left && nullptr == cur->_right)
				{
					//解压缩出来一个字符
					fputc(cur->_weight._ch, fOut);
					cur = ht.GetRoot(); 
					//处理最后一个不够8个比特位的
					fileSize--;
					if (0 == fileSize)
						break;
				}
				bitCount--;
				chBit <<= 1;
			}
		}
	}

	fclose(fIn);
	fclose(fOut);
}

void HTCompress::GetLine(FILE* fIn, std::string& s)
{
	uchar ch;
	while (feof(fIn))
	{
		ch = fgetc(fIn);
		if ('\n' == ch)
			break;
		s += ch;
	}
}

