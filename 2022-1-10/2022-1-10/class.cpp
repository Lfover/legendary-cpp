#include <iostream>
#include <Windows.h>
using namespace std;



class A
{
	//类体：成员变量和成员函数组成
	void test();
	char c;
	int b;
};//注意，一定要带分号
class C
{

};



int main()
{
	cout << sizeof(A) << endl;
	cout << sizeof(C) << endl;
	system("pause");
	return 0;
}