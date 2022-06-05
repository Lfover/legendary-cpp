#include <iostream>
#include <assert.h>
#include <map>
using namespace std;

#include "BitZip.h"

struct IntervalSolution
{
	ush code;               // ������
	uch extraBit;           // ��չ��
	ush interval[2];        // �������а������ٸ�����
};

/*************************************************************/
//�����
static IntervalSolution distInterval[] = {
	{ 0, 0, { 1, 1 } },
	{ 1, 0, { 2, 2 } },
	{ 2, 0, { 3, 3 } },
	{ 3, 0, { 4, 4 } },
	{ 4, 1, { 5, 6 } },
	{ 5, 1, { 7, 8 } },
	{ 6, 2, { 9, 12 } },
	{ 7, 2, { 13, 16 } },
	{ 8, 3, { 17, 24 } },
	{ 9, 3, { 25, 32 } },
	{ 10, 4, { 33, 48 } },
	{ 11, 4, { 49, 64 } },
	{ 12, 5, { 65, 96 } },
	{ 13, 5, { 97, 128 } },
	{ 14, 6, { 129, 192 } },
	{ 15, 6, { 193, 256 } },
	{ 16, 7, { 257, 384 } },
	{ 17, 7, { 385, 512 } },
	{ 18, 8, { 513, 768 } },
	{ 19, 8, { 769, 1024 } },
	{ 20, 9, { 1025, 1536 } },
	{ 21, 9, { 1537, 2048 } },
	{ 22, 10, { 2049, 3072 } },
	{ 23, 10, { 3073, 4096 } },
	{ 24, 11, { 4097, 6144 } },
	{ 25, 11, { 6145, 8192 } },
	{ 26, 12, { 8193, 12288 } },
	{ 27, 12, { 12289, 16384 } },
	{ 28, 13, { 16385, 24576 } },
	{ 29, 13, { 24577, 32768 } }
};
//���ȱ�
static IntervalSolution lengthInterval[] = {
	{ 257, 0, { 3, 3 } },
	{ 258, 0, { 4, 4 } },
	{ 259, 0, { 5, 5 } },
	{ 260, 0, { 6, 6 } },
	{ 261, 0, { 7, 7 } },
	{ 262, 0, { 8, 8 } },
	{ 263, 0, { 9, 9 } },
	{ 264, 0, { 10, 10 } },
	{ 265, 1, { 11, 12 } },
	{ 266, 1, { 13, 14 } },
	{ 267, 1, { 15, 16 } },
	{ 268, 1, { 17, 18 } },
	{ 269, 2, { 19, 22 } },
	{ 270, 2, { 23, 26 } },
	{ 271, 2, { 27, 30 } },
	{ 272, 2, { 31, 34 } },
	{ 273, 3, { 35, 42 } },
	{ 274, 3, { 43, 50 } },
	{ 275, 3, { 51, 58 } },
	{ 276, 3, { 59, 66 } },
	{ 277, 4, { 67, 82 } },
	{ 278, 4, { 83, 98 } },
	{ 279, 4, { 99, 114 } },
	{ 280, 4, { 115, 130 } },
	{ 281, 5, { 131, 162 } },
	{ 282, 5, { 163, 194 } },
	{ 283, 5, { 195, 226 } },
	{ 284, 5, { 227, 257 } },
	{ 285, 0, { 258, 258 } } };
/******************************************************************/

BitZip::BitZip()
	: _pWin(new uch[WSIZE * 2])
	, _ht(WSIZE)
	, _start(0)
	, _lookAhead(0)
	, _isLast(false)
{
	_bytelenData.reserve(0x8000);
	_distData.reserve(0x8000);
	_flag.reserve(0x1000);

	_charlenInfo.resize(286, CharInfo(0));
	for (ush i = 0; i < 286; ++i)
	{
		_charlenInfo[i]._ch = i;
	}

	_distInfo.resize(30, CharInfo(0));
	for (ush i = 0; i < 30; ++i)
	{
		_distInfo[i]._ch = i;
	}
}

BitZip::~BitZip()
{
	if (_pWin)
	{
		delete[] _pWin;
	}
}

