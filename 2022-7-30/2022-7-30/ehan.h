/*
//��ָ̬�룬�����ʼ��
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

//ֱ�Ӷ��徲̬����
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
//CPP�ļ�
Singleton Singleton::m_Instance;//���ⶨ��-��Ҫ����д
Singleton& Singleton::GetInstance()
{
	return m_Instance;
}
//��������
Singleton& instance = Singleton::GetInstance();
*/