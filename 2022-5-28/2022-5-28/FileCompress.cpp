#include "FileCompress.h"


FileCompress::FileCompress()
{
	for (size_t i = 0; i < 256; ++i)
	{
		fileInfo[i].ch = i;
		fileInfo[i].appearCount = 0;
	}
}

bool FileCompress::CompressFile(const std::string& strFilePath)
{
	// 1. 统计源文件中每个字节出现的次数
	FILE* pf = fopen(strFilePath.c_str(), "rb");
	if (NULL == pf)
	{
		return false;
	}

	uchar readBuff[1024];
	while (true)
	{
		size_t rdsize = fread(readBuff, 1, 1024, pf);
		if (0 == rdsize)
			break;

		for (size_t i = 0; i < rdsize; ++i)
		{
			// 统计
			fileInfo[readBuff[i]].appearCount++;
		}
	}

	// 2. 创建huffman树
	HuffmanTree<CharInfo> ht;
	CharInfo invalid;
	invalid.appearCount = 0;
	ht.CreateHuffmanTree(fileInfo, 256, invalid);

	// 3. 根据huffman树找每个字节的编码
	GenerateCode(ht.GetRoot());

	// 4. 需要写入解压缩时需要用到的信息
	FILE* fOut = fopen("2.txt", "wb");
	if (NULL == fOut)
	{
		fclose(pf);
		return false;
	}
	WriteFileHead(fOut, strFilePath);

	// 5. 根据找到的编码改写源文件---写压缩数据

	uchar chBit = 0;   // 用来放置转换结果的二进制比特位
	uchar bitCount = 0; // chBit中放置了几个比特位

	// 1. 获取源文件中的内容
	fseek(pf, 0, SEEK_SET);
	while (true)
	{
		size_t rdsize = fread(readBuff, 1, 1024, pf);
		if (0 == rdsize)
			break;

		// 2. 逐个字节来进行转换
		for (size_t i = 0; i < rdsize; ++i)
		{
			auto& strCode = fileInfo[readBuff[i]].strCode;

			// 3. 将该字节对应的字符编码以二进制格式组织--chBit
			for (size_t j = 0; j < strCode.size(); ++j)
			{
				chBit <<= 1;   // chBit末尾添加了一个比特0
				if ('1' == strCode[j])
					chBit |= 1;

				bitCount++;
				if (8 == bitCount)
				{
					// chBit 里面8个比特位已经填充满了
					fputc(chBit, fOut);
					chBit = 0;
					bitCount = 0;
				}
			}
		}
	}

	if (bitCount > 0 && bitCount < 8)
	{
		chBit <<= (8 - bitCount);
		fputc(chBit, fOut);
	}

	fclose(pf);
	fclose(fOut);
	return true;
}

void FileCompress::WriteFileHead(FILE* fOut, const std::string& filePath)
{
	// 1. 保存源文件的后缀
	// xxx.txt
	// D:\FileCompress\FileCompress\xxx.txt
	std::string postFix = filePath.substr(filePath.rfind('.'));
	postFix += "\n";
	fwrite(postFix.c_str(), 1, postFix.size(), fOut);

	// 2. 保存字节频次信息总的行数

	// 3. 保存每行的字符频次信息
	std::string charAppear;
	size_t szLineCount = 0;
	for (auto& e : fileInfo)
	{
		// 将出现次数非0次的字符：字符，出现次数\n
		if (e.appearCount > 0)
		{
			charAppear += e.ch;
			charAppear += ",";  // A,
			charAppear += std::to_string(e.appearCount);   // 1234 ---> "1234"
			charAppear += "\n";
			szLineCount++;
		}  // A,1\nB,3\nC,5\nD,7\n
	}

	std::string strLineCount = std::to_string(szLineCount);
	strLineCount += "\n";
	fwrite(strLineCount.c_str(), 1, strLineCount.size(), fOut);

	fwrite(charAppear.c_str(), 1, charAppear.size(), fOut);
}

void FileCompress::GenerateCode(HTNode<CharInfo>* root)
{
	if (NULL == root)
		return;

	if (NULL == root->left && NULL == root->right)
	{
		// 从叶子一直向根节点方向移动找编码
		HTNode<CharInfo>* cur = root;
		HTNode<CharInfo>* parent = cur->parent;

		auto& strCode = fileInfo[cur->weight.ch].strCode;
		while (parent)
		{
			if (cur == parent->left)
				strCode += '0';
			else
				strCode += '1';

			cur = parent;
			parent = cur->parent;
		}

		reverse(strCode.begin(), strCode.end());
	}

	GenerateCode(root->left);
	GenerateCode(root->right);
}


bool FileCompress::UNCompressFile(const std::string& strFilePath)
{
	FILE* fIn = fopen(strFilePath.c_str(), "rb");

	// 获取解压缩需要的信息---一次读取一行的内容
	std::string szContent;
	GetLine(fIn, szContent);
	std::string postFix = szContent;

	szContent = "";
	GetLine(fIn, szContent);   // "4"

	size_t lineCount = atoi(szContent.c_str());
	for (size_t i = 0; i < lineCount; ++i)
	{
		szContent = "";
		GetLine(fIn, szContent);  // "A,1"
		if (szContent == "")
		{
			// 遇到的是\n
			szContent += "\n";
			GetLine(fIn, szContent);
		}

		uchar ch = szContent[0];
		fileInfo[ch].appearCount = atoi(szContent.c_str() + 2);
	}

	// 还原huffman
	HuffmanTree<CharInfo> ht;
	CharInfo invalid;
	invalid.appearCount = 0;
	ht.CreateHuffmanTree(fileInfo, sizeof(fileInfo) / sizeof(fileInfo[0]), invalid);

	std::string fileName("3");
	fileName += postFix;
	FILE* fOut = fopen(fileName.c_str(), "wb");

	// 解压缩
	uchar readBuff[1024];
	HTNode<CharInfo>* cur = ht.GetRoot();
	size_t filesize = cur->weight.appearCount;
	size_t unCompressSize = 0;
	while (true)
	{
		// 读取压缩数据
		size_t rdsize = fread(readBuff, 1, 1024, fIn);
		if (0 == rdsize)
			break;

		// 逐个对rdBuff中的每个字节进行解析
		// 按照该字节中的二进制比特位--从高位往低位逐个比特位解析
		// 解析：就是按照比特位的值去遍历huffman树--一直遍历到叶子节点的位置
		for (size_t i = 0; i < rdsize; ++i)
		{
			// rdBuff[i]
			uchar ch = readBuff[i];
			for (size_t j = 0; j < 8; ++j)
			{
				// 检测ch最高是1还是0
				if (ch & 0x80)
					cur = cur->right;
				else
					cur = cur->left;

				ch <<= 1;

				if (NULL == cur->left && NULL == cur->right)
				{
					// cur一定是叶子节点
					fputc(cur->weight.ch, fOut);
					cur = ht.GetRoot();
					unCompressSize++;
					if (filesize == unCompressSize)
						break;
				}
			}
		}
	}

	fclose(fIn);
	fclose(fOut);
	return true;
}

// 按照行获取文件中内容
void FileCompress::GetLine(FILE* fIn, std::string& szContent)
{
	while (!feof(fIn))
	{
		uchar ch = fgetc(fIn);
		if (ch == '\n')
			return;

		szContent += ch;
	}
}