bool BitZip::Deflate(const std::string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "���ļ�ʧ��" << endl;
		return false;
	}

	//��ȡ�ļ���С
	fseek(fIn, 0, SEEK_END);
	ulg fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);

	// �ļ���СС��3���ֽڣ�����Ҫ����ѹ��
	if (fileSize < 3)
	{
		fclose(fIn);
		return true;
	}

	// ��ȡ��ѹ���ļ��ĺ�׺�����浽ѹ���ļ��У���ѹ����ʱ����Ҫʹ��
	string fileExt;
	fileExt = filePath.substr(filePath.rfind(".") + 1);
	fileExt += "\n";

	// ����дѹ�����ݵ��ļ�
	string compressFileName;
	compressFileName = filePath.substr(0, filePath.rfind("."));
	compressFileName += ".bzp";
	fOut = fopen(compressFileName.c_str(), "wb");
	fwrite(fileExt.c_str(), 1, fileExt.size(), fOut);

	// �ȶ�ȡһ��������������
	// _lookAhead:��ѹ�����ݵĸ���
	_lookAhead = fread(_pWin, 1, 2 * WSIZE, fIn);

	ush hashAddr = 0;
	for (size_t i = 0; i < MIN_MATCH - 1; ++i)
	{
		_ht.HashFunc(hashAddr, _pWin[i]);
	}

	ush matchHead = 0;
	uch chFlag = 0;
	uch bitCount = 0;

	while (_lookAhead)
	{
		// ��startΪ�׵������ַ����뵽��ϣ����
		_ht.Insert(hashAddr, _pWin[_start + 2], _start, matchHead);

		// ���ƥ��
		ush curMatchDist = 0;
		uch curMatchLen = 0;
		if (matchHead)
		{
			curMatchLen = LongMatch(matchHead, curMatchDist);
		}

		if (curMatchLen < MIN_MATCH)
		{
			// ͳ�����������ʱ����ȥ��������huffman��
			SaveLZ77Result(0, _pWin[_start], chFlag, bitCount);
			++_start;
			--_lookAhead;
		}
		else
		{
			// ͳ�ƾ����������������huffman�����н�һ��ѹ��
			SaveLZ77Result(curMatchDist, curMatchLen - 3, chFlag, bitCount);
			_lookAhead -= curMatchLen;

			// ���¹�ϣ��
			curMatchLen -= 1;
			while (curMatchLen)
			{
				++_start;
				_ht.Insert(hashAddr, _pWin[_start + 2], _start, matchHead);
				curMatchLen--;
			}
			++_start;
		}

		// ��������������������򴰿����������
		if (_lookAhead <= MIN_LOOKAHEAD)
			FillWindow(fIn);
	}

	if (_bytelenData.size() != 0)
	{
		if (bitCount > 0 && bitCount < 8)
		{
			chFlag <<= (8 - bitCount);
			_flag.push_back(chFlag);
		}

		_isLast = true;
		CompressFileHuffman();
	}

	fclose(fIn);
	fclose(fOut);
	return true;
}

// matchHead--->��ϣƥ������ʼλ��
uch BitZip::LongMatch(ush matchHead, ush& curMatchDist)
{
	uch curMatchLen = 0;
	uch maxLen = 0;
	ush pos = 0;
	uch Matchchainlen = 255;

	// ���ֻ����_start���MAX_DIST��Χ�ڵĴ�
	ush limit = _start > MAX_DIST ? _start - MAX_DIST : 0;
	do
	{
		uch* pStart = _pWin + _start;
		uch* pEnd = pStart + MAX_MATCH;

		// �ڲ��һ��������ҵ�ƥ�䴮����ʼλ��
		uch* pCurStart = _pWin + matchHead;
		curMatchLen = 0;

		// �ҵ�������ƥ�䳤��
		while (pStart < pEnd && *pStart == *pCurStart)
		{
			pStart++;
			pCurStart++;
			curMatchLen++;
		}

		if (curMatchLen > maxLen)
		{
			maxLen = curMatchLen;
			pos = matchHead;

			curMatchDist = _start - pos;
		}

	} while (((matchHead = _ht.GetNext(matchHead)) > limit) &&
		Matchchainlen--);

	curMatchDist = _start - pos;

	// �������̫Զ�Ͷ�������
	if (curMatchDist > MAX_DIST)
		maxLen = 0;

	return maxLen;
}

