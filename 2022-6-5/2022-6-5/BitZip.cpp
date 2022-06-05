#include <iostream>
#include <assert.h>
#include <map>
using namespace std;

#include "BitZip.h"

struct IntervalSolution
{
	ush code;               // 区间编号
	uch extraBit;           // 扩展码
	ush interval[2];        // 改区间中包含多少个数字
};

/*************************************************************/
//距离表
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
//长度表
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
		cout << "打开文件失败" << endl;
		return false;
	}

	//获取文件大小
	fseek(fIn, 0, SEEK_END);
	ulg fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);

	// 文件大小小于3个字节，不需要进行压缩
	if (fileSize < 3)
	{
		fclose(fIn);
		return true;
	}

	// 获取待压缩文件的后缀，保存到压缩文件中，解压缩的时候需要使用
	string fileExt;
	fileExt = filePath.substr(filePath.rfind(".") + 1);
	fileExt += "\n";

	// 用来写压缩数据的文件
	string compressFileName;
	compressFileName = filePath.substr(0, filePath.rfind("."));
	compressFileName += ".bzp";
	fOut = fopen(compressFileName.c_str(), "wb");
	fwrite(fileExt.c_str(), 1, fileExt.size(), fOut);

	// 先读取一个缓冲区的数据
	// _lookAhead:带压缩数据的个数
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
		// 将start为首的三个字符插入到哈希表中
		_ht.Insert(hashAddr, _pWin[_start + 2], _start, matchHead);

		// 找最长匹配
		ush curMatchDist = 0;
		uch curMatchLen = 0;
		if (matchHead)
		{
			curMatchLen = LongMatch(matchHead, curMatchDist);
		}

		if (curMatchLen < MIN_MATCH)
		{
			// 统计其个数，到时给出去用来创建huffman树
			SaveLZ77Result(0, _pWin[_start], chFlag, bitCount);
			++_start;
			--_lookAhead;
		}
		else
		{
			// 统计距离个数，用来创建huffman树进行进一步压缩
			SaveLZ77Result(curMatchDist, curMatchLen - 3, chFlag, bitCount);
			_lookAhead -= curMatchLen;

			// 更新哈希表
			curMatchLen -= 1;
			while (curMatchLen)
			{
				++_start;
				_ht.Insert(hashAddr, _pWin[_start + 2], _start, matchHead);
				curMatchLen--;
			}
			++_start;
		}

		// 窗口中数据如果不够，向窗口中填充数据
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

// matchHead--->哈希匹配链起始位置
uch BitZip::LongMatch(ush matchHead, ush& curMatchDist)
{
	uch curMatchLen = 0;
	uch maxLen = 0;
	ush pos = 0;
	uch Matchchainlen = 255;

	// 因此只搜索_start左边MAX_DIST范围内的串
	ush limit = _start > MAX_DIST ? _start - MAX_DIST : 0;
	do
	{
		uch* pStart = _pWin + _start;
		uch* pEnd = pStart + MAX_MATCH;

		// 在查找缓冲区中找到匹配串的起始位置
		uch* pCurStart = _pWin + matchHead;
		curMatchLen = 0;

		// 找单条链的匹配长度
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

	// 如果距离太远就丢弃掉了
	if (curMatchDist > MAX_DIST)
		maxLen = 0;

	return maxLen;
}

void BitZip::FillWindow(FILE* fIn)
{
	// 将右窗口中数据搬移到左窗口
	if (_start >= WSIZE + MAX_DIST)
	{
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		memset(_pWin + WSIZE, 0, WSIZE);
		_start -= WSIZE;

		// 更新哈希表
		_ht.Update();
	}

	// 向右窗口中填充数据
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
		// 距离对
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
		// 使用huffman对结果进行压缩
		if (0 == _lookAhead)
			_isLast = true;

		CompressFileHuffman();
	}
}

