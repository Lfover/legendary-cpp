#include <iostream>
using namespace std;

#if 0
//基类
class B
{
public:
	void test(){}
	int _b;
};

//继承类B
class C1 :public B
{
public:
	int _c1;
};
//继承类B
class C2 :public B
{
public: 
	int _c2;
};
//继承C1,C2类
class D :public C1, public C2
{
public:
	int _d;
};

//测试函数
void TestD()
{
	cout << sizeof(D) << endl;

	//创建D类的对象
	D d;
	d.C1::_b = 1;
	d.C2::_b = 4;
	d._c1 = 2;
	d._c2 = 3;
	d._d = 5;
}

//主函数
int main()
{
	TestD();
	return 0;
}

#endif

#if 0
//基类
class B
{
public:
	int _b;
};

//子类，共有继承B
class D : virtual public B//虚拟继承
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