#if 0
#include <iostream>
#include <thread>

using namespace std;

//仿函数
struct MyCop {
	void operator()(int a) {
		cout << "仿函数 :" << a << endl;
	}
};

void fun(int a) {
	cout << "function pointer: " << a << endl;
}
int main()
{
	//无参构造函数
	thread t1;
	cout << t1.get_id() << endl;
	//lambda
	thread t2([](int a) {
		cout << "lambda :" << a << endl;
		}, 10);
	t2.join();

	//仿函数
	MyCop mc;
	thread t3(mc, 1);
	t3.join();

	//函数指针
	thread t4(fun, 1);
	t4.join();
	return 0;
}
#endif 