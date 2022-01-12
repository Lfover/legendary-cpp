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