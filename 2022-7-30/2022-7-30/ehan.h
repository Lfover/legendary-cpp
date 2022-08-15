/*
//静态指针，类外初始化
#pragma once
class Singleton
{
protected:
	Singleton() {}
private:
	static Singleton* p;
public:
	static Singleton* initance();
};

Singleton* Singleton::p = new Singleton();
Singleton* Singleton::initance()
{
	return p;
}

//直接定义静态对象
class Singleton
{
public:
	static Singleton& GetInstance();
private:
	Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator= (const Singleton&);
private:
	static Singleton m_Instance;
};
//CPP文件
Singleton Singleton::m_Instance;//类外定义-不要忘记写
Singleton& Singleton::GetInstance()
{
	return m_Instance;
}
//函数调用
Singleton& instance = Singleton::GetInstance();
*/