void BitZip::FillWindow(FILE* fIn)
{
	// ���Ҵ��������ݰ��Ƶ��󴰿�
	if (_start >= WSIZE + MAX_DIST)
	{
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		memset(_pWin + WSIZE, 0, WSIZE);
		_start -= WSIZE;

		// ���¹�ϣ��
		_ht.Update();
	}

	// ���Ҵ������������
	if (!feof(fIn))
	{
		_lookAhead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
	}
}

void BitZip::SaveLZ77Result(ush dist, uch ch, uch& flag, uch& bitCount)
{
	_bytelenData.push_back(ch);
	flag <<= 1;
	bitCount++;
	if (0 != dist)
	{
		// �����
		_distData.push_back(dist);
		flag |= 1;
	}

	if (bitCount == 8) {
		_flag.push_back(flag);
		flag = 0;
		bitCount = 0;
	}

	if (_bytelenData.size() == LZ77_BUFF_SIZE || _distData.size() == LZ77_BUFF_SIZE)
	{
		// ʹ��huffman�Խ������ѹ��
		if (0 == _lookAhead)
			_isLast = true;

		CompressFileHuffman();
	}
}

void BitZip::WriteCodeInfo(FILE* fOut)
{
	// ����Ƿ������һ����
	if (_isLast)
		fputc(1, fOut);
	else
		fputc(0, fOut);

	// ������zip�˴�ʹ�õ����γ̱���
	for (auto e : _charlenInfo)
		fputc(e._len, fOut);

	for (auto e : _distInfo)
		fputc(e._len, fOut);
}

void BitZip::InitCharInfoArray()
{
	for (size_t i = 0; i < 286; ++i)
	{
		_charlenInfo[i]._charCount = 0;
		_charlenInfo[i]._code = 0;
		_charlenInfo[i]._len = 0;
	}

	for (size_t i = 0; i < 30; i++)
	{
		_distInfo[i]._charCount = 0;
		_distInfo[i]._code = 0;
		_distInfo[i]._len = 0;
	}
}

size_t BitZip::GetSeconIndex(uch ch)
{
	ush length = ch + 3;
	for (size_t i = 0; i < sizeof(lengthInterval) / sizeof(lengthInterval[0]); ++i)
	{
		if (length >= lengthInterval[i].interval[0] && length <= lengthInterval[i].interval[1])
		{
			return i;
		}
	}

	assert(false);
	return 0;
}

size_t BitZip::GetSeconIndex(ush dist)
{
	for (size_t i = 0; i < sizeof(distInterval) / sizeof(distInterval[0]); ++i)
	{
		if (dist >= distInterval[i].interval[0] && dist <= distInterval[i].interval[1])
		{
			return i;
		}
	}

	assert(false);
	return 0;
}

void BitZip::StatAppearCount()
{
	ush fIdx = 0, distIdx = 0;
	uch bitCount = 0;
	uch chFlag = 0;
	for (size_t i = 0; i < _bytelenData.size(); ++i)
	{
		if (0 == bitCount)
		{
			chFlag = _flag[fIdx++];
			bitCount = 8;
		}

		if (chFlag & 0x80)
		{
			// ���Ⱦ����
			_charlenInfo[GetSeconIndex(_bytelenData[i]) + 257]._charCount++;
			_distInfo[GetSeconIndex(_distData[distIdx++])]._charCount++;
		}
		else
		{
			// ��ǰλ��Ϊԭ�ַ�
			_charlenInfo[_bytelenData[i]]._charCount++;
		}

		chFlag <<= 1;
		bitCount--;
	}

	// �ÿ�Ľ�β���
	_charlenInfo[256]._charCount = 1;
}