void BitZip::WriteCodeInfo(FILE* fOut)
{
	// 标记是否是最后一个块
	if (_isLast)
		fputc(1, fOut);
	else
		fputc(0, fOut);

	// 真正的zip此处使用的是游程编码
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
			// 长度距离对
			_charlenInfo[GetSeconIndex(_bytelenData[i]) + 257]._charCount++;
			_distInfo[GetSeconIndex(_distData[distIdx++])]._charCount++;
		}
		else
		{
			// 当前位置为原字符
			_charlenInfo[_bytelenData[i]]._charCount++;
		}

		chFlag <<= 1;
		bitCount--;
	}

	// 该块的结尾标记
	_charlenInfo[256]._charCount = 1;
}

void BitZip::CompressFileHuffman()
{
	InitCharInfoArray();

	// 1. 统计每个字节出现的次数
	StatAppearCount();

	// 2. 以每个字符出现的次数为权值创建huffman树
	HuffmanTree<CharInfo> clTree;
	clTree.CreatHuffmanTree(_charlenInfo, CharInfo(0));

	HuffmanTree<CharInfo> distTree;
	distTree.CreatHuffmanTree(_distInfo, CharInfo(0));

	// 3. 以范式huffman树的方式获取字符长度树的编码
	GetCodeLen(clTree.GetRoot(), _charlenInfo);
	GenerateCode(_charlenInfo);

	GetCodeLen(distTree.GetRoot(), _distInfo);
	GenerateCode(_distInfo);

	// 开始压缩
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
			// 当前为长度距离对: 先压缩长度，再压缩距离
			CompressLengthDist(_bytelenData[i], _distData[distIdx++], ch, bitCount);
		}
		else
		{
			// 当前为源字符
			CompressChar(_bytelenData[i], ch, bitCount);
		}

		leftFlagBit--;
		chFlag <<= 1;
	}

	// 压缩一个256表示该块结束
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

// 压缩长度距离对
void BitZip::CompressLengthDist(uch length, ush dist, uch& data, uch& bitCount)
{
	// 压缩长度在huffman树中的编码, 并不是对长度直接进行压缩，而是对区间码进行压缩
	ush index = GetSeconIndex(length);
	ulg code = _charlenInfo[lengthInterval[index].code]._code;
	ulg codeLen = _charlenInfo[lengthInterval[index].code]._len;
	Compress(code, codeLen, data, bitCount);

	// 压缩额外的补位编码
	index = GetSeconIndex(length);
	code = length + 3 - lengthInterval[index].interval[0];
	codeLen = lengthInterval[index].extraBit;
	Compress(code, codeLen, data, bitCount);

	////////////////////////////////////////////////////////////////////
	// 压缩距离
	// 获取dist在huffman树中的编码并压缩
	index = GetSeconIndex(dist);
	code = _distInfo[index]._code;
	codeLen = _distInfo[index]._len;
	Compress(code, codeLen, data, bitCount);

	// 压缩额外的补位编码
	index = GetSeconIndex(dist);
	code = dist - distInterval[index].interval[0];
	codeLen = distInterval[index].extraBit;
	Compress(code, codeLen, data, bitCount);
}

// 压缩源字符
void BitZip::CompressChar(ush ch, uch& data, uch& bitCount)
{
	ulg charCode = _charlenInfo[ch]._code;
	ulg codeLen = _charlenInfo[ch]._len;

	Compress(charCode, codeLen, data, bitCount);
}

void BitZip::Compress(ulg code, ulg codeLen, uch& data, uch& bitCount)
{
	// 将编码移动到高位
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
		// 找到叶子节点
		codeInfo[pRoot->_weight._ch]._len = len;
		return;
	}

	len += 1;
	GetCodeLen(pRoot->_pLeft, codeInfo, len);
	GetCodeLen(pRoot->_pRight, codeInfo, len);
}

