#include <iostream>
#include <Windows.h>
using namespace std;


//class A
//{
//public:
//	//���壺��Ա�����ͳ�Ա�������
//	void test()
//	{
//		cout << this << endl;
//	}
//	char c;
//	int b;
//};//ע�⣬һ��Ҫ���ֺ�
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