void BitZip::CompressFileHuffman()
{
	InitCharInfoArray();

	// 1. ͳ��ÿ���ֽڳ��ֵĴ���
	StatAppearCount();

	// 2. ��ÿ���ַ����ֵĴ���ΪȨֵ����huffman��
	HuffmanTree<CharInfo> clTree;
	clTree.CreatHuffmanTree(_charlenInfo, CharInfo(0));

	HuffmanTree<CharInfo> distTree;
	distTree.CreatHuffmanTree(_distInfo, CharInfo(0));

	// 3. �Է�ʽhuffman���ķ�ʽ��ȡ�ַ��������ı���
	GetCodeLen(clTree.GetRoot(), _charlenInfo);
	GenerateCode(_charlenInfo);

	GetCodeLen(distTree.GetRoot(), _distInfo);
	GenerateCode(_distInfo);

	// ��ʼѹ��
	WriteCodeInfo(fOut);

	uch ch = 0;
	uch bitCount = 0;
	ush flagIdx = 0;
	ush distIdx = 0;
	uch chFlag = 0;
	uch leftFlagBit = 0;
	for (ush i = 0; i < _bytelenData.size(); ++i)
	{
		if (0 == leftFlagBit)
		{
			chFlag = _flag[flagIdx++];
			leftFlagBit = 8;
		}

		if (chFlag & 0x80)
		{
			// ��ǰΪ���Ⱦ����: ��ѹ�����ȣ���ѹ������
			CompressLengthDist(_bytelenData[i], _distData[distIdx++], ch, bitCount);
		}
		else
		{
			// ��ǰΪԴ�ַ�
			CompressChar(_bytelenData[i], ch, bitCount);
		}

		leftFlagBit--;
		chFlag <<= 1;
	}

	// ѹ��һ��256��ʾ�ÿ����
	CompressChar(256, ch, bitCount);
	if (bitCount > 0 && bitCount < 8)
	{
		ch <<= (8 - bitCount);
		fputc(ch, fOut);
	}

	_bytelenData.clear();
	_distData.clear();
	_flag.clear();
}

// ѹ�����Ⱦ����
void BitZip::CompressLengthDist(uch length, ush dist, uch& data, uch& bitCount)
{
	// ѹ��������huffman���еı���, �����ǶԳ���ֱ�ӽ���ѹ�������Ƕ����������ѹ��
	ush index = GetSeconIndex(length);
	ulg code = _charlenInfo[lengthInterval[index].code]._code;
	ulg codeLen = _charlenInfo[lengthInterval[index].code]._len;
	Compress(code, codeLen, data, bitCount);

	// ѹ������Ĳ�λ����
	index = GetSeconIndex(length);
	code = length + 3 - lengthInterval[index].interval[0];
	codeLen = lengthInterval[index].extraBit;
	Compress(code, codeLen, data, bitCount);

	////////////////////////////////////////////////////////////////////
	// ѹ������
	// ��ȡdist��huffman���еı��벢ѹ��
	index = GetSeconIndex(dist);
	code = _distInfo[index]._code;
	codeLen = _distInfo[index]._len;
	Compress(code, codeLen, data, bitCount);

	// ѹ������Ĳ�λ����
	index = GetSeconIndex(dist);
	code = dist - distInterval[index].interval[0];
	codeLen = distInterval[index].extraBit;
	Compress(code, codeLen, data, bitCount);
}

// ѹ��Դ�ַ�
void BitZip::CompressChar(ush ch, uch& data, uch& bitCount)
{
	ulg charCode = _charlenInfo[ch]._code;
	ulg codeLen = _charlenInfo[ch]._len;

	Compress(charCode, codeLen, data, bitCount);
}

void BitZip::Compress(ulg code, ulg codeLen, uch& data, uch& bitCount)
{
	// �������ƶ�����λ
	code <<= (16 - codeLen);
	for (int i = 0; i < codeLen; ++i)
	{
		data <<= 1;
		if (code & 0x8000)
			data |= 1;

		bitCount++;

		if (bitCount == 8)
		{
			fputc(data, fOut);
			data = 0;
			bitCount = 0;
		}

		code <<= 1;
	}
}

void BitZip::GetCodeLen(Node* pRoot, vector<CharInfo>& codeInfo)
{
	int codeLen = 0;
	GetCodeLen(pRoot, codeInfo, codeLen);
}

void BitZip::GetCodeLen(HuffmanTreeNode<CharInfo>* pRoot, vector<CharInfo>& codeInfo, int len)
{
	if (nullptr == pRoot)
		return;

	if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
	{
		// �ҵ�Ҷ�ӽڵ�
		codeInfo[pRoot->_weight._ch]._len = len;
		return;
	}

	len += 1;
	GetCodeLen(pRoot->_pLeft, codeInfo, len);
	GetCodeLen(pRoot->_pRight, codeInfo, len);
}

