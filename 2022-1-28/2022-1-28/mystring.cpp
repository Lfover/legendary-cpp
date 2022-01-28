#include <iostream>
#include <string.h>
using namespace std;

//class String
//{
//public:
//	//构造函数
//	String(const char* str = "")
//	{
//		if (nullptr == str)
//		{
//			str = "";
//		}
//		_str = new char[strlen(str) + 1];
//		strcpy(_str, str);
//	}
//	//拷贝构造函数
//	String(const String& s)
//		:_str(new char[strlen(s._str) + 1])
//	{
//		strcpy(_str, s._str);
//	}
//	//赋值运算符重载
//	String& operator=(const String& s)
//	{
//		if (this != &s)
//		{
//			char* temp = new char[strlen(s._str) + 1];
//			strcpy(temp, s._str);
//			delete[] _str;
//			_str = temp;
//		}
//		return *this;
//	}
//	//析构函数
//	~String()
//	{
//		if (_str)
//		{
//			delete[] _str;
//			_str = nullptr;
//		}
//	}
//
//private:
//	char* _str;
//
//};

class String
{
public:
	//构造函数
	String(const char* str = "")
	{
		if (nullptr == str)
		{
			str = "";
		}
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	//拷贝构造函数
	String(const String& s)
		:_str(nullptr)
	{
		String strTemp(s._str);
		std::swap(_str, strTemp._str);
	}
	//赋值运算符重载
	String& operator=(String& s)
	{
		std::swap(_str, s._str);
		return *this;
	}
	//析构函数
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}

private:
	char* _str;

};

void TestString1()
{
	//空字符串""是一个有效的字符串，只不过里面存储的只有一个\0
	//空   nullptr
	String s1;
	String s2("hello");
	String s3(nullptr);
	//String s4("world");
	//s4 = s2;//浅拷贝，资源泄露
	String s5(s2);//深拷贝
}

int main()
{
	TestString1();
	return 0;
}