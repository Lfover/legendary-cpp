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
		cout << "文件打开失败" << endl;
		return;
	}
	//如果文件小于三个字节不压缩，左移要获取文件大小
	fseek(fIn, 0, SEEK_END);
	ulg fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	if (fileSize < 3)
	{
		cout << "文件太小，不压缩" << endl;
		return;
	}
	//读一个窗口的数据
	ulg lookahead = fread(_pWin, 1, 2 * WSIZE, fIn);
	ush hashAddr  = 0;
	ush matchHead = 0;
	for (ush i = 0; i < MIN_MATCH - 1; i++)
	{
		_ht.Insert(hashAddr, _pWin[i], i, matchHead);
	}
	FILE* fOut = fopen("111.txt", "wb");
	//该文件是用来写标记信息的
	FILE* fFlag = fopen("temp.txt", "wb");
	ush start = 0;
	ush curMatchLength = 0;
	ush curMatchDist = 0;

	uch ch = 0;
	uch bitCount = 0;
	while (lookahead)
	{
		//三个字符一组，插入

		_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
		if (0 == matchHead)
		{
			//该三个字节没有匹配的
			fputc(_pWin[start], fOut);
			start++;
			lookahead--;
			writeFlag(fFlag, false, ch, bitCount);
		}
		else
		{
			//找最长匹配
			//依靠这个方法找到最长的匹配
			curMatchLength = LongestMatch(matchHead, start, curMatchDist);
			fputc(curMatchLength - 3, fOut);
			fwrite(&curMatchDist, 2, 1, fOut);
			writeFlag(fFlag, true, ch, bitCount);
			lookahead -= curMatchLength;
			//需要将匹配的内容三个字节一组往哈希表汇总插入 
			curMatchLength -= 1;//因为atart开始的字节已经插入进去了
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
	//合并两个文件
	MergeFile(fOut, fileSize);
	fclose(fOut);
}
//大文件，需要将右窗中的数据搬移到左窗
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
		//找一个匹配
		while (pScan < pEnd && *pScan == *pStart)
		{
			pScan++;
			pStart++;
		} 
		curDist = start - matchHead;
		//确保最长的匹配
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
		cout << "带压缩文件路径有问题" << endl;
		return;
	}
	//获取源文件的大小
	fseek(fIn, 0 - sizeof(ulg), SEEK_END);
	ulg fileSize = 0;
	fread(&fileSize, sizeof(fileSize), 1, fIn);
	//获取标记大小 
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
			//长度距离对
			ush matchLength = fgetc(fIn) + 3;
			ush matchDist = 0;
			fread(&matchDist, sizeof(matchDist), 1, fIn);
			//刷新缓冲区
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