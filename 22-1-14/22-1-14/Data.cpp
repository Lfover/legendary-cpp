#include <iostream>
#include <Windows.h>

class Date
{
public:
	//构造函数
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
	//拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	//+操作符重载
	Date operator+(const Date& d)//为什么这里用引用，为了提高效率，不用再次调用拷贝构造函数
	{
		Date tem(*this);
		tem._year = (*this)._year + d._year;
		tem._month = (*this)._month + d._month;
		tem._day = (*this)._day + d._day;
		return tem;
	}
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._year;
			_day = d._day;
		}
		return *this;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main()
{
	Date d1(2022, 1, 14);
	Date d2(d1);
	
	Date d3 = d1 + d2;
	d3 = d1;
	return 0;

}