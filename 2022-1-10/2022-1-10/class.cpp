#include <iostream>
#include <Windows.h>
using namespace std;



class A
{
	//���壺��Ա�����ͳ�Ա�������
	void test();
	char c;
	int b;
};//ע�⣬һ��Ҫ���ֺ�
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