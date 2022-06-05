#include "LZ77.h"
#include <iostream>
#include "HashTable.h"
#include <assert.h>
const static ush WSIZE = 0x8000;
using namespace std;

LZ77::LZ77()
	: _pWin(new uch[2 * WSIZE])
	, _ht(WSIZE)
{}
LZ77::~LZ77()
{
	delete[] _pWin;
	_pWin = nullptr;
}
void LZ77::CompressLZ77(const string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	//����ļ�С�������ֽڲ�ѹ��������Ҫ��ȡ�ļ���С
	fseek(fIn, 0, SEEK_END);
	ulg fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	if (fileSize < 3)
	{
		cout << "�ļ�̫С����ѹ��" << endl;
		return;
	}
	//��һ�����ڵ�����
	ulg lookahead = fread(_pWin, 1, 2 * WSIZE, fIn);
	ush hashAddr  = 0;
	ush matchHead = 0;
	for (ush i = 0; i < MIN_MATCH - 1; i++)
	{
		_ht.Insert(hashAddr, _pWin[i], i, matchHead);
	}
	FILE* fOut = fopen("111.txt", "wb");
	//���ļ�������д�����Ϣ��
	FILE* fFlag = fopen("temp.txt", "wb");
	ush start = 0;
	ush curMatchLength = 0;
	ush curMatchDist = 0;

	uch ch = 0;
	uch bitCount = 0;
	while (lookahead)
	{
		//�����ַ�һ�飬����

		_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
		if (0 == matchHead)
		{
			//�������ֽ�û��ƥ���
			fputc(_pWin[start], fOut);
			start++;
			lookahead--;
			writeFlag(fFlag, false, ch, bitCount);
		}
		else
		{
			//���ƥ��
			//������������ҵ����ƥ��
			curMatchLength = LongestMatch(matchHead, start, curMatchDist);
			fputc(curMatchLength - 3, fOut);
			fwrite(&curMatchDist, 2, 1, fOut);
			writeFlag(fFlag, true, ch, bitCount);
			lookahead -= curMatchLength;
			//��Ҫ��ƥ������������ֽ�һ������ϣ����ܲ��� 
			curMatchLength -= 1;//��Ϊatart��ʼ���ֽ��Ѿ������ȥ��
			while (curMatchLength)
			{
				_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
				curMatchLength--;
			}
			
		}

	}
	if (bitCount > 0 && bitCount < 8)
	{
		ch <<= (8 - bitCount);
		fputc(ch, fFlag);
	}
	fclose(fIn);
	
	fclose(fFlag);
	//�ϲ������ļ�
	MergeFile(fOut, fileSize);
	fclose(fOut);
}
//���ļ�����Ҫ���Ҵ��е����ݰ��Ƶ���
ush LZ77::LongestMatch(ush matchHead, ush start, ush& curMatchDist)
{
	ush maxLength = 0;
	ush maxMatchCount = 255;
	ush limit = start > MAX_DIST ? start - MAX_DIST : 0;
	do
	{
		uch* pScan = _pWin + matchHead;
		uch* pEnd = pScan + MAX_MATCH;//MAX_MATCH:258
		uch* pStart = _pWin + start;
		ush curLength = 0;
		ush curDist = 0;
		//��һ��ƥ��
		while (pScan < pEnd && *pScan == *pStart)
		{
			pScan++;
			pStart++;
		} 
		curDist = start - matchHead;
		//ȷ�����ƥ��
		if (curLength > maxLength)
		{
			maxLength = curLength;
			curMatchDist = curDist;
		}

	} while(((matchHead = _ht.GetNext(matchHead)) > limit) && (maxMatchCount--));
	
	return maxLength;
	
}
void WriteFlag(FILE* temp, bool isDist, uch& ch, uch& bitCount)
{
	ch <<= 1;
	if (isDist)
		ch |= 1;
	bitCount++;
	if (8 == bitCount)
	{
		fputc(ch, temp);
		ch = 0;
		bitCount = 0;
	}
}

void LZ77::MergeFile(FILE* fOut, ulg fileSize)
{
	FILE* fFlag = fopen("temp.txt", "rb");
	assert(fFlag);
	uch readBuff[1024];
	size_t flagSize = 0;
	while (true)
	{
		size_t rdSize = fread(readBuff, 1, 1024, fFlag);
		if (rdSize == 0)
			break;
		flagSize += rdSize;
		fwrite(readBuff, 1, rdSize, fOut);

	}
	fwrite(&flagSize, sizeof(flagSize), 1, fOut);
	fwrite(&fileSize, sizeof(fileSize), 1, fOut);
	fclose(fFlag);
	remove("temp.txt");
}
void LZ77::UNCompressLZ77(const string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "��ѹ���ļ�·��������" << endl;
		return;
	}
	//��ȡԴ�ļ��Ĵ�С
	fseek(fIn, 0 - sizeof(ulg), SEEK_END);
	ulg fileSize = 0;
	fread(&fileSize, sizeof(fileSize), 1, fIn);
	//��ȡ��Ǵ�С 
	size_t flagSize = 0;
	fseek(fIn, 0 - sizeof(fileSize) - sizeof(flagSize), SEEK_END);
	fread(&flagSize, sizeof(flagSize), 1, fIn);
	FILE* fFlag = fopen(filePath.c_str(), "rb");  
	fseek(fFlag, 0 - sizeof(fileSize) - sizeof(flagSize) - fileSize, SEEK_END);
	FILE* fOut = fopen("22.txt", "wb");  
	FILE* fRead = fopen("22.txt", "rb");

	uch ch = 0;
	uch bitCount = 0;
	size_t i = 0;
	uch chData = 0;
	ulg compressCount = 0;


	while (i < flagSize)
	{
		if (0 == bitCount)
		{
			ch = fgetc(fFlag);
			bitCount = 8;
			i++; 
		}
		if(ch & 0x80)
		{
			//���Ⱦ����
			ush matchLength = fgetc(fIn) + 3;
			ush matchDist = 0;
			fread(&matchDist, sizeof(matchDist), 1, fIn);
			//ˢ�»�����
			fflush(fOut);
			fseek(fRead, 0 - matchDist, SEEK_END);
			compressCount += matchLength;
			
			while (matchLength)
			{
				chData = fgetc(fRead);
				fputc(chData, fOut);
				fflush(fOut);
				matchLength--;
			}
		}
		else
		{
			chData = fgetc(fIn);
			fputc(chData, fOut);
			compressCount++;
		}
		bitCount--;
		ch <<= 1;
		if (compressCount == fileSize)
		{
			break;
		}
	}
	fclose(fIn);
	fclose(fFlag);
	fclose(fOut);
	fclose(fRead);		
}