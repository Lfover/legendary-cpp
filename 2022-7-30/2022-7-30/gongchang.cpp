/*
#include <iostream>
using namespace std;
//����ģʽ
//���൥��
class SingleCode
{
public:
	virtual void show() = 0;
};
//���˵�A����
class SingleCodeA : public SingleCode
{
public:
	void show()
	{
		cout << "Single code A" << endl;
	}
};
//���˵�B����
class SingleCodeB : public SingleCode
{
public:
	void show()
	{
		cout << "Single Code B" << endl;
	}
};
//������
class MultiCode
{
public:
	virtual void show() = 0;
};
//���A
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

//����
class CodeFactory
{
public:
	virtual SingleCode* CreateSingleCode() = 0;
	virtual MultiCode* CreateMultiCode() = 0;
};

//����A
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
//����B
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