void BitZip::GenerateCode(vector<CharInfo>& codeInfo)
{
	// 对编码位长按照位长第一关键字，编码第二关键字进行排序
	vector<CharInfo> v(codeInfo);
	sort(v.begin(), v.end());

	// 找到码字长度不为0的起始位置
	ush index = 0;
	for (index = 0; index < v.size(); ++index)
	{
		if (0 != v[index]._len)
			break;
	}

	// 范式huffman编码规则：同层编码从小到大增加1
	//                    下一层编码上上传最后一个编码+1左移长度差位
	v[index++]._code = 0;
	ush count = 1;
	for (; index < v.size(); ++index)
	{
		// 同一层的编码：右侧的比左侧的大1
		if (v[index]._len == v[index - 1]._len)
		{
			//v[index]._code = v[index - 1]._code + 1;
			codeInfo[v[index]._ch]._code = codeInfo[v[index - 1]._ch]._code + 1;
			count++;
		}
		else
		{
			// 不同层：第n层的编码可以根据上层算出来：code = (code + count[n-1])<<1
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
	// 读取原字符、长度的码长信息
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

	// 读取距离的码长信息
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
		cout << "解压缩文件格式有误,请输入后缀为.bzp的文件" << endl;
		return false;
	}

	// 打开待压缩文件
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "打开压缩文件失败" << endl;
		return false;
	}

	// 解压缩文件的名字
	string fileName;
	fileName = strFilePath.substr(0, strFilePath.rfind("."));
	fileName += "_d";  // 测试
	fileName += ".";
	fileName += GetLine(fIn);

	fOut = fopen(fileName.c_str(), "wb");
	FILE* f = fopen(fileName.c_str(), "rb");

	// 标记是否为最后一个块
	_isLast = false;
	while (true)
	{
		if (1 == fgetc(fIn))
			_isLast = true;

		// 获取解码时码字长度
		GetDecodeLen(fIn);

		// 构造字符、长度以及距离的解码表
		vector<DecodeTable> byteLengthTab;
		GenerateDecodeTab(_charlenInfo, byteLengthTab);

		vector<DecodeTable> distTab;
		GenerateDecodeTab(_distInfo, distTab);

		// 开始解码：
		uch bitCount = 0;
		uch ch = 0;
		while (true)
		{
			// 先解压一个原字符或者长度
			ush byteOrLength = UNCompressSymbol(fIn, _charlenInfo, byteLengthTab, ch, bitCount);
			if (byteOrLength < 256)
			{
				// 解压出来的是一个原字符，直接写入到文件
				fputc(byteOrLength, fOut);
			}
			else if (byteOrLength == 256)
			{
				break;
			}
			else
			{
				ush code = 0;
				// 长度 = 起始值 + 额外比特位
				ush length = lengthInterval[byteOrLength - 257].interval[0];

				// 获取额外的比特位
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

				// 解压出来的byteOrLength是一个长度，次数需要解压出距离
				ush dist = UNCompressSymbol(fIn, _distInfo, distTab, ch, bitCount);
				ush distBase = distInterval[dist].interval[0];

				// 获取距离的额外比特位
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
		// 中间可能会有一些长度没有出现，比如：
		// len:7---> code:126
		// len:9---> code:508
		// 次数需要一次性读取两位，但是i只加一次
		ush lenGap = decTable[i]._decodeLen - decTable[i - 1]._decodeLen;
		while (lenGap--)
		{
			GetNextBit(fIn, code, ch, bitCount);
		}
	}

	// 找出扩展的比特位
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

// 生成解码表
void BitZip::GenerateDecodeTab(vector<CharInfo>& codeInfo, vector<DecodeTable>& decTable)
{
	// 解码信息表：按照码长第一关键字，符号第二关键字小于的方式排序
	sort(codeInfo.begin(), codeInfo.end());

	// 统计相同编码长度的个数
	map<int, uch> m;
	for (auto e : codeInfo)
		m[e._len]++;

	int index = 0;   // 首字符下标
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
