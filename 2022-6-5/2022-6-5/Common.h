#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;


typedef unsigned short ush;
typedef unsigned char uch;
typedef unsigned long long ulg;



// LZ77�л������ڵĴ�С
const static size_t WSIZE = 32 * 1024;

// LZ77����Сƥ�䳤��Ϊ3������ƥ�䳤��Ϊ258��ƥ�䳤�Ƚ����պÿ���ʹ��һ���ֽڽ��д洢
// ������Ƶ�Ŀ���ǣ����Խ�ԭ�ַ���ƥ�䳤��ʹ��һ��huffman������ѹ��
const static size_t MIN_MATCH = 3;
const static size_t MAX_MATCH = 255 + 3;