void BitZip::GenerateCode(vector<CharInfo>& codeInfo)
{
	// �Ա���λ������λ����һ�ؼ��֣�����ڶ��ؼ��ֽ�������
	vector<CharInfo> v(codeInfo);
	sort(v.begin(), v.end());

	// �ҵ����ֳ��Ȳ�Ϊ0����ʼλ��
	ush index = 0;
	for (index = 0; index < v.size(); ++index)
	{
		if (0 != v[index]._len)
			break;
	}

	// ��ʽhuffman�������ͬ������С��������1
	//                    ��һ��������ϴ����һ������+1���Ƴ��Ȳ�λ
	v[index++]._code = 0;
	ush count = 1;
	for (; index < v.size(); ++index)
	{
		// ͬһ��ı��룺�Ҳ�ı����Ĵ�1
		if (v[index]._len == v[index - 1]._len)
		{
			//v[index]._code = v[index - 1]._code + 1;
			codeInfo[v[index]._ch]._code = codeInfo[v[index - 1]._ch]._code + 1;
			count++;
		}
		else
		{
			// ��ͬ�㣺��n��ı�����Ը����ϲ��������code = (code + count[n-1])<<1
			//v[index]._code = (v[index-count]._code + count) << (v[index]._len - v[index - 1]._len);
			codeInfo[v[index]._ch]._code = (codeInfo[v[index - count]._ch]._code + count) << (codeInfo[v[index]._ch]._len - codeInfo[v[index - 1]._ch]._len);
			count = 1;
		}
	}
}

std::string BitZip::GetLine(FILE* fIn)
{
	string s;
	while (!feof(fIn))
	{
		uch ch = fgetc(fIn);
		if ('\n' == ch)
			break;

		s += ch;
	}

	return s;
}

void BitZip::GetDecodeLen(FILE* fIn)
{
	// ��ȡԭ�ַ������ȵ��볤��Ϣ
	_charlenInfo.clear();
	for (size_t i = 0; i < 286; ++i)
	{
		uch len = fgetc(fIn);
		if (0 != len)
		{
			CharInfo charInfo;
			charInfo._ch = i;
			charInfo._len = len;
			_charlenInfo.push_back(charInfo);
		}
	}

	// ��ȡ������볤��Ϣ
	_distInfo.clear();
	for (size_t i = 0; i < 30; ++i)
	{
		uch len = fgetc(fIn);
		if (0 != len)
		{
			CharInfo charInfo;
			charInfo._ch = i;
			charInfo._len = len;
			_distInfo.push_back(charInfo);
		}
	}
}

