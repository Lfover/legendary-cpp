#if 0
#include <iostream>
#include <thread>

using namespace std;

//�º���
struct MyCop {
	void operator()(int a) {
		cout << "�º��� :" << a << endl;
	}
};

void fun(int a) {
	cout << "function pointer: " << a << endl;
}
int main()
{
	//�޲ι��캯��
	thread t1;
	cout << t1.get_id() << endl;
	//lambda
	thread t2([](int a) {
		cout << "lambda :" << a << endl;
		}, 10);
	t2.join();

	//�º���
	MyCop mc;
	thread t3(mc, 1);
	t3.join();

	//����ָ��
	thread t4(fun, 1);
	t4.join();
	return 0;
}
#endif 