
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
		cout << "��ѹ�����ļ�·������" << endl;
		return;
	}
	//1.ͳ���ļ���ÿ���ַ����ֵĴ���
	//����Ϊʲô��ucharʱΪ�˽����������
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
	//2.��ChInfo��ΪȨֵȥ����huffman��
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charInfo, CharInfo(0));

	//3.�ٻ�ȡÿ���ַ���Ӧ��huffman����
	GeneteCode(ht.GetRoot());
	//���ļ�ָ��ָ�����ʼλ��
	rewind(fIn);
	//����ļ�
	FILE* fOut = fopen("2.txt", "wb");

	WriteHeadInfo(fOut, filePath);
	//4.�û�ȡ���ı����Դ�ļ��е�ÿ���ַ����и�д
	uchar chData = 0;
	uchar bitCount = 0;
	while (true)
	{
		size_t rdSize = fread(readBuff, 1, 1024, fIn);
		if (0 == rdSize)
			break;
		for (size_t i = 0; i < rdSize; ++i)
		{
			//�Ҹýڵ��Ӧ�ı���
			//charInfo[]�д�����ֽڶ�Ӧ�ı���
			//readBuff[]�д���Ǵ��ļ��ж������ֽ�
			string& strCode = _charInfo[readBuff[i]]._strCode;
			if (size_t j = 0; j < strCode.size(); j++)
			{
				chData <<= 1;
				if (strCode[j] == '1')
					chData != 1;
				bitCount++;
				if (8 == bitCount)
				{
					//�����ֽ�д���ļ�������ȥ
					fputc(chData, fOut);
					bitCount = 0;
				}
			 }
		}
	}
	//���chData����Ч�ı���λ����8��ʱ��ʱû��д��ѹ���ļ��е�
	if (bitCount > 0 && bitCount < 8)
	{
		chData <<= (8 - bitCount);
		fputc(chData, fOut);
	}
	fclose(fIn);
}

//���ߵ�Ҷ�ӽڵ��λ�ã�Ȼ��˳��Ҷ�ӽڵ����Ͻ��б����ȡ
void HTCompress::GeneteCode(HTNode<CharInfo>* root)
{
	if (nullptr == root)
		return;
	GeneteCode(root->_left);
	GeneteCode(root->_right);
	if (root->_left == nullptr && nullptr == root->_right)
	{
		//�ߵ���Ҷ�ӽڵ�
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
void HTCompress::WriteHeadInfo(FILE* fOut��const std::string& filePath)
{
	//1.Դ�ļ���׺
	string filePostFix = filePath.substr(find('.'));
	filePostFix += "\n";
		//2.�ֽڣ����ִ���������
		size_t szCount = 0;
	//3.�ֽڣ����ֵĴ�����Ϣ��һ��һ��
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
	//ΪʲôҪ�Զ����Ƶķ�ʽ���ļ�����Ϊѹ����ʱ��������ı����ļ����ο����Ƕ����Ƹ�ʽ���ļ�
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "ѹ���ļ�·��������" << endl;
		return;
	}
	//Դ�ļ�������Ӧ��ҲҪ������ѹ�������
	string filename("2");
	string s;
	GetLine(fIn, s);
	filename += s;
	//��ȡ�ֽڴ�����������
	s = "";
	GetLine(fIn, s);
	size_t szCount = atoi(s.c_str());
	//��ȡ�ֽڴ�����ÿ����Ϣ
	for (size_t i = 0; i < szCount; ++i)
	{
		s = "";
		GetLine(fIn, s);
		//��Ҫ�ѻ��е�������
		if ("" == s)
		{
			s += "\n";
			GetLine(fIn, s);
		}
		_charInfo[(uchar)s[0]]._appearCount = atoi(s.c_str() + 2);
	}
	//��ԭhuffman��
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charInfo, CharInfo(0));
	//��ѹ��
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
		//��readBuff��ÿ���ֽ������λ�������н���
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
					//��ѹ������һ���ַ�
					fputc(cur->_weight._ch, fOut);
					cur = ht.GetRoot(); 
					//�������һ������8������λ��
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