bool BitZip::unDeflate(const string& strFilePath)
{
	if (strFilePath.substr(strFilePath.rfind(".") + 1) != "bzp")
	{
		cout << "��ѹ���ļ���ʽ����,�������׺Ϊ.bzp���ļ�" << endl;
		return false;
	}

	// �򿪴�ѹ���ļ�
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "��ѹ���ļ�ʧ��" << endl;
		return false;
	}

	// ��ѹ���ļ�������
	string fileName;
	fileName = strFilePath.substr(0, strFilePath.rfind("."));
	fileName += "_d";  // ����
	fileName += ".";
	fileName += GetLine(fIn);

	fOut = fopen(fileName.c_str(), "wb");
	FILE* f = fopen(fileName.c_str(), "rb");

	// ����Ƿ�Ϊ���һ����
	_isLast = false;
	while (true)
	{
		if (1 == fgetc(fIn))
			_isLast = true;

		// ��ȡ����ʱ���ֳ���
		GetDecodeLen(fIn);

		// �����ַ��������Լ�����Ľ����
		vector<DecodeTable> byteLengthTab;
		GenerateDecodeTab(_charlenInfo, byteLengthTab);

		vector<DecodeTable> distTab;
		GenerateDecodeTab(_distInfo, distTab);

		// ��ʼ���룺
		uch bitCount = 0;
		uch ch = 0;
		while (true)
		{
			// �Ƚ�ѹһ��ԭ�ַ����߳���
			ush byteOrLength = UNCompressSymbol(fIn, _charlenInfo, byteLengthTab, ch, bitCount);
			if (byteOrLength < 256)
			{
				// ��ѹ��������һ��ԭ�ַ���ֱ��д�뵽�ļ�
				fputc(byteOrLength, fOut);
			}
			else if (byteOrLength == 256)
			{
				break;
			}
			else
			{
				ush code = 0;
				// ���� = ��ʼֵ + �������λ
				ush length = lengthInterval[byteOrLength - 257].interval[0];

				// ��ȡ����ı���λ
				uch extraBit = lengthInterval[byteOrLength - 257].extraBit;
				ush extraCode = 0;
				while (extraBit--)
				{
					GetNextBit(fIn, code, ch, bitCount);
					extraCode <<= 1;
					if (code & 0x01)
						extraCode |= 1;
				}
				length += extraCode;

				// ��ѹ������byteOrLength��һ�����ȣ�������Ҫ��ѹ������
				ush dist = UNCompressSymbol(fIn, _distInfo, distTab, ch, bitCount);
				ush distBase = distInterval[dist].interval[0];

				// ��ȡ����Ķ������λ
				extraBit = distInterval[dist].extraBit;
				extraCode = 0;
				while (extraBit--)
				{
					GetNextBit(fIn, code, ch, bitCount);
					extraCode <<= 1;
					if (code & 0x01)
						extraCode |= 1;
				}

				distBase += extraCode;
				fflush(fOut);
				fseek(f, 0 - distBase, SEEK_END);
				while (length--)
				{
					uch content = fgetc(f);
					fputc(content, fOut);
					fflush(fOut);
				}
			}
		}

		if (_isLast)
			break;
	}

	fclose(f);
	fclose(fIn);
	fclose(fOut);
	return true;
}

ush BitZip::UNCompressSymbol(FILE* fIn, vector<CharInfo>& codeInfo, vector<DecodeTable>& decTable, uch& ch, uch& bitCount)
{
	ush i = 0;
	ush codeLen = decTable[0]._decodeLen;
	ush code = 0;
	while (codeLen--)
	{
		GetNextBit(fIn, code, ch, bitCount);
	}

	ush num = 0;
	while ((num = code - decTable[i]._code) >= decTable[i]._lenCount)
	{
		i++;
		// �м���ܻ���һЩ����û�г��֣����磺
		// len:7---> code:126
		// len:9---> code:508
		// ������Ҫһ���Զ�ȡ��λ������iֻ��һ��
		ush lenGap = decTable[i]._decodeLen - decTable[i - 1]._decodeLen;
		while (lenGap--)
		{
			GetNextBit(fIn, code, ch, bitCount);
		}
	}

	// �ҳ���չ�ı���λ
	num += decTable[i]._charIndex;
	return codeInfo[num]._ch;
}

void BitZip::GetNextBit(FILE* fIn, ush& code, uch& ch, uch& bitCount)
{
	if (0 == bitCount)
	{
		ch = fgetc(fIn);
		bitCount = 8;
	}

	code <<= 1;
	if (ch & 0x80)
		code |= 1;

	ch <<= 1;
	bitCount--;
}

// ���ɽ����
void BitZip::GenerateDecodeTab(vector<CharInfo>& codeInfo, vector<DecodeTable>& decTable)
{
	// ������Ϣ�������볤��һ�ؼ��֣����ŵڶ��ؼ���С�ڵķ�ʽ����
	sort(codeInfo.begin(), codeInfo.end());

	// ͳ����ͬ���볤�ȵĸ���
	map<int, uch> m;
	for (auto e : codeInfo)
		m[e._len]++;

	int index = 0;   // ���ַ��±�
	for (auto e : m)
	{
		DecodeTable decode;
		decode._decodeLen = e.first;
		decode._lenCount = e.second;
		decode._charIndex = index;
		if (0 == index)
			decode._code = 0;
		else
		{
			DecodeTable& prev = decTable.back();
			decode._code = (prev._code + prev._lenCount) << (e.first - prev._decodeLen);
		}
		decTable.push_back(decode);
		index += decode._lenCount;
	}
}
