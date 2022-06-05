#pragma once

#include <string>
#include <vector>
using std::string;
using std::vector;


typedef unsigned short ush;
typedef unsigned char uch;
typedef unsigned long long ulg;



// LZ77中滑动窗口的大小
const static size_t WSIZE = 32 * 1024;

// LZ77中最小匹配长度为3，最大的匹配长度为258，匹配长度将来刚好可以使用一个字节进行存储
// 这样设计的目的是：可以将原字符与匹配长度使用一个huffman树进行压缩
const static size_t MIN_MATCH = 3;
const static size_t MAX_MATCH = 255 + 3;