#include <iostream>
using namespace std;
int main()
{
	int a = 10;
	int c = 2;
	double d = 2.5;
	auto b = [=, &a](int b,double x) {
		cout << a << endl;
		a += 2;
		cout << a << endl;
		cout << c << endl;
		cout << d << endl;
		cout << b << endl;
	};
	b(1, 1.1);
	return 0;
}