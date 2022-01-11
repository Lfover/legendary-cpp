#include <iostream>
#include <Windows.h>
using namespace std;


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

class Data
{
public:
	//Data(int year, int month, int day)
	//{
	//	_year = year;
	//	_month = month;
	//	_day = day;
	//}
	//Data()
	//{

	//}
	void Set(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Data d();
	//d.Set(100, 12, 12);
	system("pause");
	return 0;
	
}