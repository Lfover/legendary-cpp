#include <iostream>
#include <string.h>
using namespace std;

//class String
//{
//public:
//	//���캯��
//	String(const char* str = "")
//	{
//		if (nullptr == str)
//		{
//			str = "";
//		}
//		_str = new char[strlen(str) + 1];
//		strcpy(_str, str);
//	}
//	//�������캯��
//	String(const String& s)
//		:_str(new char[strlen(s._str) + 1])
//	{
//		strcpy(_str, s._str);
//	}
//	//��ֵ���������
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
//	//��������
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
	//���캯��
	String(const char* str = "")
	{
		if (nullptr == str)
		{
			str = "";
		}
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	//�������캯��
	String(const String& s)
		:_str(nullptr)
	{
		String strTemp(s._str);
		std::swap(_str, strTemp._str);
	}
	//��ֵ���������
	String& operator=(String& s)
	{
		std::swap(_str, s._str);
		return *this;
	}
	//��������
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
	//���ַ���""��һ����Ч���ַ�����ֻ��������洢��ֻ��һ��\0
	//��   nullptr
	String s1;
	String s2("hello");
	String s3(nullptr);
	//String s4("world");
	//s4 = s2;//ǳ��������Դй¶
	String s5(s2);//���
}

int main()
{
	TestString1();
	return 0;
}