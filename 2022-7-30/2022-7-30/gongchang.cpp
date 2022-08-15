/*
#include <iostream>
using namespace std;
//工厂模式
//父类单核
class SingleCode
{
public:
	virtual void show() = 0;
};
//单核的A工厂
class SingleCodeA : public SingleCode
{
public:
	void show()
	{
		cout << "Single code A" << endl;
	}
};
//单核的B工厂
class SingleCodeB : public SingleCode
{
public:
	void show()
	{
		cout << "Single Code B" << endl;
	}
};
//父类多核
class MultiCode
{
public:
	virtual void show() = 0;
};
//多核A
class MultiCodeA : public MultiCode
{
public:
	void show()
	{
		cout << "Multi Code A" << endl;
	}
};
class MultiCodeB : public MultiCode
{
public:
	void show()
	{
		cout << "Multi Code B" << endl;
	}
};

//工厂
class CodeFactory
{
public:
	virtual SingleCode* CreateSingleCode() = 0;
	virtual MultiCode* CreateMultiCode() = 0;
};

//工厂A
class FactoryA : public CodeFactory
{
public:
	SingleCode* CreateSingleCore()
	{
		return new SingleCodeA();
	}
	MultiCode* CreateMultiCore()
	{
		return new MultiCodeA();
	}
};
//工厂B
class FactoryB : public CodeFactory
{
public:
	SingleCode* CreateSingleCore()
	{
		return new SingleCodeB();
	}
	MultiCode* CreateMultiCore()
	{
		return new MultiCodeB();
	}
};
int main()
{
	return 0;
}
*/