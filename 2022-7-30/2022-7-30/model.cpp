/* ����ģʽ�̰߳�ȫ
��ָ̬��+ ʹ��ʱ��ʼ��
#include <iostream>
using namespace std;
template < class T>
class singgelon
{
public:
	static T& hanshu()
	{
		if (!val_)
		{
			val_ = new T();
		}
		return *val_;
	}
private:
	class cg
	{
	public:
		~cg()
		{
			if (singgelon::val_)
			{
				delete singgelon::val;
			}
		}
	};
	static cg c;
	singgelon();
	~singgelon();
	static T* val_;

};
template<typename T>
T* singgelon<T>::val_ = NULL;
int main()
{
	return 0;
}
*/


//��̬�ֲ�����
//����ʵ�����̰߳�ȫ��
#include <string>
#include <iostream>
using namespace std;
class Log
{
public:
    static Log* GetInstance()
    {
        static Log oLog;
        return &oLog;
    }

    void Output(string strLog)
    {
        cout << strLog << (*m_pInt) << endl;
    }
private:
    Log() :m_pInt(new int(3))
    {
    }
    ~Log()
    {
        cout << "~Log" << endl;
        delete m_pInt;
        m_pInt = nullptr;
    }
    int* m_pInt;
};

class Context
{
public:
    static Context* GetInstance()
    {
        static Context oContext;
        return &oContext;
    }
    ~Context()
    {
        Log::GetInstance()->Output(__FUNCTION__);
    }

    void fun()
    {
        Log::GetInstance()->Output(__FUNCTION__);
    }
private:
    Context() {}
    Context(const Context& context);
};

int main(int argc, char* argv[])
{
    Context::GetInstance()->fun();
    return 0;
}