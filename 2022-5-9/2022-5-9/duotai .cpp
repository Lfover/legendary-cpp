/*
#include <iostream>
using namespace std;

class Person
{
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
};
class Student : public Person
{
public:
	virtual void BuyTicket() { cout << "买票-半价" << endl; }
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
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
	virtual void BuyTicket1() { cout << "买票-全价" << endl; }
};
class Student : public Person
{
public:
	virtual void BuyTicket() { cout << "买票-半价" << endl; }
	virtual void BuyTicket1() { cout << "买票-半价" << endl; }
	virtual void BuyTicket2() { cout << "买票-半价" << endl; }
};
typedef void(*VFPTR) ();
void Print(VFPTR vtable[])
{
	cout << "虚表地址" << vtable << endl;
 	for (int i = 0; vtable[i] != nullptr; ++i)
	{
		printf("第%d各虚函数的地址 ： 0X%x, ->", i, vtable[i]);
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