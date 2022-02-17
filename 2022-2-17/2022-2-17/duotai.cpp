#include <iostream>
using namespace std;

#if 0
//����
class B
{
public:
	void test(){}
	int _b;
};

//�̳���B
class C1 :public B
{
public:
	int _c1;
};
//�̳���B
class C2 :public B
{
public: 
	int _c2;
};
//�̳�C1,C2��
class D :public C1, public C2
{
public:
	int _d;
};

//���Ժ���
void TestD()
{
	cout << sizeof(D) << endl;

	//����D��Ķ���
	D d;
	d.C1::_b = 1;
	d.C2::_b = 4;
	d._c1 = 2;
	d._c2 = 3;
	d._d = 5;
}

//������
int main()
{
	TestD();
	return 0;
}

#endif

#if 0
//����
class B
{
public:
	int _b;
};

//���࣬���м̳�B
class D : virtual public B//����̳�
{
public:
	D()
	{
		cout << "D::D()" << endl;
	}
	int _d;
};

void TestD()
{
	cout << sizeof(D) << endl;

	D d;
	d._b = 1;
	d._d = 2;
}

int main()
{
	TestD();
	return 0;
}
#endif

class B
{
public:
	void Test(){}
	int _b;
};

class C1 :virtual public B
{
public:
	int _c1;
};

class C2 :virtual public B
{
public:
	int _c2;
};

class D : public C1, public C2
{
public:
	int _d;
};

int main()
{
	D d;
	d._b = 1;
	d.Test();

	d._b = 1;
	d._c1 = 2;
	d._c2 = 3;
	d._d = 4;

	cout << sizeof(D) << endl;
	return 0;
}