#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

//class A
//{
//public:
//	//类体：成员变量和成员函数组成
//	void test()
//	{
//		cout << this << endl;
//	}
//	char c;
//	int b;
//};//注意，一定要带分号
//class C
//{
//
//};
#if 0
class Data
{
public:
	void SetData(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void PrintfData()
	{
		cout << _year << " " << _month << " " << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Data d1, d2, d3;
	d1.SetData(2022, 1, 9);
	d2.SetData(2022, 1, 10);
	d3.SetData(2022, 1, 11);

	d1.PrintfData();
	d2.PrintfData();
	d3.PrintfData();

	cout << sizeof(d1) << endl;
	cout << sizeof(d2) << endl;
	cout << sizeof(d3) << endl;
	system("pause");
	return 0;
	
}
#endif
#if 0
class Data
{
public:
	Data(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	Data(const Data d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	void PrintfData()
	{
		cout << _year << " " << _month << " " << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
#endif
#if 0
class String
{
public:
	String(const char* str = "jack")
	{
		_str = (char *)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}

	~String()
	{
		free(_str);
		_str = nullptr;
	}
private:
	char* _str;
};
int main()
{
	//Data d1(2022, 1, 13);
	//Data d2(d1);
	//int a;
	//int b = 10;
	//int c = b;
	//int d(c);
	String s1("hello world");
	String s2(s1);
	system("pause");
	return 0;
}
#endif
class String
{
public:
	//构造函数
	String(const char* str = "jack")
	{
		_str = (char *)malloc(strlen(str) + 1);
		strcpy(String::_str, str);
	}
	//拷贝构造函数
	String(const string& s)
	{
		cout << "拷贝构造函数" << endl;
	}

	~String()
	{
		if (_str)
		{
			free(_str);
			_str = nullptr;
		}
	}
private:
	char* _str;
};
int main()
{
	String s1("hello world");
	String s2("Hello World");
	s1 = s2;
	system("pause");
	return 0;
}