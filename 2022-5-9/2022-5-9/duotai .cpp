/*
#include <iostream>
using namespace std;

class Person
{
public:
	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }
};
class Student : public Person
{
public:
	virtual void BuyTicket() { cout << "��Ʊ-���" << endl; }
};
void fun(Person& p)
{
	p.BuyTicket();
}
int main()
{
	Person Li;
	fun(Li);
	Student Ru;
	fun(Ru);
	return 0;
}
*/
#include <iostream>
using namespace std;

class Person
{
public:
	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }
	virtual void BuyTicket1() { cout << "��Ʊ-ȫ��" << endl; }
};
class Student : public Person
{
public:
	virtual void BuyTicket() { cout << "��Ʊ-���" << endl; }
	virtual void BuyTicket1() { cout << "��Ʊ-���" << endl; }
	virtual void BuyTicket2() { cout << "��Ʊ-���" << endl; }
};
typedef void(*VFPTR) ();
void Print(VFPTR vtable[])
{
	cout << "����ַ" << vtable << endl;
 	for (int i = 0; vtable[i] != nullptr; ++i)
	{
		printf("��%d���麯���ĵ�ַ �� 0X%x, ->", i, vtable[i]);
		VFPTR f = vtable[i];
		f();
	}
	cout << endl;
}
int main()
{
	Person Li;
	Student Ru;
	VFPTR* vtabled = (VFPTR*)(*(int*)&Li);
	Print(vtabled);

	vtabled = (VFPTR*)(*(int*)&Ru);
	Print(vtabled);
	return 0;
}