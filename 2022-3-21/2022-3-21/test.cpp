//#include <iostream>
//
//using namespace std;
//int& Add(int a, int b)
//{
//	int c = a + b;
//	return c;
//}
//int main()
//{
//	int& ret = Add(1, 2);
//	Add(3, 4);
//	cout << ret << endl;
//	system("pause");
//	return 0;
//}

//#include <iostream>
//
//#include <time.h>
//using namespace std;
//struct A
//{
//	int a[10000];
//};
//void Test1(A a){}
//
//void Test2(A& a) {}
//
//void Test()
//{
//	A a;
//	//��ֵ��Ϊ��������
//	size_t begin1 = clock();
//	for (size_t i = 0; i < 10000; ++i)
//		Test1(a);
//	size_t end1 = clock();
//
//	//��������Ϊ��������
//	size_t begin2 = clock();
//	for (size_t i = 0; i < 10000; ++i)
//		Test2(a);
//	size_t end2 = clock();
//	//�ֱ���������������н������ʱ��
//	cout << "Test1(A)-time:" << end1 - begin1 << endl;
//	cout << "Test2(A&)-time:" << end2 - begin2 << endl;
//}
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}


#include <time.h>
#include <iostream>
using namespace std;
struct A
{
	int a[10000];
};
A a;
//ֵ����
void Test1(){ return a; }
//���÷���
void Test2() { return a; }

void Test()
{
	//��ֵ��Ϊ��������ֵ����
	size_t begin1 = clock();
	for (size_t i = 0; i < 100000; ++i)
		Test1();
	size_t end1 = clock();

	//��������Ϊ�����ķ���ֵ����
	size_t begin2 = clock();
	for (size_t i = 0; i < 100000; ++i)
		Test2();
	size_t end2 = clock();
	//�ֱ���������������н������ʱ��
	cout << "Test1-time:" << end1 - begin1 << endl;
	cout << "Test2-time:" << end2 - begin2 << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}