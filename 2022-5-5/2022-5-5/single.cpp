#include <iostream>
using namespace std;
#include <mutex> 

class Singleton
{
public:
	Singleton* GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_mutex.lock();
			if (nullptr == m_instance)
			{
				m_instance = new Singleton;
			}
			m_mutex.unlock();
		} 
		return m_instance;
	}
	~Singleton()
	{
		if (nullptr == m_instance)
		{
			//保证线程安全
			m_mutex.lock();
			if (m_instance)
			{
				delete m_instance;
				m_instance = nullptr;
			}
			m_mutex.unlock();
		}
	}
	//禁止拷贝
	Singleton(Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	Singleton()
	{

	}
	static Singleton* m_instance;
	static mutex m_mutex;
	static CGarbo gc;
};
Singleton* Singleton::m_instance = nullptr;
mutex Singleton::m_mutex;
Singleton::CGarbo gc;




class Singleton
{
public:
	//注意返回的是引用
	static Singleton& getInstance()
	{
		static Singleton m_instance;
		return m_instance;
	}
private:
	Singleton()
	{

	}
	Singleton(const Singleton& other);
};
int main()
{

}